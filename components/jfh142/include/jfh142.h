#ifndef _JFH142_H_
#define _JFH142_H_

#include <stdbool.h>
#include "esp_err.h"

// 健康数据结构体(供应用层使用)
typedef struct
{
    uint8_t heartrate;          // 心率
    uint8_t spo2;               // 血氧
    uint8_t bk;                 // 微循环
    uint8_t fatigue_index;      // 疲劳指数
    uint8_t systolic_pressure;  // 收缩压 (高压)
    uint8_t diastolic_pressure; // 舒张压 （低压）
    bool is_detected;           // 是否检测到人体
} jfh142_health_data_t;


/**
 * @brief 初始化JFH142传感器
 *
 * 初始化成功后会自动启动数据采集
 * 任务每秒读取一次数据，数据保存在全局变量g_health_data中
 * 
 * 初始化硬件->初始化UART->创建数据接收任务->启动数据采集
 *
 * @param  无
 * @return ESP_OK: 成功
 */
esp_err_t jfh142_init(void);

char *jfh142_get_heart_str(void);

char *jfh142_get_tired_str(void);

char *jfh142_get_o2_str(void);

char *jfh142_get_bk_str(void);

#endif // _JFH142_H_