#ifndef _BMP280_H_
#define _BMP280_H_

#include "esp_err.h"

typedef struct __attribute__((packed))
{
    int32_t temperature;
    uint32_t pressure;
} bmp280_data_t;

extern bmp280_data_t g_bmp280_data;

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
esp_err_t bmp280_init(void);

#endif // _BMP280_H_