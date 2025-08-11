#include "qmc5883l.h"
#include "iic_bus.h"
#include <math.h>
#include <stdio.h>
#include "esp_log.h"

/**=========================================================================================== */
/**                                     DEFINE                                                 */
/**=========================================================================================== */
#define LOG_LOCAL_LEVEL ESP_LOG_DEBUG
#define QMC5883L_I2C_ADDR 0x0D
#define QMC5883L_MODE_REG 0x0B   // 模式寄存器地址
#define QMC5883L_CONFIG_REG 0x09 // 配置寄存器地址

/**=========================================================================================== */
/**                                     DATA                                                   */
/**=========================================================================================== */
static const char *TAG = "QMC5883L";
static i2c_port_t qmc5883l_i2c_port = I2C_NUM_0;
static TaskHandle_t kmc5883l_task_handle = NULL;

qmc5883l_data_t g_qmc5883l_data;

/**=========================================================================================== */
/**                                     FUNCITON                                               */
/**=========================================================================================== */
static esp_err_t qmc5883l_send_cmds(uint8_t reg_addr, const uint8_t *cmd_data, size_t len);
static esp_err_t qmc5883l_read_status(uint8_t reg_addr, uint8_t *status);
static esp_err_t qmc5883l_read_data(uint8_t reg_addr, uint8_t *data, size_t len);
static esp_err_t qmc5883l_get_angle(void);
static void kmc5881l_task(void *pvParameters);

/**=========================================================================================== */
/**                                     PUBILIC                                                */
/**=========================================================================================== */
/**
 * @brief qmc5883l初始化
 * 
 * 自动检测I2C总线是否已初始化，如果未初始化则自动初始化
 * 初始化成功后，自动启动任务
 * 任务每秒读取一次数据，并计算角度，存放于全局变量g_qmc5883l_data中
 * 
 * 检测是否初始化iic->检测设备是否存在->软件复位->设置模式->配置->启动任务
 * 
 * @param  void
 * @return esp_err_t 
 */
esp_err_t qmc5883l_init(void)
{
    esp_err_t err;
    esp_log_level_set(TAG, ESP_LOG_WARN);

    // 确保I2C总线已初始化
    if (i2c_is_inited(qmc5883l_i2c_port) == false)
    {
        err = i2c_bus_init(qmc5883l_i2c_port, GPIO_NUM_7, GPIO_NUM_8, 100000);
        if (err != ESP_OK)
        {
            ESP_LOGE(TAG, "I2C总线初始化失败: %d", err);
            return err;
        }
    }

    // 检查设备是否存在
    uint8_t id = 0;
    err = qmc5883l_read_status(0x0D, &id);
    if (err != ESP_OK)
    {
        ESP_LOGE(TAG, "QMC5883L读取设备ID失败: %d", err);
        return err;
    }
    if (id != 0xff)
    {
        ESP_LOGE(TAG, "QMC5883L设备ID不匹配: %d", id);
        return ESP_ERR_INVALID_STATE;
    }

    // 软件复位
    err = qmc5883l_send_cmds(0x0A, (const uint8_t[]){0x80}, 1);
    if (err != ESP_OK)
    {
        ESP_LOGE(TAG, "QMC5883L复位失败: %d", err);
        return err;
    }

    // Continuous Mode Setup
    err = qmc5883l_send_cmds(QMC5883L_MODE_REG, (const uint8_t[]){0x01}, 1);
    if (err != ESP_OK)
    {
        ESP_LOGE(TAG, "QMC5883L设置模式失败: %d", err);
        return err;
    }
    err = qmc5883l_send_cmds(QMC5883L_CONFIG_REG, (const uint8_t[]){0x1D}, 1);
    if (err != ESP_OK)
    {
        ESP_LOGE(TAG, "QMC5883L配置失败: %d", err);
        return err;
    }

    ESP_LOGI(TAG, "QMC5883L初始化成功");

    // 启动任务
    BaseType_t xReturned = xTaskCreatePinnedToCore((TaskFunction_t)kmc5881l_task, "kmc5881l_task", 4096, NULL, 5, &kmc5883l_task_handle, 1);
    if (xReturned != pdPASS)
    {
        ESP_LOGE("kmc5881l_task", "Failed to create task");
    }
    ESP_LOGI("kmc5881l_task", "Task created");

    return ESP_OK;
}

