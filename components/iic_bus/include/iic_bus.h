#ifndef _IIC_BUS_H_
#define _IIC_BUS_H_

#include "stdint.h"
#include "driver/i2c.h"

/**
 * @brief 判断指定I2C端口是否初始化
 * @param port 要检查的I2C端口（如I2C_NUM_0）
 * @return bool 初始化状态（true已初始化，false未初始化）
 */
bool i2c_is_inited(i2c_port_t port);

/**
 * @brief 初始化指定I2C端口
 * @param port I2C端口（如I2C_NUM_0）
 * @param sda SDA引脚号
 * @param scl SCL引脚号
 * @param freq I2C总线频率（如100000、400000）
 * @return esp_err_t 操作结果（ESP_OK表示成功）
 */
esp_err_t i2c_bus_init(i2c_port_t port, gpio_num_t sda, gpio_num_t scl, uint32_t freq);

/**
 * @brief I2C发送一个字节（支持多端口，带/不带寄存器地址）
 * @param port I2C端口（如I2C_NUM_0）
 * @param dev_addr 设备I2C地址（7位地址，无需左移）
 * @param reg_addr 寄存器地址（无需寄存器地址时传0xFF）
 * @param data 要发送的字节数据
 * @return esp_err_t 操作结果（ESP_OK表示成功）
 */
esp_err_t i2c_bus_write_byte(i2c_port_t port, uint8_t dev_addr, uint8_t reg_addr, uint8_t data);

/**
 * @brief I2C读取一个字节（支持多端口，带/不带寄存器地址）
 * @param port I2C端口（如I2C_NUM_0）
 * @param dev_addr 设备I2C地址（7位地址，无需左移）
 * @param reg_addr 寄存器地址（无需寄存器地址时传0xFF）
 * @param[out] data 读取到的数据（通过指针返回）
 * @return esp_err_t 操作结果（ESP_OK表示成功）
 */
esp_err_t i2c_bus_read_byte(i2c_port_t port, uint8_t dev_addr, uint8_t reg_addr, uint8_t *data);

/**
 * @brief I2C读取多个字节（支持多端口，带/不带寄存器地址）
 * @param port I2C端口（如I2C_NUM_0）
 * @param dev_addr 设备I2C地址（7位地址，无需左移）
 * @param reg_addr 寄存器地址（无需寄存器地址时传0xFF）
 * @param[out] data 读取到的数据缓冲区
 * @param len 要读取的字节数
 * @return esp_err_t 操作结果（ESP_OK表示成功）
 */
esp_err_t i2c_bus_read_bytes(i2c_port_t port, uint8_t dev_addr, uint8_t reg_addr, uint8_t *data, size_t len);

/**
 * @brief I2C发送多个字节（支持多端口，带/不带寄存器地址）
 * @param port I2C端口（如I2C_NUM_0）
 * @param dev_addr 设备I2C地址（7位地址，无需左移）
 * @param reg_addr 寄存器地址（无需寄存器地址时传0xFF）
 * @param data 要发送的数据缓冲区
 * @param len 要发送的字节数
 * @return esp_err_t 操作结果（ESP_OK表示成功）
 */
esp_err_t i2c_bus_write_bytes(i2c_port_t port, uint8_t dev_addr, uint8_t reg_addr, const uint8_t *data, size_t len);

#endif // _IIC_BUS_H_
