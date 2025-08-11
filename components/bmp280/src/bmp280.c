#include "bmp280.h"
#include "iic_bus.h"
#include "esp_log.h"

/**=========================================================================================== */
/**                                     DEFINE                                                 */
/**=========================================================================================== */
#define LOG_LOCAL_LEVEL ESP_LOG_DEBUG

#define BMP280_I2C_ADDR 0x77
#define BMP280_REG_ID 0xD0
#define BMP280_CHIP_ID 0x58
#define BMP280_REG_CTRL_MEAS 0xF4

/**=========================================================================================== */
/**                                     DATA                                                   */
/**=========================================================================================== */
bmp280_data_t g_bmp280_data; // bmp280数据

// 定义校准数据结构体（全局或通过参数传递）
typedef struct __attribute__((packed))
{
    uint16_t dig_T1; // 字节0-1
    int16_t dig_T2;  // 字节2-3
    int16_t dig_T3;  // 字节4-5
    uint16_t dig_P1; // 字节6-7
    int16_t dig_P2;  // 字节8-9
    int16_t dig_P3;  // 字节10-11
    int16_t dig_P4;  // 字节12-13
    int16_t dig_P5;  // 字节14-15
    int16_t dig_P6;  // 字节16-17
    int16_t dig_P7;  // 字节18-19
    int16_t dig_P8;  // 字节20-21
    int16_t dig_P9;  // 字节22-23
} bmp280_calib_data_t;

static TaskHandle_t bmp280_task_handle = NULL;
static const char *TAG = "bmp280";
static i2c_port_t bmp280_i2c_port = I2C_NUM_0;
static bmp280_calib_data_t calib;

/**=========================================================================================== */
/**                                     FUNCTION                                               */
/**=========================================================================================== */
// bmp280任务
static void bmp280_task(void *pvParameters);
// bmp280读取温度和压力数据
static esp_err_t bmp280_get_data(float *temp, float *press);
// bmp280读取temp校准数据
static float bmp280_convert_temp(int32_t adc_T, int32_t *t_fine);
// bmp280读取press校准数据
static float bmp280_convert_press(int32_t adc_P, int32_t t_fine);
// bmp280发送命令
static esp_err_t bmp280_send_cmds(uint8_t reg_addr, const uint8_t *cmd_data, size_t len);
// bmp280读取数据(地址位递归读取)
static esp_err_t bmp280_read_data(uint8_t reg_addr, uint8_t *data, size_t len);

/**=========================================================================================== */
/**                                     PUBLIC                                                 */
/**=========================================================================================== */
/**
 * @brief 初始化bmp280
 *
 * 自动确定I2C总线是否已初始化，如果未初始化则进行初始化
 * 成功初始化后，会自动创建一个任务，用于读取温度和压力数据
 * 数据每2秒更新一次，存放在全局变量g_bmp280_data中
 *
 * 确定iic是否已初始化->>初始化iic->>读取芯片ID->>读取校准数据->>配置工作参数->>创建任务
 *
 * @param 无
 * @return esp_err_t 操作结果（ESP_OK表示成功）
 */
esp_err_t bmp280_init(void)
{
    esp_err_t err;
    esp_log_level_set(TAG, ESP_LOG_WARN);

    // 确保I2C总线已初始化
    if (i2c_is_inited(bmp280_i2c_port) == false)
    {
        err = i2c_bus_init(bmp280_i2c_port, GPIO_NUM_7, GPIO_NUM_8, 100000);
        if (err != ESP_OK)
        {
            ESP_LOGE(TAG, "I2C总线初始化失败: %d", err);
            return err;
        }
    }

    // 读取芯片ID
    uint8_t chip_id;
    err = bmp280_read_data(BMP280_REG_ID, &chip_id, 1);
    if (err != ESP_OK)
    {
        ESP_LOGE(TAG, "读取芯片ID失败: %d", err);
        return err;
    }

    if (chip_id != BMP280_CHIP_ID)
    {
        ESP_LOGE(TAG, "芯片ID不匹配: 0x%02x", chip_id);
        return ESP_ERR_INVALID_STATE;
    }

    // 读取校准数据
    err = bmp280_read_data(0x88, (uint8_t *)&calib, 24);
    if (err != ESP_OK)
    {
        ESP_LOGE(TAG, "读取校准数据失败: %d", err);
        return err;
    }

    for (uint8_t i = 0; i < 24; i++)
    {
        ESP_LOGD(TAG, "calib[%d]: 0x%02x", i, ((uint8_t *)&calib)[i]);
    }

    ESP_LOGD(TAG, "P校准参数: P1=%u, P2=%d, P3=%d, P4=%d, P5=%d, P6=%d, P7=%d, P8=%d, P9=%d",
             calib.dig_P1, calib.dig_P2, calib.dig_P3, calib.dig_P4,
             calib.dig_P5, calib.dig_P6, calib.dig_P7, calib.dig_P8, calib.dig_P9);

    // meas
    // 0101 0111
    // 010 2位温度过采样率
    // 101 16位压力过采样率
    // 11 模式正常
    err = bmp280_send_cmds(0xF4, (uint8_t[]){0x57}, 1);
    if (err != ESP_OK)
    {
        ESP_LOGE(TAG, "配置工作参数失败: %d", err);
        return err;
    }

    // config
    // 1010 1000
    // 101 1000ms
    // 010 x4
    // 00
    err = bmp280_send_cmds(0xF5, (uint8_t[]){0xA8}, 1);
    if (err != ESP_OK)
    {
        ESP_LOGE(TAG, "配置工作参数失败: %d", err);
        return err;
    }

    ESP_LOGI(TAG, "bmp280初始化成功");

    // 创建任务
    BaseType_t xReturned = xTaskCreatePinnedToCore((TaskFunction_t)bmp280_task, "bmp280_task", 4096, NULL, 5, &bmp280_task_handle, 1);
    if (xReturned != pdPASS)
    {
        ESP_LOGE("bmp280_task", "Failed to create task");
    }
    ESP_LOGI("bmp280_task", "Task created");

    return ESP_OK;
}

