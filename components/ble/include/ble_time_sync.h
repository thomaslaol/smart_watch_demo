#ifndef BLE_TIME_SYNC_H
#define BLE_TIME_SYNC_H

#include <stdint.h>
#include <stdbool.h>
#include "esp_err.h"

/**
 * 获取当前蓝牙连接状态
 */
bool ble_is_connected(void);

/**
 * @brief 蓝牙初始化入口函数
 *
 * @note 初始化顺序：NVS -> 时区 -> 蓝牙控制器 -> Bluedroid -> GAP 回调 -> GATT 回调 -> GATT 应用 -> 广播配置
 *
 * @param device_name 设备名称
 * @return ESP_OK 成功，其他失败
 */
esp_err_t ble_time_sync_init(const char *device_name);

#endif // BLE_TIME_SYNC_H
