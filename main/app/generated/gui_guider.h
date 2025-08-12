/*
* Copyright 2025 NXP
* NXP Proprietary. This software is owned or controlled by NXP and may only be used strictly in
* accordance with the applicable license terms. By expressly accepting such terms or by downloading, installing,
* activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to
* comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license
* terms, then you may not retain, install, activate or otherwise use the software.
*/

#ifndef GUI_GUIDER_H
#define GUI_GUIDER_H
#ifdef __cplusplus
extern "C" {
#endif

#include "lvgl.h"

typedef struct
{
  
	lv_obj_t *screen_main;
	bool screen_main_del;
	lv_obj_t *screen_main_canvas_direct;
	lv_obj_t *screen_main_img_pointer;
	lv_obj_t *screen_main_label_weather_temp;
	lv_obj_t *screen_main_img_ine_1;
	lv_obj_t *screen_main_label_weather;
	lv_obj_t *screen_main_cont_2;
	lv_obj_t *screen_main_carousel_2;
	lv_obj_t *screen_main_carousel_2_element_1;
	lv_obj_t *screen_main_carousel_2_element_2;
	lv_obj_t *screen_main_carousel_2_element_3;
	lv_obj_t *screen_main_img_1;
	lv_obj_t *screen_main_img_Wallpaper_2;
	lv_obj_t *screen_main_img_wallpaper_3;
	lv_obj_t *screen_main_canvas_time_bg;
	lv_obj_t *screen_main_canvas_cnt_bg;
	lv_obj_t *screen_main_label_cnt;
	lv_obj_t *screen_main_label_time;
	lv_obj_t *screen_main_label_time_sec;
	lv_obj_t *screen_main_label_date;
	lv_obj_t *screen_main_img_4;
	lv_obj_t *screen_main_line_1;
	lv_obj_t *screen_main_cont_3;
	lv_obj_t *screen_main_carousel_1;
	lv_obj_t *screen_main_carousel_1_element_1;
	lv_obj_t *screen_main_carousel_1_element_2;
	lv_obj_t *screen_main_cont_1;
	lv_obj_t *screen_main_img_line_2;
	lv_obj_t *screen_main_label_pressure_value;
	lv_obj_t *screen_main_label_step_cnt;
	lv_obj_t *screen_main_label_pressure;
	lv_obj_t *screen_main_img_step;
	lv_obj_t *screen_main_label_week;
	lv_obj_t *screen_main_label_heart_cnt;
	lv_obj_t *screen_main_img_heart;
	lv_obj_t *screen_main_label_heart;
	lv_obj_t *screen_main_img_pressure;
	lv_obj_t *screen_main_img_week;
	lv_obj_t *screen_main_canvas_2;
	lv_obj_t *screen_main_cont_4;
	lv_obj_t *screen_main_img_9;
	lv_obj_t *screen_main_label_hum;
	lv_obj_t *screen_main_label_wei;
	lv_obj_t *screen_main_img_wei;
	lv_obj_t *screen_main_label_temp;
	lv_obj_t *screen_main_label_o2;
	lv_obj_t *screen_main_img_7;
	lv_obj_t *screen_main_label_1;
	lv_obj_t *screen_main_img_hum;
	lv_obj_t *screen_main_img_temp;
	lv_obj_t *screen_main_canvas_3;
	lv_obj_t *screen_main_img_10;
	lv_obj_t *screen_main_img_11;
}lv_ui;

typedef void (*ui_setup_scr_t)(lv_ui * ui);

void ui_init_style(lv_style_t * style);

void ui_load_scr_animation(lv_ui *ui, lv_obj_t ** new_scr, bool new_scr_del, bool * old_scr_del, ui_setup_scr_t setup_scr,
                           lv_scr_load_anim_t anim_type, uint32_t time, uint32_t delay, bool is_clean, bool auto_del);

void ui_animation(void * var, int32_t duration, int32_t delay, int32_t start_value, int32_t end_value, lv_anim_path_cb_t path_cb,
                       uint16_t repeat_cnt, uint32_t repeat_delay, uint32_t playback_time, uint32_t playback_delay,
                       lv_anim_exec_xcb_t exec_cb, lv_anim_start_cb_t start_cb, lv_anim_ready_cb_t ready_cb, lv_anim_deleted_cb_t deleted_cb);


void init_scr_del_flag(lv_ui *ui);

void setup_ui(lv_ui *ui);

void init_keyboard(lv_ui *ui);

extern lv_ui guider_ui;


void setup_scr_screen_main(lv_ui *ui);
LV_IMG_DECLARE(_pointer2_15x15);
LV_IMG_DECLARE(_3304542_20230221171348882211_0_100x2);
LV_IMG_DECLARE(_5555_240x135);
LV_IMG_DECLARE(_222_240x135);
LV_IMG_DECLARE(_333_240x135);
LV_IMG_DECLARE(_date_15x15);
LV_IMG_DECLARE(_3304542_20230221171348882211_0_58x2);
LV_IMG_DECLARE(_step_23x20);
LV_IMG_DECLARE(_heart2_25x25);
LV_IMG_DECLARE(_tired_25x25);
LV_IMG_DECLARE(_week_25x25);
LV_IMG_DECLARE(_3304542_20230221171348882211_0_alpha_236x1);
LV_IMG_DECLARE(_3304542_20230221171348882211_0_alpha_238x1);
LV_IMG_DECLARE(_3304542_20230221171348882211_0_alpha_238x1);
LV_IMG_DECLARE(_3304542_20230221171348882211_0_58x2);
LV_IMG_DECLARE(_wei_22x22);
LV_IMG_DECLARE(_o2_21x20);
LV_IMG_DECLARE(_hum_23x23);
LV_IMG_DECLARE(_temp_25x25);
LV_IMG_DECLARE(_3304542_20230221171348882211_0_alpha_236x1);
LV_IMG_DECLARE(_3304542_20230221171348882211_0_alpha_238x1);
LV_IMG_DECLARE(_3304542_20230221171348882211_0_alpha_238x1);
LV_IMG_DECLARE(_power2_20x20);
LV_IMG_DECLARE(_bt_20x20);

LV_FONT_DECLARE(lv_font_sun_16)
LV_FONT_DECLARE(lv_font_montserratMedium_16)
LV_FONT_DECLARE(lv_font_arial_16)
LV_FONT_DECLARE(lv_font_sun_32)
LV_FONT_DECLARE(lv_font_sun_14)
LV_FONT_DECLARE(lv_font_montserratMedium_12)


#ifdef __cplusplus
}
#endif
#endif
