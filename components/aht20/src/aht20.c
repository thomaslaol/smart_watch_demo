#include "aht20.h"
#include "iic_bus.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"

/**=========================================================================================== */
/**                                     DEFINE                                                 */
/**=========================================================================================== */
#define AHT20_I2C_ADDR 0x38        // AHT20默认I2C地址
#define AHT20_CMD_CALIBRATION 0x71 // 校准命令
#define AHT20_CMD_INIT 0xBE        // 初始化命令
#define AHT20_CMD_TRIGGER 0xAC     // 触发测量命令
#define AHT20_CMD_SOFT_RESET 0xBA  // 软复位命令
#define AHT20_STATUS_BUSY 0x80     // 状态字: 忙碌位(bit7)
#define AHT20_STATUS_CALIB 0x08    // 状态字: 校准位(bit3)

/**=========================================================================================== */
/**                                     DATA                                                   */
/**=========================================================================================== */

aht20_data_t g_aht20_data;             // 全局变量，用于存储AHT20测量数据
TaskHandle_t aht20_task_handle = NULL; // 全局变量，用于存储AHT20任务句柄

static const char *TAG = "AHT20";
static i2c_port_t aht20_i2c_port = I2C_NUM_0;
static esp_err_t aht20_get_value(aht20_data_t *aht20_data);            // 获取AHT20测量数据
static void aht20_task(void *pvParameters);                            // AHT20任务函数
static esp_err_t aht20_send_cmds(const uint8_t *cmd_data, size_t len); // 发送AHT20命令
static esp_err_t aht20_read_status(uint8_t *status);                   // 读取AHT20状态寄存器
static esp_err_t aht20_read_data(uint8_t *data, size_t len);           // 读取AHT20测量数据（支持读取指定长度的字节）
static esp_err_t aht20_wait_for_idle(uint32_t timeout_ms);             // 等待AHT20完成测量
static uint8_t crc8_calculate(const uint8_t *data, int length);        // crc校验

/**=========================================================================================== */
/**                                     PUBLIC                                                 */
/**=========================================================================================== */
/**
 * @brief 初始化AHT20传感器
 * @param void 无参数
 * @return esp_err_t 操作结果（ESP_OK表示成功）
 */
esp_err_t aht20_init(void)
{
    esp_err_t err;
    uint8_t status;

    esp_log_level_set(TAG, ESP_LOG_WARN);

    // 确保I2C总线已初始化
    if (i2c_is_inited(aht20_i2c_port) == false)
    {
        err = i2c_bus_init(aht20_i2c_port, GPIO_NUM_7, GPIO_NUM_8, 100000);
        if (err != ESP_OK)
        {
            ESP_LOGE(TAG, "I2C总线初始化失败: %d", err);
            return err;
        }
    }

    // 等待AHT20完成上电
    vTaskDelay(pdMS_TO_TICKS(400));

    /**状态字的校准使能位 Bit[3]是否为 1*/
    // 1、发送0x71
    err = aht20_send_cmds((const uint8_t[]){AHT20_CMD_CALIBRATION}, 1);
    if (err != ESP_OK)
    {
        if (err != ESP_OK)
        {
            ESP_LOGE(TAG, "校准使能位发送失败: %d", err);
            return err;
        }
    }

    // 2、接收状态字
    err = aht20_read_status(&status);
    if (err != ESP_OK)
    {
        ESP_LOGE(TAG, "读取状态字失败: %d", err);
        return err;
    }
    ESP_LOGD(TAG, "状态字: 0x%02X", status);

    // 校准使能位 Bit[3]是否为 1
    if ((status & (1 << 3)) == 0)
    {
        ESP_LOGW(TAG, "校准使能位为0,传感器连接异常,状态字: %d,正在尝试重置...", status);
        uint8_t cmd[3] = {AHT20_CMD_INIT, 0x08, 0x00};
        aht20_send_cmds(cmd, 3);
        vTaskDelay(pdMS_TO_TICKS(10));
    }
    vTaskDelay(pdMS_TO_TICKS(100));
    ESP_LOGI(TAG, "初始化成功完成");

    // 启动任务
    BaseType_t xReturned;
    xReturned = xTaskCreatePinnedToCore((TaskFunction_t)aht20_task, "aht20_task", 4096, NULL, 5, &aht20_task_handle, 1);
    if (xReturned != pdPASS)
    {
        ESP_LOGE("aht20_task", "Failed to create task");
        return ESP_FAIL;
    }
    ESP_LOGI("aht20_task", "Task created");

    return ESP_OK;
}

char *aht20_get_temp_str(void)
{
    static char temp_str[32];
    sprintf(temp_str, "%.0f", g_aht20_data.temperature);
    return temp_str;
}

char *aht20_get_hum_str(void)
{
    static char hum_str[32] = {0};
    sprintf(hum_str, "%.0f%", g_aht20_data.humidity);
    return hum_str;
}
/**=========================================================================================== */
/**                                     STATIC                                                 */
/**=========================================================================================== */
/**
 * @brief AHT20任务
 *
 * 每2秒获取一次温度和湿度值
 *
 * @param pvParameters
 */
