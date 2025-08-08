#include "lcd_api.h"
#include "lcd_common.h"

// 首先在文件顶部添加必要的变量声明
lv_indev_t *touch_indev;
lv_indev_data_t touch_data;
SemaphoreHandle_t touch_mutex; // 用于保护触摸数据的互斥锁

// 触摸数据读取回调函数，供LVGL调用
static void touch_read_cb(lv_indev_drv_t *indev_drv, lv_indev_data_t *data)
{
    if (xSemaphoreTake(touch_mutex, pdMS_TO_TICKS(10)) == pdTRUE)
    {
        // 复制最新的触摸数据到LVGL
        data->point.x = touch_data.point.x;
        data->point.y = touch_data.point.y;
        data->state = touch_data.state;
        xSemaphoreGive(touch_mutex);
    }
    else
    {
        // 如果获取不到锁，默认释放状态
        data->state = LV_INDEV_STATE_REL;
    }
}

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
// 修改LVGL初始化函数，添加触摸输入设备注册
void lvgl_init(void)
{
    // 步骤 1：初始化 LVGL 核心
    lv_init();

    // 提前初始化触摸互斥锁，确保在任何触摸操作前就绪
    touch_mutex = xSemaphoreCreateMutex();
    if (!touch_mutex) {
        ESP_LOGE("LVGL_INIT", "创建触摸互斥锁失败");
        return;
    }
    
    // 初始化触摸数据
    xSemaphoreTake(touch_mutex, portMAX_DELAY);
    touch_data.state = LV_INDEV_STATE_REL;
    touch_data.point.x = 0;
    touch_data.point.y = 0;
    xSemaphoreGive(touch_mutex);

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

    // 步骤 4：配置显示驱动
    static lv_disp_drv_t disp_drv;
    lv_disp_drv_init(&disp_drv);
    disp_drv.hor_res = TFT_WIDTH;
    disp_drv.ver_res = TFT_HEIGHT;
    disp_drv.draw_buf = &draw_buf;
    disp_drv.flush_cb = disp_flush;
    lv_disp_drv_register(&disp_drv);

    // 步骤 5：初始化触摸设备
    static lv_indev_drv_t indev_drv;
    lv_indev_drv_init(&indev_drv);
    indev_drv.type = LV_INDEV_TYPE_POINTER;  // 触摸设备类型
    indev_drv.read_cb = touch_read_cb;       // 设置触摸读取回调
    touch_indev = lv_indev_drv_register(&indev_drv);

    // 步骤 6：初始化 LVGL 时间基准
    const esp_timer_create_args_t tick_timer_args = {
        .callback = &lv_tick_task,
        .name = "lv_tick_timer"};
    esp_timer_handle_t tick_timer;
    esp_timer_create(&tick_timer_args, &tick_timer);
    esp_timer_start_periodic(tick_timer, 1000); // 每1ms触发一次

    // 步骤 7：创建 LVGL 任务
    xTaskCreate(lvgl_task, "lvgl_task", 16384, NULL, 8, NULL);

    // 创建UI任务
    xTaskCreate(ui_task, "ui_task", 2048, NULL, 7, NULL);

    // 启动触摸驱动
    cst816t_start_verify();

    vTaskDelay(pdMS_TO_TICKS(100));
}
