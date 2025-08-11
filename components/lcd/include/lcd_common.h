#ifndef _LCD_COMMON_H_
#define _LCD_COMMON_H_

#include "esp_log.h"
#include "lvgl/lvgl.h"
#include "st7789v.h"
#include "esp_timer.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"

extern lv_indev_t *touch_indev;
extern lv_indev_data_t touch_data;
extern SemaphoreHandle_t touch_mutex; 

#endif // _LCD_COMMON_H_