static void aht20_task(void *pvParameters)
{
    ESP_LOGI(TAG, "AHT20任务开始");
    while (1)
    {
        aht20_get_value(&g_aht20_data);
        // printf("温度：%f, 湿度：%f\n", g_aht20_data.temperature, g_aht20_data.humidity);
        vTaskDelay(pdMS_TO_TICKS(2000));
    }
}

// 获取AHT20的温度和湿度值
static esp_err_t aht20_get_value(aht20_data_t *aht20_data)
{
    uint8_t data[7] = {0xff, 0};
    esp_err_t err;

    /**发送触发测量 */
    uint8_t cmd[3] = {AHT20_CMD_TRIGGER, 0x33, 0x00};
    err = aht20_send_cmds(cmd, 3);
    if (err != ESP_OK)
    {
        ESP_LOGE(TAG, "触发测量命令发送失败: %d", err);
        return err;
    }

    // 等待测量完成
    vTaskDelay(pdMS_TO_TICKS(80));

    err = aht20_wait_for_idle(1000);
    if (err != ESP_OK)
    {
        ESP_LOGE(TAG, "等待测量完成超时: %d", err);
        return err;
    }

    // 读取测量数据
    err = aht20_read_data(&data[0], 7);
    if (err != ESP_OK)
    {
        ESP_LOGE(TAG, "读取测量数据失败: %d", err);
        return err;
    }

    // 检查数据有效性
    ESP_LOGD(TAG, "读取到的数据: %02X %02X %02X %02X %02X %02X %02X", data[0], data[1], data[2], data[3], data[4], data[5], data[6]);

    uint8_t crc_ret = crc8_calculate(data, 6);
    if (crc_ret != data[6])
    {
        ESP_LOGE(TAG, "数据校验失败: CRC不匹配:%d != %d", crc_ret, data[6]);
        return ESP_ERR_INVALID_CRC;
    }

    // 解析数据
    uint32_t hum_raw = ((uint32_t)data[1] << 12) | ((uint32_t)data[2] << 4) | (data[3] >> 4);
    uint32_t temp_raw = (((uint32_t)(data[3] & 0x0F)) << 16) | ((uint32_t)data[4] << 8) | data[5];

    aht20_data->humidity = (float)hum_raw * 100.0f / 0x100000;
    aht20_data->temperature = (float)temp_raw * 200.0f / 0x100000 - 50.0f;

    ESP_LOGD(TAG, "温度: %.2f°C, 湿度: %.2f%%", aht20_data->humidity, aht20_data->temperature);

    return ESP_OK;
}

// 向AHT20发送多字节命令（支持单条/多条指令）
static esp_err_t aht20_send_cmds(const uint8_t *cmd_data, size_t len)
{
    // 参数合法性检查
    if (cmd_data == NULL || len == 0)
    {
        ESP_LOGE(TAG, "无效参数:cmd_data=%p, len=%zu", cmd_data, len);
        return ESP_ERR_INVALID_ARG;
    }

    // AHT20无需寄存器地址，寄存器地址传0xFF；发送多字节命令
    return i2c_bus_write_bytes(aht20_i2c_port, AHT20_I2C_ADDR, 0xFF, cmd_data, len);
}

// 读取AHT20状态寄存器
static esp_err_t aht20_read_status(uint8_t *status)
{
    return i2c_bus_read_byte(aht20_i2c_port, AHT20_I2C_ADDR, 0xFF, status);
}

// 读取AHT20测量数据（支持读取指定长度的字节）
static esp_err_t aht20_read_data(uint8_t *data, size_t len)
{
    // 1. 参数合法性检查（避免空指针或无效长度）
    if (data == NULL || len == 0)
    {
        ESP_LOGE("AHT20", "读取失败:无效参数(data=%p, len=%zu)", data, len);
        return ESP_ERR_INVALID_ARG;
    }

    esp_err_t err = i2c_bus_read_bytes(aht20_i2c_port, AHT20_I2C_ADDR, 0xFF, data, len);
    if (err != ESP_OK)
        ESP_LOGE("AHT20", "读取数据失败（长度：%zu字节),错误码：%d", len, err);
    else
        ESP_LOGI("AHT20", "成功读取%d字节数据", len);

    return err;
}

// 等待AHT20完成测量
static esp_err_t aht20_wait_for_idle(uint32_t timeout_ms)
{
    uint8_t status = 0;
    uint32_t start_time = xTaskGetTickCount() * portTICK_PERIOD_MS;

    do
    {
        esp_err_t err = aht20_read_status(&status);
        if (err != ESP_OK)
        {
            return err;
        }

        if ((status & AHT20_STATUS_BUSY) == 0)
        {
            ESP_LOGI(TAG, "测量完成: 状态字: 0x%02X", status);
            return ESP_OK; // 不再忙碌
        }

        vTaskDelay(pdMS_TO_TICKS(10));
    } while ((xTaskGetTickCount() * portTICK_PERIOD_MS - start_time) < timeout_ms);

    return ESP_ERR_TIMEOUT;
}

// crc校验
static uint8_t crc8_calculate(const uint8_t *data, int length)
{
    uint8_t crc = 0xff;
    while (length--)
    {
        crc ^= *data++;
        for (int i = 0; i < 8; i++)
        {
            if (crc & 0x80)
            {
                crc = (crc << 1) ^ 0x31;
            }
            else
            {
                crc <<= 1;
            }
        }
    }
    return crc;
}