/**=========================================================================================== */
/**                                     STATIC                                                 */
/**=========================================================================================== */
/**
 * @brief qmc5883l任务
 * @param pvParameters 
 */
static void kmc5881l_task(void *pvParameters)
{
    while (1)
    {
        qmc5883l_get_angle();
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

/**
 * @brief qmc5883l读取角度
 * @return esp_err_t
 */
static esp_err_t qmc5883l_get_angle(void)
{
    esp_err_t err;
    uint8_t status = 0;
    uint8_t data[6] = {0};

    // Check status register 06H[0]
    err = qmc5883l_read_status(0x06, &status);
    if (err != ESP_OK)
    {
        ESP_LOGE(TAG, "QMC5883L读取状态失败: %d", err);
        return err;
    }
    if ((status & 0x01) != 1)
    {
        ESP_LOGE(TAG, "QMC5883L数据未准备好, 状态: %d", status);
        return ESP_ERR_TIMEOUT;
    }

    // Read data
    err = qmc5883l_read_data(0x00, data, 6);
    if (err != ESP_OK)
    {
        ESP_LOGE(TAG, "QMC5883L读取数据失败: %d", err);
        return err;
    }

    // ESP_LOGD(TAG, "QMC5883L数据: %d, %d, %d ,%d, %d, %d", data[0], data[1], data[2], data[3], data[4], data[5]);

    int16_t x = (int16_t)((data[1] << 8) | data[0]);
    int16_t y = (int16_t)((data[3] << 8) | data[2]);
    int16_t z = (int16_t)((data[5] << 8) | data[4]);

    // ESP_LOGD(TAG, "QMC5883L数据: %d, %d, %d", x, y, z);

    // -910 850
    //-1450 380

    // X_offset = (Xmax + Xmin) / 2
    // Y_offset = (Ymax + Ymin) / 2
    // 校准后的数据：
    // X_cal = X_raw - X_offset
    // Y_cal = Y_raw - Y_offset

    int16_t X_offset = (850 - 910) / 2;
    int16_t Y_offset = (380 - 1450) / 2;
    x -= X_offset;
    y -= Y_offset;

    // ESP_LOGD(TAG, "QMC5883L数据: %d, %d, %d", x, y, z);

    // 角度
    g_qmc5883l_data.angle = atan2((double)y, (double)x) * 180 / M_PI;
    if (g_qmc5883l_data.angle < 0)
        g_qmc5883l_data.angle += 360;

    ESP_LOGD(TAG, "QMC5883L角度: %.2f", g_qmc5883l_data.angle);

    return ESP_OK;
}

// qmc5883l发送命令
static esp_err_t qmc5883l_send_cmds(uint8_t reg_addr, const uint8_t *cmd_data, size_t len)
{
    return i2c_bus_write_bytes(qmc5883l_i2c_port, QMC5883L_I2C_ADDR, reg_addr, cmd_data, len);
}

// qmc5883l读取状态
static esp_err_t qmc5883l_read_status(uint8_t reg_addr, uint8_t *status)
{
    return i2c_bus_read_byte(qmc5883l_i2c_port, QMC5883L_I2C_ADDR, reg_addr, status);
}

// qmc5883l读取数据(地址位递归读取)
static esp_err_t qmc5883l_read_data(uint8_t reg_addr, uint8_t *data, size_t len)
{
    return i2c_bus_read_bytes(qmc5883l_i2c_port, QMC5883L_I2C_ADDR, reg_addr, data, len);
}
