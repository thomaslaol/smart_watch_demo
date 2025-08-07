#ifndef _AHT20_H_
#define _AHT20_H_

#include "esp_err.h"

#define AHT20_I2C_ADDR 0x38        // AHT20默认I2C地址
#define AHT20_CMD_CALIBRATION 0x71 // 校准命令
#define AHT20_CMD_INIT 0xBE        // 初始化命令
#define AHT20_CMD_TRIGGER 0xAC     // 触发测量命令
#define AHT20_CMD_SOFT_RESET 0xBA  // 软复位命令
#define AHT20_STATUS_BUSY 0x80     // 状态字: 忙碌位(bit7)
#define AHT20_STATUS_CALIB 0x08    // 状态字: 校准位(bit3)

/**
 * @brief 初始化AHT20传感器
 * @param void
 * @return esp_err_t 操作结果（ESP_OK表示成功）
 */
esp_err_t aht20_init(void);

/**
 * @brief 获取AHT20的温度和湿度值
 * @param temperature 温度值（单位：摄氏度）
 * @param humidity 湿度值（单位：百分比）
 * @return esp_err_t 操作结果（ESP_OK表示成功）
 */
esp_err_t aht20_get_value(float *temperature, float *humidity);

#endif // _AHT20_H_