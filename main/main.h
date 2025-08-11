#ifndef _MAIN_H_
#define _MAIN_H_

#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "aht20.h"
#include "qmc5883l.h"
#include "bmp280.h"
#include "mpu6050_api.h"
#include "jfh142.h"
#include "app.h"
#include "mrtc.h"
#include "ble_time_sync.h"


#define LOG_LOCAL_LEVEL ESP_LOG_DEBUG
// 定义宏函数，用于检查函数返回值
#define CHEKRET(ret, func_name)                         \
    if ((ret) != ESP_OK)                                \
    {                                                   \
        ESP_LOGE("MAIN", "%s 初始化失败", (func_name)); \
        return;                                         \
    }

#endif // _MAIN_H_