#include "lcd_api.h"
#include "lcd_common.h"

// 显示刷新回调（同上，保持不变）
static void disp_flush(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p)
{
    uint16_t x1 = area->x1, y1 = area->y1, x2 = area->x2, y2 = area->y2;
    st7789v_set_window(&tft, x1, y1, x2, y2);
    st7789v_send_colors(&tft, (uint16_t *)color_p, (x2 - x1 + 1) * (y2 - y1 + 1));
    lv_disp_flush_ready(disp);
}

// 向 LVGL 提供时间基准 每 1ms 调用一次
static void lv_tick_task(void *arg)
{
    lv_tick_inc(1); // 每次增加 1ms
}

// LVGL 主任务
static void lvgl_task(void *arg)
{
    while (1)
    {
        lv_task_handler(); // 处理 LVGL 事件（依赖时间基准）
        vTaskDelay(pdMS_TO_TICKS(5));
    }
}

/**
 * @brief 初始化 LVGL
 * @param  void
 */
void lvgl_init(void)
{
    // 步骤 1：初始化 LVGL 核心
    lv_init();

    // 步骤 2：初始化屏幕
    esp_err_t ret = st7789v_init(&tft, LCD_MISO, LCD_SDA, LCD_SCL, LCD_CS, LCD_DC, LCD_RST, LCD_BL, 20000000);
    if (ret != ESP_OK)
    {
        ESP_LOGE("LVGL_INIT", "屏幕初始化失败！");
        return;
    }

    // 步骤 3：配置双缓存
    static lv_color_t buf1[TFT_WIDTH * BUF_LINE_CNT];
    static lv_color_t buf2[TFT_WIDTH * BUF_LINE_CNT];
    static lv_disp_draw_buf_t draw_buf;
    lv_disp_draw_buf_init(&draw_buf, buf1, buf2, TFT_WIDTH * BUF_LINE_CNT);

    // // // 步骤 4：配置显示驱动
    static lv_disp_drv_t disp_drv;
    lv_disp_drv_init(&disp_drv);
    disp_drv.hor_res = TFT_WIDTH;
    disp_drv.ver_res = TFT_HEIGHT;
    disp_drv.draw_buf = &draw_buf;
    disp_drv.flush_cb = disp_flush;
    lv_disp_drv_register(&disp_drv);

    // 步骤 5：初始化 LVGL 时间基准
    // 创建一个 1ms 周期的定时器，用于更新 LVGL 时间
    const esp_timer_create_args_t tick_timer_args = {
        .callback = &lv_tick_task,
        .name = "lv_tick_timer"};
    esp_timer_handle_t tick_timer;
    esp_timer_create(&tick_timer_args, &tick_timer);
    esp_timer_start_periodic(tick_timer, 1000); // 每 1000us（1ms）触发一次

    // // 步骤 6：创建 LVGL 任务
    xTaskCreate(lvgl_task, "lvgl_task", 16384, NULL, 8, NULL);

    //创建 ui 任务
    xTaskCreate(ui_task, "ui_task", 2048, NULL, 7, NULL);

    vTaskDelay(pdMS_TO_TICKS(100));
}
