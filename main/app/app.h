#ifndef _APP_H_
#define _APP_H_

#include "esp_err.h"

/**
 * @brief 应用层初始化函数
 *
 * 初始化lvgl，包括屏幕、双缓存、显示驱动、触摸设备、时间基准和 LVGL 任务
 *
 * 初始化成功后，自动启动 LVGL 任务
 *
 * @param  void
 */
esp_err_t app_init(void);

#endif // _APP_H_