/**=========================================================================================== */
/**                                     STATIC                                                 */
/**=========================================================================================== */
// bmp280任务 每2s读取一次数据
static void bmp280_task(void *pvParameters)
{
    while (1)
    {
        bmp280_get_data(&g_bmp280_data.pressure, &g_bmp280_data.temperature);
        // printf("温度：%.2f, 气压：%.2f\n", temperature, pressure);
        vTaskDelay(pdMS_TO_TICKS(2000));
    }
}

// bmp280读取数据(地址位递归读取)
static esp_err_t bmp280_get_data(float *temp, float *press)
{
    esp_err_t err;
    int32_t t_fine;
    uint8_t buf[6] = {0};

    err = bmp280_read_data(0xF7, buf, 6);
    if (err != ESP_OK)
    {
        ESP_LOGE(TAG, "读取数据失败: %d", err);
        return err;
    }

    int32_t adc_P = ((buf[0] << 12) | (buf[1] << 4) | (buf[2] >> 4));
    int32_t adc_T = ((buf[3] << 12) | (buf[4] << 4) | (buf[5] >> 4));

    ESP_LOGD(TAG, "adc_P: %d, adc_T: %d", adc_P, adc_T);

    // 转换为实际值
    *temp = bmp280_convert_temp(adc_T, &t_fine);

    *press = bmp280_convert_press(adc_P, t_fine);
    ESP_LOGI(TAG, "温度: %.2f ℃, 气压: %.2f hPa", *temp, *press);

    return ESP_OK;
}

// bmp280读取temp校准数据
static float bmp280_convert_temp(int32_t adc_T, int32_t *t_fine)
{
    int32_t var1, var2;
    var1 = ((((adc_T >> 3) - ((int32_t)calib.dig_T1 << 1))) * ((int32_t)calib.dig_T2)) >> 11;
    var2 = (((((adc_T >> 4) - ((int32_t)calib.dig_T1)) * ((adc_T >> 4) - ((int32_t)calib.dig_T1))) >> 12) * ((int32_t)calib.dig_T3)) >> 14;
    *t_fine = var1 + var2;

    float temp_calc = (float)(*t_fine * 5 + 128) / 25600.0f; // 修正后的公式
    ESP_LOGD(TAG, "计算的温度值: %.2f", temp_calc);          // 新增打印
    return temp_calc;
}

// bmp280读取press校准数据
static float bmp280_convert_press(int32_t adc_P, int32_t t_fine)
{
    int64_t var1, var2, p;
    var1 = (int64_t)t_fine - 128000;
    var2 = var1 * var1 * (int64_t)calib.dig_P6;
    var2 = var2 + ((var1 * (int64_t)calib.dig_P5) << 17);
    var2 = var2 + (((int64_t)calib.dig_P4) << 35);
    var1 = ((var1 * var1 * (int64_t)calib.dig_P3) >> 8) + ((var1 * (int64_t)calib.dig_P2) << 12);
    var1 = (((((int64_t)1) << 47) + var1) * (int64_t)calib.dig_P1) >> 33;

    if (var1 == 0)
        return 0.0f;

    p = 1048576 - adc_P;
    p = (((p << 31) - var2) * 3125) / var1;
    var1 = ((int64_t)calib.dig_P9 * (p >> 13) * (p >> 13)) >> 25;
    var2 = ((int64_t)calib.dig_P8 * p) >> 19;
    p = ((p + var1 + var2) >> 8) + ((int64_t)calib.dig_P7 << 4);

    return (float)p / 25600.0f; // 直接返回hPa（除以256*100）
}

// bmp280发送命令
static esp_err_t bmp280_send_cmds(uint8_t reg_addr, const uint8_t *cmd_data, size_t len)
{
    return i2c_bus_write_bytes(bmp280_i2c_port, BMP280_I2C_ADDR, reg_addr, cmd_data, len);
}

// bmp280读取数据(地址位递归读取)
static esp_err_t bmp280_read_data(uint8_t reg_addr, uint8_t *data, size_t len)
{
    return i2c_bus_read_bytes(bmp280_i2c_port, BMP280_I2C_ADDR, reg_addr, data, len);
}
