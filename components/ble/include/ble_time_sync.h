#ifndef BLE_TIME_SYNC_H
#define BLE_TIME_SYNC_H

#include <stdint.h>
#include <stdbool.h>
#include "esp_err.h"



// 初始化蓝牙（返回 ESP_OK 表示成功）
esp_err_t ble_init(void);

// 获取当前连接状态（true 表示已连接）
bool ble_is_connected(void);

void ble_adv_config(const char *device_name);

esp_err_t ble_time_sync_init(const char *device_name);

#endif // BLE_TIME_SYNC_H
    