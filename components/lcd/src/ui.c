#include "lcd_api.h"
#include "lcd_common.h"


// 3. ui 主任务
void ui_task(void *arg)
{
    vTaskDelay(pdMS_TO_TICKS(1000));
     // // 获取屏幕根对象（LVGL 管理的"屏幕"容器）
    lv_obj_t *scr = lv_scr_act();
    lv_obj_set_style_bg_color(scr, lv_color_hex(TFT_BLACK), LV_PART_MAIN);

    lv_obj_t *label1 = lv_label_create(lv_scr_act()); // 在当前屏幕上创建一个文本对象
    lv_label_set_long_mode(label1, LV_LABEL_LONG_WRAP);
    lv_label_set_recolor(label1, true); // 开启重找色功能
    lv_label_set_text(label1, "#0000ff Re-color# #ff00ff words# #ff0000 of a# label "
                              "and wrap long text automatically.");
    lv_obj_set_width(label1, 150);
    lv_obj_align(label1, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_text_font(label1, &lv_font_montserrat_20, LV_PART_MAIN);

    // // 创建一条线
    // lv_point_t points[] = {
    //     {50, 2},  // 起点：x=5, y=220
    //     {50, 275} // 终点：x=200, y=220（水平向右的线）
    // };
    // lv_obj_t *line1 = lv_line_create(lv_scr_act());
    // lv_line_set_points(line1, points, 2);
    // lv_obj_set_style_line_color(line1, lv_color_hex(TFT_BLACK), LV_PART_MAIN); // 红色
    // lv_obj_set_style_line_width(line1, 2, LV_PART_MAIN);                       // 线宽2像素
    while (1)
    {


        vTaskDelay(pdMS_TO_TICKS(200));
    }
}