/*
* Copyright 2025 NXP
* NXP Proprietary. This software is owned or controlled by NXP and may only be used strictly in
* accordance with the applicable license terms. By expressly accepting such terms or by downloading, installing,
* activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to
* comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license
* terms, then you may not retain, install, activate or otherwise use the software.
*/

#include "lvgl.h"
#include <stdio.h>
#include "gui_guider.h"
#include "events_init.h"
#include "widgets_init.h"
#include "custom.h"



void setup_scr_screen_main(lv_ui *ui)
{
    //Write codes screen_main
    ui->screen_main = lv_obj_create(NULL);
    lv_obj_set_size(ui->screen_main, 240, 280);
    lv_obj_set_scrollbar_mode(ui->screen_main, LV_SCROLLBAR_MODE_AUTO);

    //Write style for screen_main, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_main, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_main, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_main, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_main_canvas_direct
    ui->screen_main_canvas_direct = lv_canvas_create(ui->screen_main);
    static lv_color_t buf_screen_main_canvas_direct[LV_CANVAS_BUF_SIZE_TRUE_COLOR_ALPHA(220, 30)];
    lv_canvas_set_buffer(ui->screen_main_canvas_direct, buf_screen_main_canvas_direct, 220, 30, LV_IMG_CF_TRUE_COLOR_ALPHA);
    lv_canvas_fill_bg(ui->screen_main_canvas_direct, lv_color_hex(0xffffff), 0);
    lv_obj_set_pos(ui->screen_main_canvas_direct, 10, 245);
    lv_obj_set_size(ui->screen_main_canvas_direct, 220, 30);
    lv_obj_set_scrollbar_mode(ui->screen_main_canvas_direct, LV_SCROLLBAR_MODE_OFF);

    //Write codes screen_main_img_pointer
    ui->screen_main_img_pointer = lv_img_create(ui->screen_main);
    lv_obj_add_flag(ui->screen_main_img_pointer, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->screen_main_img_pointer, &_pointer2_15x15);
    lv_img_set_pivot(ui->screen_main_img_pointer, 0,0);
    lv_img_set_angle(ui->screen_main_img_pointer, 450);
    lv_obj_set_pos(ui->screen_main_img_pointer, 120, 260);
    lv_obj_set_size(ui->screen_main_img_pointer, 15, 15);

    //Write style for screen_main_img_pointer, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->screen_main_img_pointer, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->screen_main_img_pointer, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_main_img_pointer, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->screen_main_img_pointer, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_main_label_step_cnt
    ui->screen_main_label_step_cnt = lv_label_create(ui->screen_main);
    lv_label_set_text(ui->screen_main_label_step_cnt, "4434");
    lv_label_set_long_mode(ui->screen_main_label_step_cnt, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->screen_main_label_step_cnt, 37, 216);
    lv_obj_set_size(ui->screen_main_label_step_cnt, 45, 22);

    //Write style for screen_main_label_step_cnt, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_main_label_step_cnt, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_main_label_step_cnt, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_main_label_step_cnt, lv_color_hex(0xffd5f2), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_main_label_step_cnt, &lv_font_sun_14, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_main_label_step_cnt, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_main_label_step_cnt, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_main_label_step_cnt, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_main_label_step_cnt, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_main_label_step_cnt, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_main_label_step_cnt, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_main_label_step_cnt, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_main_label_step_cnt, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_main_label_step_cnt, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_main_label_step_cnt, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_main_label_pressure
    ui->screen_main_label_pressure = lv_label_create(ui->screen_main);
    lv_label_set_text(ui->screen_main_label_pressure, "疲劳度");
    lv_label_set_long_mode(ui->screen_main_label_pressure, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->screen_main_label_pressure, 118, 220);
    lv_obj_set_size(ui->screen_main_label_pressure, 49, 16);

    //Write style for screen_main_label_pressure, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_main_label_pressure, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_main_label_pressure, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_main_label_pressure, lv_color_hex(0xf2f1f1), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_main_label_pressure, &lv_font_sun_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_main_label_pressure, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_main_label_pressure, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_main_label_pressure, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_main_label_pressure, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_main_label_pressure, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_main_label_pressure, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_main_label_pressure, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_main_label_pressure, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_main_label_pressure, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_main_label_pressure, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_main_img_step
    ui->screen_main_img_step = lv_img_create(ui->screen_main);
    lv_obj_add_flag(ui->screen_main_img_step, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->screen_main_img_step, &_step_20x20);
    lv_img_set_pivot(ui->screen_main_img_step, 50,50);
    lv_img_set_angle(ui->screen_main_img_step, 0);
    lv_obj_set_pos(ui->screen_main_img_step, 17, 219);
    lv_obj_set_size(ui->screen_main_img_step, 20, 20);

    //Write style for screen_main_img_step, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->screen_main_img_step, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->screen_main_img_step, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_main_img_step, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->screen_main_img_step, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_main_label_week
    ui->screen_main_label_week = lv_label_create(ui->screen_main);
    lv_label_set_text(ui->screen_main_label_week, "星期五");
    lv_label_set_long_mode(ui->screen_main_label_week, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->screen_main_label_week, 139, 196);
    lv_obj_set_size(ui->screen_main_label_week, 55, 16);

    //Write style for screen_main_label_week, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_main_label_week, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_main_label_week, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_main_label_week, lv_color_hex(0xf2f1f1), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_main_label_week, &lv_font_sun_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_main_label_week, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_main_label_week, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_main_label_week, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_main_label_week, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_main_label_week, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_main_label_week, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_main_label_week, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_main_label_week, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_main_label_week, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_main_label_week, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_main_label_heart_cnt
    ui->screen_main_label_heart_cnt = lv_label_create(ui->screen_main);
    lv_label_set_text(ui->screen_main_label_heart_cnt, "100");
    lv_label_set_long_mode(ui->screen_main_label_heart_cnt, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->screen_main_label_heart_cnt, 81, 192);
    lv_obj_set_size(ui->screen_main_label_heart_cnt, 45, 22);

    //Write style for screen_main_label_heart_cnt, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_main_label_heart_cnt, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_main_label_heart_cnt, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_main_label_heart_cnt, lv_color_hex(0xffd5f2), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_main_label_heart_cnt, &lv_font_sun_14, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_main_label_heart_cnt, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_main_label_heart_cnt, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_main_label_heart_cnt, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_main_label_heart_cnt, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_main_label_heart_cnt, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_main_label_heart_cnt, 6, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_main_label_heart_cnt, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_main_label_heart_cnt, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_main_label_heart_cnt, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_main_label_heart_cnt, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_main_img_heart
    ui->screen_main_img_heart = lv_img_create(ui->screen_main);
    lv_obj_add_flag(ui->screen_main_img_heart, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->screen_main_img_heart, &_heat_25x25);
    lv_img_set_pivot(ui->screen_main_img_heart, 50,50);
    lv_img_set_angle(ui->screen_main_img_heart, 0);
    lv_obj_set_pos(ui->screen_main_img_heart, 64, 192);
    lv_obj_set_size(ui->screen_main_img_heart, 25, 25);

    //Write style for screen_main_img_heart, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->screen_main_img_heart, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->screen_main_img_heart, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_main_img_heart, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->screen_main_img_heart, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_main_label_heart
    ui->screen_main_label_heart = lv_label_create(ui->screen_main);
    lv_label_set_text(ui->screen_main_label_heart, "当前心率");
    lv_label_set_long_mode(ui->screen_main_label_heart, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->screen_main_label_heart, 0, 192);
    lv_obj_set_size(ui->screen_main_label_heart, 65, 22);

    //Write style for screen_main_label_heart, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_main_label_heart, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_main_label_heart, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_main_label_heart, lv_color_hex(0xffd5f2), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_main_label_heart, &lv_font_sun_14, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_main_label_heart, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_main_label_heart, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_main_label_heart, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_main_label_heart, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_main_label_heart, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_main_label_heart, 6, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_main_label_heart, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_main_label_heart, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_main_label_heart, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_main_label_heart, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_main_img_pressure
    ui->screen_main_img_pressure = lv_img_create(ui->screen_main);
    lv_obj_add_flag(ui->screen_main_img_pressure, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->screen_main_img_pressure, &_icon_wx_25x25);
    lv_img_set_pivot(ui->screen_main_img_pressure, 50,50);
    lv_img_set_angle(ui->screen_main_img_pressure, 0);
    lv_obj_set_pos(ui->screen_main_img_pressure, 171, 215);
    lv_obj_set_size(ui->screen_main_img_pressure, 25, 25);

    //Write style for screen_main_img_pressure, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->screen_main_img_pressure, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->screen_main_img_pressure, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_main_img_pressure, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->screen_main_img_pressure, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_main_img_line_2
    ui->screen_main_img_line_2 = lv_img_create(ui->screen_main);
    lv_obj_add_flag(ui->screen_main_img_line_2, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->screen_main_img_line_2, &_3304542_20230221171348882211_0_58x2);
    lv_img_set_pivot(ui->screen_main_img_line_2, 0,0);
    lv_img_set_angle(ui->screen_main_img_line_2, 1220);
    lv_obj_set_pos(ui->screen_main_img_line_2, 135, 191);
    lv_obj_set_size(ui->screen_main_img_line_2, 58, 2);

    //Write style for screen_main_img_line_2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->screen_main_img_line_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->screen_main_img_line_2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_main_img_line_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->screen_main_img_line_2, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_main_img_week
    ui->screen_main_img_week = lv_img_create(ui->screen_main);
    lv_obj_add_flag(ui->screen_main_img_week, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->screen_main_img_week, &_week_25x25);
    lv_img_set_pivot(ui->screen_main_img_week, 50,50);
    lv_img_set_angle(ui->screen_main_img_week, 0);
    lv_obj_set_pos(ui->screen_main_img_week, 201, 191);
    lv_obj_set_size(ui->screen_main_img_week, 25, 25);

    //Write style for screen_main_img_week, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->screen_main_img_week, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->screen_main_img_week, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_main_img_week, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->screen_main_img_week, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_main_label_pressure_value
    ui->screen_main_label_pressure_value = lv_label_create(ui->screen_main);
    lv_label_set_text(ui->screen_main_label_pressure_value, "100\n");
    lv_label_set_long_mode(ui->screen_main_label_pressure_value, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->screen_main_label_pressure_value, 194, 219);
    lv_obj_set_size(ui->screen_main_label_pressure_value, 40, 16);

    //Write style for screen_main_label_pressure_value, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_main_label_pressure_value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_main_label_pressure_value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_main_label_pressure_value, lv_color_hex(0xf2f1f1), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_main_label_pressure_value, &lv_font_sun_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_main_label_pressure_value, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_main_label_pressure_value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_main_label_pressure_value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_main_label_pressure_value, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_main_label_pressure_value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_main_label_pressure_value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_main_label_pressure_value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_main_label_pressure_value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_main_label_pressure_value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_main_label_pressure_value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_main_canvas_2
    ui->screen_main_canvas_2 = lv_canvas_create(ui->screen_main);
    static lv_color_t buf_screen_main_canvas_2[LV_CANVAS_BUF_SIZE_TRUE_COLOR_ALPHA(240, 51)];
    lv_canvas_set_buffer(ui->screen_main_canvas_2, buf_screen_main_canvas_2, 240, 51, LV_IMG_CF_TRUE_COLOR_ALPHA);
    lv_canvas_fill_bg(ui->screen_main_canvas_2, lv_color_hex(0xffffff), 0);
    //Canvas draw image
    lv_draw_img_dsc_t screen_main_canvas_2_img_dsc_0;
    lv_draw_img_dsc_init(&screen_main_canvas_2_img_dsc_0);
    lv_canvas_draw_img(ui->screen_main_canvas_2, 2, 1, &_3304542_20230221171348882211_0_alpha_236x1, &screen_main_canvas_2_img_dsc_0);

    //Canvas draw image
    lv_draw_img_dsc_t screen_main_canvas_2_img_dsc_1;
    lv_draw_img_dsc_init(&screen_main_canvas_2_img_dsc_1);
    lv_canvas_draw_img(ui->screen_main_canvas_2, 2, 26, &_3304542_20230221171348882211_0_alpha_238x1, &screen_main_canvas_2_img_dsc_1);

    //Canvas draw image
    lv_draw_img_dsc_t screen_main_canvas_2_img_dsc_2;
    lv_draw_img_dsc_init(&screen_main_canvas_2_img_dsc_2);
    lv_canvas_draw_img(ui->screen_main_canvas_2, 2, 50, &_3304542_20230221171348882211_0_alpha_238x1, &screen_main_canvas_2_img_dsc_2);

    lv_obj_set_pos(ui->screen_main_canvas_2, 0, 190);
    lv_obj_set_size(ui->screen_main_canvas_2, 240, 51);
    lv_obj_set_scrollbar_mode(ui->screen_main_canvas_2, LV_SCROLLBAR_MODE_OFF);

    //Write codes screen_main_canvas_1
    ui->screen_main_canvas_1 = lv_canvas_create(ui->screen_main);
    static lv_color_t buf_screen_main_canvas_1[LV_CANVAS_BUF_SIZE_TRUE_COLOR_ALPHA(240, 38)];
    lv_canvas_set_buffer(ui->screen_main_canvas_1, buf_screen_main_canvas_1, 240, 38, LV_IMG_CF_TRUE_COLOR_ALPHA);
    lv_canvas_fill_bg(ui->screen_main_canvas_1, lv_color_hex(0xffffff), 0);
    //Canvas draw line
    static lv_point_t screen_main_canvas_1_points_array_0[] = {{1, 36},{240, 36},};
    lv_draw_line_dsc_t screen_main_canvas_1_line_dsc_0;
    lv_draw_line_dsc_init(&screen_main_canvas_1_line_dsc_0);
    screen_main_canvas_1_line_dsc_0.color = lv_color_hex(0x0039ff);
    screen_main_canvas_1_line_dsc_0.opa = 255;
    screen_main_canvas_1_line_dsc_0.width = 0;
    screen_main_canvas_1_line_dsc_0.round_start = false;
    screen_main_canvas_1_line_dsc_0.round_end = false;
    lv_canvas_draw_line(ui->screen_main_canvas_1, screen_main_canvas_1_points_array_0, 2, &screen_main_canvas_1_line_dsc_0);

    //Canvas draw line
    static lv_point_t screen_main_canvas_1_points_array_1[] = {{120, 4},{120, 30},};
    lv_draw_line_dsc_t screen_main_canvas_1_line_dsc_1;
    lv_draw_line_dsc_init(&screen_main_canvas_1_line_dsc_1);
    screen_main_canvas_1_line_dsc_1.color = lv_color_hex(0xa44040);
    screen_main_canvas_1_line_dsc_1.opa = 194;
    screen_main_canvas_1_line_dsc_1.width = 1;
    screen_main_canvas_1_line_dsc_1.round_start = false;
    screen_main_canvas_1_line_dsc_1.round_end = false;
    lv_canvas_draw_line(ui->screen_main_canvas_1, screen_main_canvas_1_points_array_1, 2, &screen_main_canvas_1_line_dsc_1);

    lv_obj_set_pos(ui->screen_main_canvas_1, 0, 0);
    lv_obj_set_size(ui->screen_main_canvas_1, 240, 38);
    lv_obj_set_scrollbar_mode(ui->screen_main_canvas_1, LV_SCROLLBAR_MODE_OFF);

    //Write codes screen_main_img_temp
    ui->screen_main_img_temp = lv_img_create(ui->screen_main);
    lv_obj_add_flag(ui->screen_main_img_temp, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->screen_main_img_temp, &_temp_15x15);
    lv_img_set_pivot(ui->screen_main_img_temp, 50,50);
    lv_img_set_angle(ui->screen_main_img_temp, 0);
    lv_obj_set_pos(ui->screen_main_img_temp, 129, 12);
    lv_obj_set_size(ui->screen_main_img_temp, 15, 15);

    //Write style for screen_main_img_temp, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->screen_main_img_temp, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->screen_main_img_temp, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_main_img_temp, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->screen_main_img_temp, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_main_label_temp
    ui->screen_main_label_temp = lv_label_create(ui->screen_main);
    lv_label_set_text(ui->screen_main_label_temp, "32");
    lv_label_set_long_mode(ui->screen_main_label_temp, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->screen_main_label_temp, 145, 14);
    lv_obj_set_size(ui->screen_main_label_temp, 23, 15);

    //Write style for screen_main_label_temp, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_main_label_temp, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_main_label_temp, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_main_label_temp, lv_color_hex(0x9aedf6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_main_label_temp, &lv_font_sun_14, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_main_label_temp, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_main_label_temp, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_main_label_temp, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_main_label_temp, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_main_label_temp, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_main_label_temp, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_main_label_temp, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_main_label_temp, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_main_label_temp, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_main_label_temp, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_main_label_humi
    ui->screen_main_label_humi = lv_label_create(ui->screen_main);
    lv_label_set_text(ui->screen_main_label_humi, "50%");
    lv_label_set_long_mode(ui->screen_main_label_humi, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->screen_main_label_humi, 189, 14);
    lv_obj_set_size(ui->screen_main_label_humi, 44, 15);

    //Write style for screen_main_label_humi, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_main_label_humi, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_main_label_humi, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_main_label_humi, lv_color_hex(0x9aedf6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_main_label_humi, &lv_font_sun_14, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_main_label_humi, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_main_label_humi, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_main_label_humi, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_main_label_humi, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_main_label_humi, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_main_label_humi, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_main_label_humi, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_main_label_humi, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_main_label_humi, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_main_label_humi, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_main_img_humi
    ui->screen_main_img_humi = lv_img_create(ui->screen_main);
    lv_obj_add_flag(ui->screen_main_img_humi, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->screen_main_img_humi, &_hum_15x14);
    lv_img_set_pivot(ui->screen_main_img_humi, 50,50);
    lv_img_set_angle(ui->screen_main_img_humi, 0);
    lv_obj_set_pos(ui->screen_main_img_humi, 175, 13);
    lv_obj_set_size(ui->screen_main_img_humi, 15, 14);

    //Write style for screen_main_img_humi, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->screen_main_img_humi, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->screen_main_img_humi, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_main_img_humi, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->screen_main_img_humi, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_main_img_1
    ui->screen_main_img_1 = lv_img_create(ui->screen_main);
    lv_obj_add_flag(ui->screen_main_img_1, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->screen_main_img_1, &_222_240x135);
    lv_img_set_pivot(ui->screen_main_img_1, 50,50);
    lv_img_set_angle(ui->screen_main_img_1, 0);
    lv_obj_set_pos(ui->screen_main_img_1, 0, 39);
    lv_obj_set_size(ui->screen_main_img_1, 240, 135);

    //Write style for screen_main_img_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->screen_main_img_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->screen_main_img_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_main_img_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->screen_main_img_1, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_main_canvas_time_bg
    ui->screen_main_canvas_time_bg = lv_canvas_create(ui->screen_main);
    static lv_color_t buf_screen_main_canvas_time_bg[LV_CANVAS_BUF_SIZE_TRUE_COLOR_ALPHA(140, 15)];
    lv_canvas_set_buffer(ui->screen_main_canvas_time_bg, buf_screen_main_canvas_time_bg, 140, 15, LV_IMG_CF_TRUE_COLOR_ALPHA);
    lv_canvas_fill_bg(ui->screen_main_canvas_time_bg, lv_color_hex(0xffffff), 0);
    //Canvas draw polygon
    static lv_point_t screen_main_canvas_time_bg_points_array_0[] = {{25, 0},{0, 40},{140, 40},{140, 0},};
    lv_draw_rect_dsc_t screen_main_canvas_time_bg_rect_dsc_0;
    lv_draw_rect_dsc_init(&screen_main_canvas_time_bg_rect_dsc_0);
    screen_main_canvas_time_bg_rect_dsc_0.radius = 0;
    screen_main_canvas_time_bg_rect_dsc_0.bg_opa = 255;
    screen_main_canvas_time_bg_rect_dsc_0.bg_color = lv_color_hex(0x000000);
    screen_main_canvas_time_bg_rect_dsc_0.bg_grad.dir = LV_GRAD_DIR_NONE;
    screen_main_canvas_time_bg_rect_dsc_0.border_width = 0;
    screen_main_canvas_time_bg_rect_dsc_0.border_opa = 255;
    screen_main_canvas_time_bg_rect_dsc_0.border_color = lv_color_hex(0x000000);
    lv_canvas_draw_polygon(ui->screen_main_canvas_time_bg, screen_main_canvas_time_bg_points_array_0, 4, &screen_main_canvas_time_bg_rect_dsc_0);

    lv_obj_set_pos(ui->screen_main_canvas_time_bg, 100, 159);
    lv_obj_set_size(ui->screen_main_canvas_time_bg, 140, 15);
    lv_obj_set_scrollbar_mode(ui->screen_main_canvas_time_bg, LV_SCROLLBAR_MODE_OFF);

    //Write codes screen_main_label_weather_temp
    ui->screen_main_label_weather_temp = lv_label_create(ui->screen_main);
    lv_label_set_text(ui->screen_main_label_weather_temp, "32℃");
    lv_label_set_long_mode(ui->screen_main_label_weather_temp, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->screen_main_label_weather_temp, 0, 0);
    lv_obj_set_size(ui->screen_main_label_weather_temp, 60, 38);

    //Write style for screen_main_label_weather_temp, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_main_label_weather_temp, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_main_label_weather_temp, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_main_label_weather_temp, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_main_label_weather_temp, &lv_font_sun_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_main_label_weather_temp, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_main_label_weather_temp, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_main_label_weather_temp, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_main_label_weather_temp, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_main_label_weather_temp, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_main_label_weather_temp, 15, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_main_label_weather_temp, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_main_label_weather_temp, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_main_label_weather_temp, 10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_main_label_weather_temp, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_main_img_ine_1
    ui->screen_main_img_ine_1 = lv_img_create(ui->screen_main);
    lv_obj_add_flag(ui->screen_main_img_ine_1, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->screen_main_img_ine_1, &_3304542_20230221171348882211_0_100x2);
    lv_img_set_pivot(ui->screen_main_img_ine_1, 50,50);
    lv_img_set_angle(ui->screen_main_img_ine_1, 0);
    lv_obj_set_pos(ui->screen_main_img_ine_1, 0, 38);
    lv_obj_set_size(ui->screen_main_img_ine_1, 100, 2);

    //Write style for screen_main_img_ine_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->screen_main_img_ine_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->screen_main_img_ine_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_main_img_ine_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->screen_main_img_ine_1, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_main_label_weather
    ui->screen_main_label_weather = lv_label_create(ui->screen_main);
    lv_label_set_text(ui->screen_main_label_weather, "阴天");
    lv_label_set_long_mode(ui->screen_main_label_weather, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->screen_main_label_weather, 60, 0);
    lv_obj_set_size(ui->screen_main_label_weather, 60, 38);

    //Write style for screen_main_label_weather, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_main_label_weather, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_main_label_weather, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_main_label_weather, lv_color_hex(0xfef7f7), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_main_label_weather, &lv_font_sun_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_main_label_weather, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_main_label_weather, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_main_label_weather, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_main_label_weather, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_main_label_weather, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_main_label_weather, 15, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_main_label_weather, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_main_label_weather, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_main_label_weather, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_main_label_weather, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_main_canvas_cnt_bg
    ui->screen_main_canvas_cnt_bg = lv_canvas_create(ui->screen_main);
    static lv_color_t buf_screen_main_canvas_cnt_bg[LV_CANVAS_BUF_SIZE_TRUE_COLOR_ALPHA(120, 20)];
    lv_canvas_set_buffer(ui->screen_main_canvas_cnt_bg, buf_screen_main_canvas_cnt_bg, 120, 20, LV_IMG_CF_TRUE_COLOR_ALPHA);
    lv_canvas_fill_bg(ui->screen_main_canvas_cnt_bg, lv_color_hex(0xffffff), 0);
    //Canvas draw polygon
    static lv_point_t screen_main_canvas_cnt_bg_points_array_0[] = {{0, 0},{100, 0},{80, 20},{0, 20},};
    lv_draw_rect_dsc_t screen_main_canvas_cnt_bg_rect_dsc_0;
    lv_draw_rect_dsc_init(&screen_main_canvas_cnt_bg_rect_dsc_0);
    screen_main_canvas_cnt_bg_rect_dsc_0.radius = 0;
    screen_main_canvas_cnt_bg_rect_dsc_0.bg_opa = 255;
    screen_main_canvas_cnt_bg_rect_dsc_0.bg_color = lv_color_hex(0x000000);
    screen_main_canvas_cnt_bg_rect_dsc_0.bg_grad.dir = LV_GRAD_DIR_NONE;
    screen_main_canvas_cnt_bg_rect_dsc_0.border_width = 0;
    screen_main_canvas_cnt_bg_rect_dsc_0.border_opa = 255;
    screen_main_canvas_cnt_bg_rect_dsc_0.border_color = lv_color_hex(0x000000);
    lv_canvas_draw_polygon(ui->screen_main_canvas_cnt_bg, screen_main_canvas_cnt_bg_points_array_0, 4, &screen_main_canvas_cnt_bg_rect_dsc_0);

    lv_obj_set_pos(ui->screen_main_canvas_cnt_bg, 0, 39);
    lv_obj_set_size(ui->screen_main_canvas_cnt_bg, 120, 20);
    lv_obj_set_scrollbar_mode(ui->screen_main_canvas_cnt_bg, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui->screen_main_canvas_cnt_bg, LV_OBJ_FLAG_HIDDEN);

    //Write codes screen_main_label_cnt
    ui->screen_main_label_cnt = lv_label_create(ui->screen_main);
    lv_label_set_text(ui->screen_main_label_cnt, "< 1/3 >");
    lv_label_set_long_mode(ui->screen_main_label_cnt, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->screen_main_label_cnt, 4, 39);
    lv_obj_set_size(ui->screen_main_label_cnt, 80, 17);
    lv_obj_add_flag(ui->screen_main_label_cnt, LV_OBJ_FLAG_HIDDEN);

    //Write style for screen_main_label_cnt, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_main_label_cnt, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_main_label_cnt, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_main_label_cnt, lv_color_hex(0xefefef), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_main_label_cnt, &lv_font_arial_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_main_label_cnt, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_main_label_cnt, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_main_label_cnt, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_main_label_cnt, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_main_label_cnt, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_main_label_cnt, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_main_label_cnt, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_main_label_cnt, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_main_label_cnt, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_main_label_cnt, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_main_label_time
    ui->screen_main_label_time = lv_label_create(ui->screen_main);
    lv_label_set_text(ui->screen_main_label_time, "10:10");
    lv_label_set_long_mode(ui->screen_main_label_time, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->screen_main_label_time, 116, 162);
    lv_obj_set_size(ui->screen_main_label_time, 95, 32);

    //Write style for screen_main_label_time, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_main_label_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_main_label_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_main_label_time, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_main_label_time, &lv_font_sun_32, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_main_label_time, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_main_label_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_main_label_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_main_label_time, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_main_label_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_main_label_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_main_label_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_main_label_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_main_label_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_main_label_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_main_label_time_sec
    ui->screen_main_label_time_sec = lv_label_create(ui->screen_main);
    lv_label_set_text(ui->screen_main_label_time_sec, ": 50");
    lv_label_set_long_mode(ui->screen_main_label_time_sec, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->screen_main_label_time_sec, 208, 173);
    lv_obj_set_size(ui->screen_main_label_time_sec, 30, 14);

    //Write style for screen_main_label_time_sec, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_main_label_time_sec, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_main_label_time_sec, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_main_label_time_sec, lv_color_hex(0x67bb69), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_main_label_time_sec, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_main_label_time_sec, 253, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_main_label_time_sec, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_main_label_time_sec, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_main_label_time_sec, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_main_label_time_sec, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_main_label_time_sec, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_main_label_time_sec, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_main_label_time_sec, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_main_label_time_sec, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_main_label_time_sec, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_main_label_date
    ui->screen_main_label_date = lv_label_create(ui->screen_main);
    lv_label_set_text(ui->screen_main_label_date, "2025/08/08");
    lv_label_set_long_mode(ui->screen_main_label_date, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->screen_main_label_date, 12, 175);
    lv_obj_set_size(ui->screen_main_label_date, 111, 17);

    //Write style for screen_main_label_date, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_main_label_date, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_main_label_date, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_main_label_date, lv_color_hex(0xf3f3f3), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_main_label_date, &lv_font_sun_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_main_label_date, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_main_label_date, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_main_label_date, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_main_label_date, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_main_label_date, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_main_label_date, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_main_label_date, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_main_label_date, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_main_label_date, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_main_label_date, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_main_img_4
    ui->screen_main_img_4 = lv_img_create(ui->screen_main);
    lv_obj_add_flag(ui->screen_main_img_4, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->screen_main_img_4, &_date_15x15);
    lv_img_set_pivot(ui->screen_main_img_4, 50,50);
    lv_img_set_angle(ui->screen_main_img_4, 0);
    lv_obj_set_pos(ui->screen_main_img_4, 6, 176);
    lv_obj_set_size(ui->screen_main_img_4, 15, 15);

    //Write style for screen_main_img_4, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->screen_main_img_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->screen_main_img_4, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_main_img_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->screen_main_img_4, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //The custom code of screen_main.


    //Update current screen layout.
    lv_obj_update_layout(ui->screen_main);

}
