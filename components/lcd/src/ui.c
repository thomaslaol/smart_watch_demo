#include "lcd_api.h"
#include "lcd_common.h"

// 按钮触摸回调函数
static void btn_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t *btn = lv_event_get_target(e);
    
    if(code == LV_EVENT_PRESSED) {
        ESP_LOGI("BUTTON", "按钮被按下");
        // 可以在这里添加按钮被按下时的其他操作
    }
    else if(code == LV_EVENT_RELEASED) {
        ESP_LOGI("BUTTON", "按钮被释放");
    }
}

// UI任务
void ui_task(void *arg)
{
    vTaskDelay(pdMS_TO_TICKS(1000));
    
    // 获取屏幕根对象
    lv_obj_t *scr = lv_scr_act();
    lv_obj_set_style_bg_color(scr, lv_color_hex(TFT_BLACK), LV_PART_MAIN);

    // 创建文本标签
    lv_obj_t *label1 = lv_label_create(lv_scr_act());
    lv_label_set_long_mode(label1, LV_LABEL_LONG_WRAP);
    lv_label_set_recolor(label1, true);
    lv_label_set_text(label1, "#0000ff Re-color# #ff00ff words# #ff0000 of a# label "
                              "and wrap long text automatically.");
    lv_obj_set_width(label1, 150);
    lv_obj_align(label1, LV_ALIGN_CENTER, 0, -50);
    lv_obj_set_style_text_font(label1, &lv_font_montserrat_20, LV_PART_MAIN);

    // 创建测试按钮
    lv_obj_t *test_btn = lv_btn_create(lv_scr_act());
    lv_obj_set_size(test_btn, 120, 50);  // 设置按钮大小
    lv_obj_align(test_btn, LV_ALIGN_CENTER, 0, 50);  // 设置按钮位置（居中偏下）
    
    // 给按钮添加文本
    lv_obj_t *btn_label = lv_label_create(test_btn);
    lv_label_set_text(btn_label, "测试按钮");
    
    // 为按钮添加事件回调
    lv_obj_add_event_cb(test_btn, btn_event_handler, LV_EVENT_ALL, NULL);

    while (1)
    {
        vTaskDelay(pdMS_TO_TICKS(200));
    }
}