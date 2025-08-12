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

    //Write codes screen_main_label_weather_temp
    ui->screen_main_label_weather_temp = lv_label_create(ui->screen_main);
    lv_label_set_text(ui->screen_main_label_weather_temp, "32℃");
    lv_label_set_long_mode(ui->screen_main_label_weather_temp, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->screen_main_label_weather_temp, 10, 14);
    lv_obj_set_size(ui->screen_main_label_weather_temp, 49, 17);

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
    lv_obj_set_style_pad_top(ui->screen_main_label_weather_temp, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_main_label_weather_temp, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_main_label_weather_temp, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_main_label_weather_temp, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
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
    lv_obj_set_pos(ui->screen_main_label_weather, 64, 13);
    lv_obj_set_size(ui->screen_main_label_weather, 44, 17);

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
    lv_obj_set_style_pad_top(ui->screen_main_label_weather, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_main_label_weather, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_main_label_weather, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_main_label_weather, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_main_label_weather, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_main_cont_2
    ui->screen_main_cont_2 = lv_obj_create(ui->screen_main);
    lv_obj_set_pos(ui->screen_main_cont_2, 0, 39);
    lv_obj_set_size(ui->screen_main_cont_2, 240, 152);
    lv_obj_set_scrollbar_mode(ui->screen_main_cont_2, LV_SCROLLBAR_MODE_OFF);

    //Write style for screen_main_cont_2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_main_cont_2, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->screen_main_cont_2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->screen_main_cont_2, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->screen_main_cont_2, LV_BORDER_SIDE_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_main_cont_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_main_cont_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_main_cont_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_main_cont_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_main_cont_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_main_cont_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_main_cont_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_main_carousel_2
    ui->screen_main_carousel_2 = lv_carousel_create(ui->screen_main_cont_2);
    lv_carousel_set_element_width(ui->screen_main_carousel_2, 240);
    lv_obj_set_size(ui->screen_main_carousel_2, 240, 135);
    ui->screen_main_carousel_2_element_1 = lv_carousel_add_element(ui->screen_main_carousel_2, 0);
    ui->screen_main_carousel_2_element_2 = lv_carousel_add_element(ui->screen_main_carousel_2, 1);
    ui->screen_main_carousel_2_element_3 = lv_carousel_add_element(ui->screen_main_carousel_2, 2);
    lv_obj_set_pos(ui->screen_main_carousel_2, 0, 0);
    lv_obj_set_size(ui->screen_main_carousel_2, 240, 135);
    lv_obj_set_scrollbar_mode(ui->screen_main_carousel_2, LV_SCROLLBAR_MODE_OFF);

    //Write style for screen_main_carousel_2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_main_carousel_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_main_carousel_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_main_carousel_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for screen_main_carousel_2, Part: LV_PART_SCROLLBAR, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_main_carousel_2, 0, LV_PART_SCROLLBAR|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_main_carousel_2, 0, LV_PART_SCROLLBAR|LV_STATE_DEFAULT);

    //Write style state: LV_STATE_DEFAULT for &style_screen_main_carousel_2_extra_element_items_default
    static lv_style_t style_screen_main_carousel_2_extra_element_items_default;
    ui_init_style(&style_screen_main_carousel_2_extra_element_items_default);

    lv_style_set_bg_opa(&style_screen_main_carousel_2_extra_element_items_default, 0);
    lv_style_set_outline_width(&style_screen_main_carousel_2_extra_element_items_default, 0);
    lv_style_set_border_width(&style_screen_main_carousel_2_extra_element_items_default, 0);
    lv_style_set_radius(&style_screen_main_carousel_2_extra_element_items_default, 5);
    lv_style_set_shadow_width(&style_screen_main_carousel_2_extra_element_items_default, 0);
    lv_obj_add_style(ui->screen_main_carousel_2_element_3, &style_screen_main_carousel_2_extra_element_items_default, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_add_style(ui->screen_main_carousel_2_element_2, &style_screen_main_carousel_2_extra_element_items_default, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_add_style(ui->screen_main_carousel_2_element_1, &style_screen_main_carousel_2_extra_element_items_default, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style state: LV_STATE_FOCUSED for &style_screen_main_carousel_2_extra_element_items_focused
    static lv_style_t style_screen_main_carousel_2_extra_element_items_focused;
    ui_init_style(&style_screen_main_carousel_2_extra_element_items_focused);

    lv_style_set_bg_opa(&style_screen_main_carousel_2_extra_element_items_focused, 0);
    lv_style_set_outline_width(&style_screen_main_carousel_2_extra_element_items_focused, 0);
    lv_style_set_border_width(&style_screen_main_carousel_2_extra_element_items_focused, 0);
    lv_style_set_radius(&style_screen_main_carousel_2_extra_element_items_focused, 5);
    lv_style_set_shadow_width(&style_screen_main_carousel_2_extra_element_items_focused, 0);
    lv_obj_add_style(ui->screen_main_carousel_2_element_3, &style_screen_main_carousel_2_extra_element_items_focused, LV_PART_MAIN|LV_STATE_FOCUSED);
    lv_obj_add_style(ui->screen_main_carousel_2_element_2, &style_screen_main_carousel_2_extra_element_items_focused, LV_PART_MAIN|LV_STATE_FOCUSED);
    lv_obj_add_style(ui->screen_main_carousel_2_element_1, &style_screen_main_carousel_2_extra_element_items_focused, LV_PART_MAIN|LV_STATE_FOCUSED);



    //Write codes screen_main_img_1
    ui->screen_main_img_1 = lv_img_create(ui->screen_main_carousel_2_element_1);
    lv_obj_add_flag(ui->screen_main_img_1, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->screen_main_img_1, &_5555_240x135);
    lv_img_set_pivot(ui->screen_main_img_1, 50,50);
    lv_img_set_angle(ui->screen_main_img_1, 0);
    lv_obj_set_pos(ui->screen_main_img_1, 0, 0);
    lv_obj_set_size(ui->screen_main_img_1, 240, 135);

    //Write style for screen_main_img_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->screen_main_img_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->screen_main_img_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_main_img_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->screen_main_img_1, true, LV_PART_MAIN|LV_STATE_DEFAULT);



    //Write codes screen_main_img_Wallpaper_2
    ui->screen_main_img_Wallpaper_2 = lv_img_create(ui->screen_main_carousel_2_element_2);
    lv_obj_add_flag(ui->screen_main_img_Wallpaper_2, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->screen_main_img_Wallpaper_2, &_222_240x135);
    lv_img_set_pivot(ui->screen_main_img_Wallpaper_2, 50,50);
    lv_img_set_angle(ui->screen_main_img_Wallpaper_2, 0);
    lv_obj_set_pos(ui->screen_main_img_Wallpaper_2, 0, 0);
    lv_obj_set_size(ui->screen_main_img_Wallpaper_2, 240, 135);

    //Write style for screen_main_img_Wallpaper_2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->screen_main_img_Wallpaper_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->screen_main_img_Wallpaper_2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_main_img_Wallpaper_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->screen_main_img_Wallpaper_2, true, LV_PART_MAIN|LV_STATE_DEFAULT);



    //Write codes screen_main_img_wallpaper_3
    ui->screen_main_img_wallpaper_3 = lv_img_create(ui->screen_main_carousel_2_element_3);
    lv_obj_add_flag(ui->screen_main_img_wallpaper_3, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->screen_main_img_wallpaper_3, &_333_240x135);
    lv_img_set_pivot(ui->screen_main_img_wallpaper_3, 50,50);
    lv_img_set_angle(ui->screen_main_img_wallpaper_3, 0);
    lv_obj_set_pos(ui->screen_main_img_wallpaper_3, 0, 0);
    lv_obj_set_size(ui->screen_main_img_wallpaper_3, 240, 135);

    //Write style for screen_main_img_wallpaper_3, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->screen_main_img_wallpaper_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->screen_main_img_wallpaper_3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_main_img_wallpaper_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->screen_main_img_wallpaper_3, true, LV_PART_MAIN|LV_STATE_DEFAULT);

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

    lv_obj_set_pos(ui->screen_main_canvas_time_bg, 100, 161);
    lv_obj_set_size(ui->screen_main_canvas_time_bg, 140, 15);
    lv_obj_set_scrollbar_mode(ui->screen_main_canvas_time_bg, LV_SCROLLBAR_MODE_OFF);

    //Write codes screen_main_canvas_cnt_bg
    // ui->screen_main_canvas_cnt_bg = lv_canvas_create(ui->screen_main);
    // static lv_color_t buf_screen_main_canvas_cnt_bg[LV_CANVAS_BUF_SIZE_TRUE_COLOR_ALPHA(120, 18)];
    // lv_canvas_set_buffer(ui->screen_main_canvas_cnt_bg, buf_screen_main_canvas_cnt_bg, 120, 18, LV_IMG_CF_TRUE_COLOR_ALPHA);
    // lv_canvas_fill_bg(ui->screen_main_canvas_cnt_bg, lv_color_hex(0xffffff), 0);
    //Canvas draw polygon
    // static lv_point_t screen_main_canvas_cnt_bg_points_array_0[] = {{0, 0},{100, 0},{80, 20},{0, 20},};
    // lv_draw_rect_dsc_t screen_main_canvas_cnt_bg_rect_dsc_0;
    // lv_draw_rect_dsc_init(&screen_main_canvas_cnt_bg_rect_dsc_0);
    // screen_main_canvas_cnt_bg_rect_dsc_0.radius = 0;
    // screen_main_canvas_cnt_bg_rect_dsc_0.bg_opa = 255;
    // screen_main_canvas_cnt_bg_rect_dsc_0.bg_color = lv_color_hex(0x000000);
    // screen_main_canvas_cnt_bg_rect_dsc_0.bg_grad.dir = LV_GRAD_DIR_NONE;
    // screen_main_canvas_cnt_bg_rect_dsc_0.border_width = 0;
    // screen_main_canvas_cnt_bg_rect_dsc_0.border_opa = 255;
    // screen_main_canvas_cnt_bg_rect_dsc_0.border_color = lv_color_hex(0x000000);
    // lv_canvas_draw_polygon(ui->screen_main_canvas_cnt_bg, screen_main_canvas_cnt_bg_points_array_0, 4, &screen_main_canvas_cnt_bg_rect_dsc_0);

    // lv_obj_set_pos(ui->screen_main_canvas_cnt_bg, 0, 39);
    // lv_obj_set_size(ui->screen_main_canvas_cnt_bg, 120, 18);
    // lv_obj_set_scrollbar_mode(ui->screen_main_canvas_cnt_bg, LV_SCROLLBAR_MODE_OFF);
    // lv_obj_add_flag(ui->screen_main_canvas_cnt_bg, LV_OBJ_FLAG_HIDDEN);

    //Write codes screen_main_label_cnt
    ui->screen_main_label_cnt = lv_label_create(ui->screen_main);
    lv_label_set_text(ui->screen_main_label_cnt, "< 1/3 >");
    lv_label_set_long_mode(ui->screen_main_label_cnt, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->screen_main_label_cnt, 4, 38);
    lv_obj_set_size(ui->screen_main_label_cnt, 80, 15);
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
    lv_label_set_text(ui->screen_main_label_time_sec, ":50");
    lv_label_set_long_mode(ui->screen_main_label_time_sec, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->screen_main_label_time_sec, 205, 173);
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
    lv_obj_set_pos(ui->screen_main_label_date, 14, 174);
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
    lv_obj_set_pos(ui->screen_main_img_4, 7, 175);
    lv_obj_set_size(ui->screen_main_img_4, 15, 15);

    //Write style for screen_main_img_4, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->screen_main_img_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->screen_main_img_4, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_main_img_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->screen_main_img_4, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_main_line_1
    ui->screen_main_line_1 = lv_line_create(ui->screen_main);
    static lv_point_t screen_main_line_1[] = {{1, 1},{1, 30},};
    lv_line_set_points(ui->screen_main_line_1, screen_main_line_1, 2);
    lv_obj_set_pos(ui->screen_main_line_1, 120, 4);
    lv_obj_set_size(ui->screen_main_line_1, 8, 32);

    //Write style for screen_main_line_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_line_width(ui->screen_main_line_1, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_line_color(ui->screen_main_line_1, lv_color_hex(0x757575), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_line_opa(ui->screen_main_line_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_line_rounded(ui->screen_main_line_1, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_main_cont_3
    ui->screen_main_cont_3 = lv_obj_create(ui->screen_main);
    lv_obj_set_pos(ui->screen_main_cont_3, 0, 190);
    lv_obj_set_size(ui->screen_main_cont_3, 240, 52);
    lv_obj_set_scrollbar_mode(ui->screen_main_cont_3, LV_SCROLLBAR_MODE_OFF);

    //Write style for screen_main_cont_3, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_main_cont_3, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->screen_main_cont_3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->screen_main_cont_3, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->screen_main_cont_3, LV_BORDER_SIDE_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_main_cont_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_main_cont_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_main_cont_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_main_cont_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_main_cont_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_main_cont_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_main_cont_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_main_carousel_1
    ui->screen_main_carousel_1 = lv_carousel_create(ui->screen_main_cont_3);
    lv_carousel_set_element_width(ui->screen_main_carousel_1, 240);
    lv_obj_set_size(ui->screen_main_carousel_1, 240, 52);
    ui->screen_main_carousel_1_element_1 = lv_carousel_add_element(ui->screen_main_carousel_1, 0);
    ui->screen_main_carousel_1_element_2 = lv_carousel_add_element(ui->screen_main_carousel_1, 1);
    lv_obj_set_pos(ui->screen_main_carousel_1, 0, 0);
    lv_obj_set_size(ui->screen_main_carousel_1, 240, 52);
    lv_obj_set_scrollbar_mode(ui->screen_main_carousel_1, LV_SCROLLBAR_MODE_OFF);

    //Write style for screen_main_carousel_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_main_carousel_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_main_carousel_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_main_carousel_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for screen_main_carousel_1, Part: LV_PART_SCROLLBAR, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_main_carousel_1, 0, LV_PART_SCROLLBAR|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_main_carousel_1, 0, LV_PART_SCROLLBAR|LV_STATE_DEFAULT);

    //Write style state: LV_STATE_DEFAULT for &style_screen_main_carousel_1_extra_element_items_default
    static lv_style_t style_screen_main_carousel_1_extra_element_items_default;
    ui_init_style(&style_screen_main_carousel_1_extra_element_items_default);

    lv_style_set_bg_opa(&style_screen_main_carousel_1_extra_element_items_default, 0);
    lv_style_set_outline_width(&style_screen_main_carousel_1_extra_element_items_default, 0);
    lv_style_set_border_width(&style_screen_main_carousel_1_extra_element_items_default, 0);
    lv_style_set_radius(&style_screen_main_carousel_1_extra_element_items_default, 5);
    lv_style_set_shadow_width(&style_screen_main_carousel_1_extra_element_items_default, 0);
    lv_obj_add_style(ui->screen_main_carousel_1_element_2, &style_screen_main_carousel_1_extra_element_items_default, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_add_style(ui->screen_main_carousel_1_element_1, &style_screen_main_carousel_1_extra_element_items_default, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style state: LV_STATE_FOCUSED for &style_screen_main_carousel_1_extra_element_items_focused
    static lv_style_t style_screen_main_carousel_1_extra_element_items_focused;
    ui_init_style(&style_screen_main_carousel_1_extra_element_items_focused);

    lv_style_set_bg_opa(&style_screen_main_carousel_1_extra_element_items_focused, 0);
    lv_style_set_outline_width(&style_screen_main_carousel_1_extra_element_items_focused, 0);
    lv_style_set_border_width(&style_screen_main_carousel_1_extra_element_items_focused, 0);
    lv_style_set_radius(&style_screen_main_carousel_1_extra_element_items_focused, 5);
    lv_style_set_shadow_width(&style_screen_main_carousel_1_extra_element_items_focused, 0);
    lv_obj_add_style(ui->screen_main_carousel_1_element_2, &style_screen_main_carousel_1_extra_element_items_focused, LV_PART_MAIN|LV_STATE_FOCUSED);
    lv_obj_add_style(ui->screen_main_carousel_1_element_1, &style_screen_main_carousel_1_extra_element_items_focused, LV_PART_MAIN|LV_STATE_FOCUSED);



    //Write codes screen_main_cont_1
    ui->screen_main_cont_1 = lv_obj_create(ui->screen_main_carousel_1_element_1);
    lv_obj_set_pos(ui->screen_main_cont_1, 0, 0);
    lv_obj_set_size(ui->screen_main_cont_1, 240, 51);
    lv_obj_set_scrollbar_mode(ui->screen_main_cont_1, LV_SCROLLBAR_MODE_OFF);

    //Write style for screen_main_cont_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_main_cont_1, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->screen_main_cont_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->screen_main_cont_1, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->screen_main_cont_1, LV_BORDER_SIDE_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_main_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_main_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_main_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_main_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_main_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_main_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_main_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_main_img_line_2
    ui->screen_main_img_line_2 = lv_img_create(ui->screen_main_cont_1);
    lv_obj_add_flag(ui->screen_main_img_line_2, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->screen_main_img_line_2, &_3304542_20230221171348882211_0_58x2);
    lv_img_set_pivot(ui->screen_main_img_line_2, 0,0);
    lv_img_set_angle(ui->screen_main_img_line_2, 1220);
    lv_obj_set_pos(ui->screen_main_img_line_2, 135, 0);
    lv_obj_set_size(ui->screen_main_img_line_2, 58, 2);

    //Write style for screen_main_img_line_2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->screen_main_img_line_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->screen_main_img_line_2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_main_img_line_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->screen_main_img_line_2, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_main_label_pressure_value
    ui->screen_main_label_pressure_value = lv_label_create(ui->screen_main_cont_1);
    lv_label_set_text(ui->screen_main_label_pressure_value, "100\n");
    lv_label_set_long_mode(ui->screen_main_label_pressure_value, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->screen_main_label_pressure_value, 194, 29);
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

    //Write codes screen_main_label_step_cnt
    ui->screen_main_label_step_cnt = lv_label_create(ui->screen_main_cont_1);
    lv_label_set_text(ui->screen_main_label_step_cnt, "4434");
    lv_label_set_long_mode(ui->screen_main_label_step_cnt, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->screen_main_label_step_cnt, 37, 27);
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
    ui->screen_main_label_pressure = lv_label_create(ui->screen_main_cont_1);
    lv_label_set_text(ui->screen_main_label_pressure, "疲劳度");
    lv_label_set_long_mode(ui->screen_main_label_pressure, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->screen_main_label_pressure, 118, 29);
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
    ui->screen_main_img_step = lv_img_create(ui->screen_main_cont_1);
    lv_obj_add_flag(ui->screen_main_img_step, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->screen_main_img_step, &_step_23x20);
    lv_img_set_pivot(ui->screen_main_img_step, 50,50);
    lv_img_set_angle(ui->screen_main_img_step, 0);
    lv_obj_set_pos(ui->screen_main_img_step, 14, 28);
    lv_obj_set_size(ui->screen_main_img_step, 23, 20);

    //Write style for screen_main_img_step, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->screen_main_img_step, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->screen_main_img_step, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_main_img_step, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->screen_main_img_step, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_main_label_week
    ui->screen_main_label_week = lv_label_create(ui->screen_main_cont_1);
    lv_label_set_text(ui->screen_main_label_week, "星期五六日一二三四");
    lv_label_set_long_mode(ui->screen_main_label_week, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->screen_main_label_week, 139, 4);
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
    ui->screen_main_label_heart_cnt = lv_label_create(ui->screen_main_cont_1);
    lv_label_set_text(ui->screen_main_label_heart_cnt, "100");
    lv_label_set_long_mode(ui->screen_main_label_heart_cnt, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->screen_main_label_heart_cnt, 77, 2);
    lv_obj_set_size(ui->screen_main_label_heart_cnt, 50, 22);

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
    ui->screen_main_img_heart = lv_img_create(ui->screen_main_cont_1);
    lv_obj_add_flag(ui->screen_main_img_heart, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->screen_main_img_heart, &_heart2_25x25);
    lv_img_set_pivot(ui->screen_main_img_heart, 50,50);
    lv_img_set_angle(ui->screen_main_img_heart, 0);
    lv_obj_set_pos(ui->screen_main_img_heart, 63, 2);
    lv_obj_set_size(ui->screen_main_img_heart, 25, 25);

    //Write style for screen_main_img_heart, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->screen_main_img_heart, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->screen_main_img_heart, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_main_img_heart, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->screen_main_img_heart, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_main_label_heart
    ui->screen_main_label_heart = lv_label_create(ui->screen_main_cont_1);
    lv_label_set_text(ui->screen_main_label_heart, "当前心率");
    lv_label_set_long_mode(ui->screen_main_label_heart, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->screen_main_label_heart, 0, 2);
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
    ui->screen_main_img_pressure = lv_img_create(ui->screen_main_cont_1);
    lv_obj_add_flag(ui->screen_main_img_pressure, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->screen_main_img_pressure, &_tired_25x25);
    lv_img_set_pivot(ui->screen_main_img_pressure, 50,50);
    lv_img_set_angle(ui->screen_main_img_pressure, 0);
    lv_obj_set_pos(ui->screen_main_img_pressure, 171, 25);
    lv_obj_set_size(ui->screen_main_img_pressure, 25, 25);

    //Write style for screen_main_img_pressure, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->screen_main_img_pressure, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->screen_main_img_pressure, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_main_img_pressure, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->screen_main_img_pressure, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_main_img_week
    ui->screen_main_img_week = lv_img_create(ui->screen_main_cont_1);
    lv_obj_add_flag(ui->screen_main_img_week, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->screen_main_img_week, &_week_25x25);
    lv_img_set_pivot(ui->screen_main_img_week, 50,50);
    lv_img_set_angle(ui->screen_main_img_week, 0);
    lv_obj_set_pos(ui->screen_main_img_week, 201, 0);
    lv_obj_set_size(ui->screen_main_img_week, 25, 25);

    //Write style for screen_main_img_week, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->screen_main_img_week, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->screen_main_img_week, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_main_img_week, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->screen_main_img_week, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_main_canvas_2
    ui->screen_main_canvas_2 = lv_canvas_create(ui->screen_main_cont_1);
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

    lv_obj_set_pos(ui->screen_main_canvas_2, 0, -1);
    lv_obj_set_size(ui->screen_main_canvas_2, 240, 51);
    lv_obj_set_scrollbar_mode(ui->screen_main_canvas_2, LV_SCROLLBAR_MODE_OFF);



    //Write codes screen_main_cont_4
    ui->screen_main_cont_4 = lv_obj_create(ui->screen_main_carousel_1_element_2);
    lv_obj_set_pos(ui->screen_main_cont_4, 0, 0);
    lv_obj_set_size(ui->screen_main_cont_4, 240, 51);
    lv_obj_set_scrollbar_mode(ui->screen_main_cont_4, LV_SCROLLBAR_MODE_OFF);

    //Write style for screen_main_cont_4, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_main_cont_4, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->screen_main_cont_4, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->screen_main_cont_4, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->screen_main_cont_4, LV_BORDER_SIDE_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_main_cont_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_main_cont_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_main_cont_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_main_cont_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_main_cont_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_main_cont_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_main_cont_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_main_img_9
    ui->screen_main_img_9 = lv_img_create(ui->screen_main_cont_4);
    lv_obj_add_flag(ui->screen_main_img_9, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->screen_main_img_9, &_3304542_20230221171348882211_0_58x2);
    lv_img_set_pivot(ui->screen_main_img_9, 0,0);
    lv_img_set_angle(ui->screen_main_img_9, 1220);
    lv_obj_set_pos(ui->screen_main_img_9, 135, 0);
    lv_obj_set_size(ui->screen_main_img_9, 58, 2);

    //Write style for screen_main_img_9, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->screen_main_img_9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->screen_main_img_9, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_main_img_9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->screen_main_img_9, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_main_label_hum
    ui->screen_main_label_hum = lv_label_create(ui->screen_main_cont_4);
    lv_label_set_text(ui->screen_main_label_hum, "50%\n");
    lv_label_set_long_mode(ui->screen_main_label_hum, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->screen_main_label_hum, 151, 30);
    lv_obj_set_size(ui->screen_main_label_hum, 40, 16);

    //Write style for screen_main_label_hum, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_main_label_hum, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_main_label_hum, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_main_label_hum, lv_color_hex(0xf2f1f1), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_main_label_hum, &lv_font_sun_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_main_label_hum, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_main_label_hum, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_main_label_hum, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_main_label_hum, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_main_label_hum, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_main_label_hum, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_main_label_hum, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_main_label_hum, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_main_label_hum, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_main_label_hum, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_main_label_wei
    ui->screen_main_label_wei = lv_label_create(ui->screen_main_cont_4);
    lv_label_set_text(ui->screen_main_label_wei, "4434");
    lv_label_set_long_mode(ui->screen_main_label_wei, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->screen_main_label_wei, 39, 27);
    lv_obj_set_size(ui->screen_main_label_wei, 45, 22);

    //Write style for screen_main_label_wei, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_main_label_wei, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_main_label_wei, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_main_label_wei, lv_color_hex(0xffd5f2), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_main_label_wei, &lv_font_sun_14, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_main_label_wei, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_main_label_wei, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_main_label_wei, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_main_label_wei, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_main_label_wei, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_main_label_wei, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_main_label_wei, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_main_label_wei, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_main_label_wei, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_main_label_wei, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_main_img_wei
    ui->screen_main_img_wei = lv_img_create(ui->screen_main_cont_4);
    lv_obj_add_flag(ui->screen_main_img_wei, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->screen_main_img_wei, &_wei_22x22);
    lv_img_set_pivot(ui->screen_main_img_wei, 50,50);
    lv_img_set_angle(ui->screen_main_img_wei, 0);
    lv_obj_set_pos(ui->screen_main_img_wei, 14, 28);
    lv_obj_set_size(ui->screen_main_img_wei, 22, 22);

    //Write style for screen_main_img_wei, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->screen_main_img_wei, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->screen_main_img_wei, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_main_img_wei, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->screen_main_img_wei, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_main_label_temp
    ui->screen_main_label_temp = lv_label_create(ui->screen_main_cont_4);
    lv_label_set_text(ui->screen_main_label_temp, "32℃");
    lv_label_set_long_mode(ui->screen_main_label_temp, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->screen_main_label_temp, 145, 7);
    lv_obj_set_size(ui->screen_main_label_temp, 52, 16);

    //Write style for screen_main_label_temp, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_main_label_temp, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_main_label_temp, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_main_label_temp, lv_color_hex(0xf2f1f1), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_main_label_temp, &lv_font_sun_16, LV_PART_MAIN|LV_STATE_DEFAULT);
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

    //Write codes screen_main_label_o2
    ui->screen_main_label_o2 = lv_label_create(ui->screen_main_cont_4);
    lv_label_set_text(ui->screen_main_label_o2, "100");
    lv_label_set_long_mode(ui->screen_main_label_o2, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->screen_main_label_o2, 77, 2);
    lv_obj_set_size(ui->screen_main_label_o2, 48, 22);

    //Write style for screen_main_label_o2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_main_label_o2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_main_label_o2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_main_label_o2, lv_color_hex(0xffd5f2), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_main_label_o2, &lv_font_sun_14, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_main_label_o2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_main_label_o2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_main_label_o2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_main_label_o2, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_main_label_o2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_main_label_o2, 6, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_main_label_o2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_main_label_o2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_main_label_o2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_main_label_o2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_main_img_7
    ui->screen_main_img_7 = lv_img_create(ui->screen_main_cont_4);
    lv_obj_add_flag(ui->screen_main_img_7, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->screen_main_img_7, &_o2_21x20);
    lv_img_set_pivot(ui->screen_main_img_7, 50,50);
    lv_img_set_angle(ui->screen_main_img_7, 0);
    lv_obj_set_pos(ui->screen_main_img_7, 65, 3);
    lv_obj_set_size(ui->screen_main_img_7, 21, 20);

    //Write style for screen_main_img_7, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->screen_main_img_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->screen_main_img_7, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_main_img_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->screen_main_img_7, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_main_label_1
    ui->screen_main_label_1 = lv_label_create(ui->screen_main_cont_4);
    lv_label_set_text(ui->screen_main_label_1, "当前血氧");
    lv_label_set_long_mode(ui->screen_main_label_1, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->screen_main_label_1, 0, 2);
    lv_obj_set_size(ui->screen_main_label_1, 65, 22);

    //Write style for screen_main_label_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_main_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_main_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_main_label_1, lv_color_hex(0xffd5f2), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_main_label_1, &lv_font_sun_14, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_main_label_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_main_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_main_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_main_label_1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_main_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_main_label_1, 6, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_main_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_main_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_main_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_main_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_main_img_hum
    ui->screen_main_img_hum = lv_img_create(ui->screen_main_cont_4);
    lv_obj_add_flag(ui->screen_main_img_hum, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->screen_main_img_hum, &_hum_23x23);
    lv_img_set_pivot(ui->screen_main_img_hum, 50,50);
    lv_img_set_angle(ui->screen_main_img_hum, 0);
    lv_obj_set_pos(ui->screen_main_img_hum, 198, 27);
    lv_obj_set_size(ui->screen_main_img_hum, 23, 23);

    //Write style for screen_main_img_hum, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->screen_main_img_hum, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->screen_main_img_hum, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_main_img_hum, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->screen_main_img_hum, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_main_img_temp
    ui->screen_main_img_temp = lv_img_create(ui->screen_main_cont_4);
    lv_obj_add_flag(ui->screen_main_img_temp, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->screen_main_img_temp, &_temp_25x25);
    lv_img_set_pivot(ui->screen_main_img_temp, 50,50);
    lv_img_set_angle(ui->screen_main_img_temp, 0);
    lv_obj_set_pos(ui->screen_main_img_temp, 200, 0);
    lv_obj_set_size(ui->screen_main_img_temp, 25, 25);

    //Write style for screen_main_img_temp, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->screen_main_img_temp, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->screen_main_img_temp, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_main_img_temp, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->screen_main_img_temp, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    // //Write codes screen_main_canvas_3
    // ui->screen_main_canvas_3 = lv_canvas_create(ui->screen_main_cont_4);
    // static lv_color_t buf_screen_main_canvas_3[LV_CANVAS_BUF_SIZE_TRUE_COLOR_ALPHA(240, 51)];
    // lv_canvas_set_buffer(ui->screen_main_canvas_3, buf_screen_main_canvas_3, 240, 51, LV_IMG_CF_TRUE_COLOR_ALPHA);
    // lv_canvas_fill_bg(ui->screen_main_canvas_3, lv_color_hex(0xffffff), 0);
    // //Canvas draw image
    // lv_draw_img_dsc_t screen_main_canvas_3_img_dsc_0;
    // lv_draw_img_dsc_init(&screen_main_canvas_3_img_dsc_0);
    // lv_canvas_draw_img(ui->screen_main_canvas_3, 2, 1, &_3304542_20230221171348882211_0_alpha_236x1, &screen_main_canvas_3_img_dsc_0);

    // //Canvas draw image
    // lv_draw_img_dsc_t screen_main_canvas_3_img_dsc_1;
    // lv_draw_img_dsc_init(&screen_main_canvas_3_img_dsc_1);
    // lv_canvas_draw_img(ui->screen_main_canvas_3, 2, 26, &_3304542_20230221171348882211_0_alpha_238x1, &screen_main_canvas_3_img_dsc_1);

    // //Canvas draw image
    // lv_draw_img_dsc_t screen_main_canvas_3_img_dsc_2;
    // lv_draw_img_dsc_init(&screen_main_canvas_3_img_dsc_2);
    // lv_canvas_draw_img(ui->screen_main_canvas_3, 2, 50, &_3304542_20230221171348882211_0_alpha_238x1, &screen_main_canvas_3_img_dsc_2);

    // lv_obj_set_pos(ui->screen_main_canvas_3, 0, 0);
    // lv_obj_set_size(ui->screen_main_canvas_3, 240, 51);
    // lv_obj_set_scrollbar_mode(ui->screen_main_canvas_3, LV_SCROLLBAR_MODE_OFF);

    //Write codes screen_main_img_10
    ui->screen_main_img_10 = lv_img_create(ui->screen_main);
    lv_obj_add_flag(ui->screen_main_img_10, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->screen_main_img_10, &_power2_20x20);
    lv_img_set_pivot(ui->screen_main_img_10, 50,50);
    lv_img_set_angle(ui->screen_main_img_10, 0);
    lv_obj_set_pos(ui->screen_main_img_10, 205, 13);
    lv_obj_set_size(ui->screen_main_img_10, 20, 20);

    //Write style for screen_main_img_10, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->screen_main_img_10, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->screen_main_img_10, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_main_img_10, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->screen_main_img_10, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_main_img_11
    ui->screen_main_img_11 = lv_img_create(ui->screen_main);
    lv_obj_add_flag(ui->screen_main_img_11, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->screen_main_img_11, &_bt_20x20);
    lv_img_set_pivot(ui->screen_main_img_11, 50,50);
    lv_img_set_angle(ui->screen_main_img_11, 0);
    lv_obj_set_pos(ui->screen_main_img_11, 173, 13);
    lv_obj_set_size(ui->screen_main_img_11, 20, 20);

    //Write style for screen_main_img_11, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->screen_main_img_11, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->screen_main_img_11, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_main_img_11, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->screen_main_img_11, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //The custom code of screen_main.


    //Update current screen layout.
    lv_obj_update_layout(ui->screen_main);

    //Init events for screen.
    events_init_screen_main(ui);
}
