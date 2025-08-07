#include "iic_bus.h"
// #include "driver/i2c_master.h"
#include "esp_log.h"
#include "string.h"
#include "freertos/FreeRTOS.h"

/** 记录每个I2C端口的初始化状态
 *  ESP32最多支持2个I2C端口，由I2C_NUM_MAX定义
 */
static bool i2c_port_inited[I2C_NUM_MAX] = {false};

/**
 * @brief 判断指定I2C端口是否初始化
 * @param port 要检查的I2C端口（如I2C_NUM_0）
 * @return bool 初始化状态（true已初始化，false未初始化）
 */
bool i2c_is_inited(i2c_port_t port)
{
    if (port >= I2C_NUM_MAX)
    {
        return false; // 无效端口视为未初始化
    }
    return i2c_port_inited[port];
}

/**
 * @brief 初始化指定I2C端口
 * @param port I2C端口（如I2C_NUM_0）
 * @param sda SDA引脚号
 * @param scl SCL引脚号
 * @param freq I2C总线频率（如100000、400000）
 * @return esp_err_t 操作结果（ESP_OK表示成功）
 */
esp_err_t i2c_bus_init(i2c_port_t port, gpio_num_t sda, gpio_num_t scl, uint32_t freq)
{
    // 检查端口合法性
    if (port >= I2C_NUM_MAX)
    {
        ESP_LOGE("I2C", "无效端口号: %d(最大支持%d)", port, I2C_NUM_MAX - 1);
        return ESP_ERR_INVALID_ARG;
    }

    // 若已初始化，直接返回成功
    if (i2c_port_inited[port])
    {
        ESP_LOGW("I2C", "端口%d已初始化,无需重复操作", port);
        return ESP_OK;
    }

    // 配置I2C参数
    i2c_config_t conf = {
        .mode = I2C_MODE_MASTER,
        .sda_io_num = sda,
        .scl_io_num = scl,
        .sda_pullup_en = GPIO_PULLUP_ENABLE,
        .scl_pullup_en = GPIO_PULLUP_ENABLE,
        .master.clk_speed = freq,
    };

    // 配置I2C参数
    esp_err_t err = i2c_param_config(port, &conf);
    if (err != ESP_OK)
    {
        ESP_LOGE("I2C", "端口%d参数配置失败: %d", port, err);
        return err;
    }

    // 安装I2C驱动
    err = i2c_driver_install(port, conf.mode, 0, 0, 0);
    if (err != ESP_OK)
    {
        ESP_LOGE("I2C", "端口%d驱动安装失败: %d", port, err);
        return err;
    }

    // 标记该端口已初始化
    i2c_port_inited[port] = true;
    ESP_LOGI("I2C", "端口%d初始化成功(SDA: %d, SCL: %d, 频率: %lukHz)",port, sda, scl, freq / 1000);
    return ESP_OK;
}

/**
 * @brief I2C发送一个字节（支持多端口，带/不带寄存器地址）
 * @param port I2C端口（如I2C_NUM_0）
 * @param dev_addr 设备I2C地址（7位地址，无需左移）
 * @param reg_addr 寄存器地址（无需寄存器地址时传0xFF）
 * @param data 要发送的字节数据
 * @return esp_err_t 操作结果（ESP_OK表示成功）
 */
esp_err_t i2c_bus_write_byte(i2c_port_t port, uint8_t dev_addr, uint8_t reg_addr, uint8_t data)
{
    // 检查端口合法性和初始化状态
    if (port >= I2C_NUM_MAX)
    {
        ESP_LOGE("I2C", "无效端口号: %d", port);
        return ESP_ERR_INVALID_ARG;
    }
    if (!i2c_port_inited[port])
    {
        ESP_LOGE("I2C", "端口%d未初始化,无法发送数据", port);
        return ESP_ERR_INVALID_STATE;
    }

    uint8_t buffer[2];
    size_t len = 1;

    // 区分“带寄存器地址”和“不带寄存器地址”模式
    if (reg_addr != 0xFF)
    {
        buffer[0] = reg_addr;
        buffer[1] = data;
        len = 2;
    }
    else
    {
        buffer[0] = data; // 仅数据（无寄存器地址，适合AHT20等设备）
    }

    // 调用ESP-IDF API发送数据（指定端口）
    return i2c_master_write_to_device(
        port,
        dev_addr,
        buffer,
        len,
        1000 / portTICK_PERIOD_MS
    );
}

/**
 * @brief I2C读取一个字节（支持多端口，带/不带寄存器地址）
 * @param port I2C端口（如I2C_NUM_0）
 * @param dev_addr 设备I2C地址（7位地址，无需左移）
 * @param reg_addr 寄存器地址（无需寄存器地址时传0xFF）
 * @param[out] data 读取到的数据（通过指针返回）
 * @return esp_err_t 操作结果（ESP_OK表示成功）
 */
