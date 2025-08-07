#ifndef _LCD_COMMON_H_
#define _LCD_COMMON_H_

#include "esp_log.h"
#include "lvgl/lvgl.h"
#include "st7789v.h"
#include "esp_timer.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

void ui_task(void *arg);

#endif // _LCD_COMMON_H_