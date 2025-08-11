#ifndef _AHT20_H_
#define _AHT20_H_

#include "esp_err.h"

typedef struct {
    float temperature; // 温度值（单位：摄氏度）
    float humidity;    // 湿度值（单位：百分比）
} aht20_data_t;

extern aht20_data_t g_aht20_data; // 全局变量，存储AHT20的温度和湿度值

/**
 * @brief 初始化AHT20传感器 
 * 
 * 初始化成功会自动启动AHT20的freeRTOS任务
 * 每2秒获取一次温度和湿度值存放在全局变量g_aht20_data中
 * 
 * @param void
 * @return esp_err_t 操作结果（ESP_OK表示成功）
 */

esp_err_t aht20_init(void);
char *aht20_get_temp_str(void);
char *aht20_get_hum_str(void);

#endif // _AHT20_H_