esp_err_t i2c_bus_read_byte(i2c_port_t port, uint8_t dev_addr, uint8_t reg_addr, uint8_t *data)
{
    // 检查参数合法性
    if (port >= I2C_NUM_MAX || data == NULL) {
        ESP_LOGE("I2C", "无效参数:port=%d, data=%p", port, data);
        return ESP_ERR_INVALID_ARG;
    }
    
    // 检查端口是否已初始化
    if (!i2c_port_inited[port]) {
        ESP_LOGE("I2C", "端口%d未初始化,无法读取数据", port);
        return ESP_ERR_INVALID_STATE;
    }

    esp_err_t err;

    // 情况1：需要先发送寄存器地址，再读取数据（大多数设备）
    if (reg_addr != 0xFF) {
        // 步骤1：发送寄存器地址（写操作）
        err = i2c_master_write_to_device(
            port, 
            dev_addr, 
            &reg_addr,
            1,
            1000 / portTICK_PERIOD_MS
        );
        if (err != ESP_OK) {
            ESP_LOGE("I2C", "发送寄存器地址失败：设备=0x%02X, 寄存器=0x%02X, 错误=%d", 
                     dev_addr, reg_addr, err);
            return err;
        }

        // 步骤2：读取数据（读操作）
        err = i2c_master_read_from_device(
            port, 
            dev_addr, 
            data,
            1,
            1000 / portTICK_PERIOD_MS
        );
        if (err != ESP_OK) {
            ESP_LOGE("I2C", "读取数据失败：设备=0x%02X, 错误=%d", dev_addr, err);
        }
        return err;
    }
    
    // 情况2：不需要发送寄存器地址，直接读取数据（如某些设备的状态寄存器）
    err = i2c_master_read_from_device(
        port, 
        dev_addr, 
        data,
        1,
        1000 / portTICK_PERIOD_MS
    );
    if (err != ESP_OK) {
        ESP_LOGE("I2C", "直接读取数据失败：设备=0x%02X, 错误=%d", dev_addr, err);
    }
    return err;
}


/**
 * @brief I2C读取多个字节（支持多端口，带/不带寄存器地址）
 * @param port I2C端口（如I2C_NUM_0）
 * @param dev_addr 设备I2C地址（7位地址，无需左移）
 * @param reg_addr 寄存器地址（无需寄存器地址时传0xFF）
 * @param[out] data 读取到的数据缓冲区
 * @param len 要读取的字节数
 * @return esp_err_t 操作结果（ESP_OK表示成功）
 */
esp_err_t i2c_bus_read_bytes(i2c_port_t port, uint8_t dev_addr, uint8_t reg_addr, 
                             uint8_t *data, size_t len)
{
    // 检查参数合法性
    if (port >= I2C_NUM_MAX || data == NULL || len == 0) {
        ESP_LOGE("I2C", "无效参数:port=%d, data=%p, len=%zu", port, data, len);
        return ESP_ERR_INVALID_ARG;
    }
    
    // 检查端口是否已初始化
    if (!i2c_port_inited[port]) {
        ESP_LOGE("I2C", "端口%d未初始化,无法读取数据", port);
        return ESP_ERR_INVALID_STATE;
    }

    esp_err_t err;

    // 情况1：需要先发送寄存器地址，再读取数据
    if (reg_addr != 0xFF) {
        // 步骤1：发送寄存器地址（写操作）
        err = i2c_master_write_to_device(
            port, 
            dev_addr, 
            &reg_addr,  // 要读取的寄存器地址
            1,          // 地址长度1字节
            1000 / portTICK_PERIOD_MS  // 超时时间
        );
        if (err != ESP_OK) {
            ESP_LOGE("I2C", "发送寄存器地址失败：设备=0x%02X, 寄存器=0x%02X, 错误=%d", 
                     dev_addr, reg_addr, err);
            return err;
        }
    }

    // 步骤2：读取多个字节数据（读操作）
    err = i2c_master_read_from_device(
        port, 
        dev_addr, 
        data,       // 存储读取数据的缓冲区
        len,        // 读取的字节数
        1000 / portTICK_PERIOD_MS  // 超时时间
    );
    if (err != ESP_OK) {
        ESP_LOGE("I2C", "读取数据失败：设备=0x%02X, 长度=%zu, 错误=%d", dev_addr, len, err);
    }
    return err;
}

/**
 * @brief I2C发送多个字节（支持多端口，带/不带寄存器地址）
 * @param port I2C端口（如I2C_NUM_0）
 * @param dev_addr 设备I2C地址（7位地址，无需左移）
 * @param reg_addr 寄存器地址（无需寄存器地址时传0xFF）
 * @param data 要发送的数据缓冲区
 * @param len 要发送的字节数
 * @return esp_err_t 操作结果（ESP_OK表示成功）
 */
esp_err_t i2c_bus_write_bytes(i2c_port_t port, uint8_t dev_addr, uint8_t reg_addr, 
                             const uint8_t *data, size_t len)
{
    // 检查参数合法性
    if (port >= I2C_NUM_MAX || data == NULL || len == 0) {
        ESP_LOGE("I2C", "无效参数:port=%d, data=%p, len=%zu", port, data, len);
        return ESP_ERR_INVALID_ARG;
    }
    
    // 检查端口是否已初始化
    if (!i2c_port_inited[port]) {
        ESP_LOGE("I2C", "端口%d未初始化,无法发送数据", port);
        return ESP_ERR_INVALID_STATE;
    }

    // 计算总数据长度（寄存器地址 + 数据）
    size_t total_len = (reg_addr != 0xFF) ? (len + 1) : len;
    
    // 创建临时缓冲区（如果需要发送寄存器地址）
    uint8_t *buffer = NULL;
    if (reg_addr != 0xFF) {
        buffer = (uint8_t *)malloc(total_len);
        if (buffer == NULL) {
            ESP_LOGE("I2C", "内存分配失败，无法发送数据");
            return ESP_ERR_NO_MEM;
        }
        
        // 组合数据：[寄存器地址, 数据...]
        buffer[0] = reg_addr;
        memcpy(buffer + 1, data, len);
    } else {
        buffer = (uint8_t *)data;  // 无需寄存器地址，直接使用原始数据
    }

    // 发送数据
    esp_err_t err = i2c_master_write_to_device(
        port, 
        dev_addr, 
        buffer, 
        total_len, 
        1000 / portTICK_PERIOD_MS
    );

    // 释放临时缓冲区（如果分配了）
    if (reg_addr != 0xFF) {
        free(buffer);
    }

    return err;
}
