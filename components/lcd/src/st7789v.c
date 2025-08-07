#include "st7789v.h"
#include "driver/ledc.h"
#include <string.h>
#include "driver/spi_master.h"
#include "driver/gpio.h"
#include "esp_log.h"

st7789v_t tft; // 屏幕对象
static const char *TAG = "ST7789V";

// 发送命令
static void send_command(st7789v_t *dev, uint8_t cmd)
{
    gpio_set_level(dev->dc_pin, 0); // 命令模式

    spi_transaction_t t = {
        .length = 8, // 8位命令
        .tx_buffer = &cmd,
    };

    spi_device_transmit(dev->spi_handle, &t);
}

// 发送数据
static void send_data(st7789v_t *dev, uint8_t *data, size_t len)
{
    if (len == 0)
        return;

    gpio_set_level(dev->dc_pin, 1); // 数据模式

    spi_transaction_t t = {
        .length = len * 8, // 总长度（位）
        .tx_buffer = data,
    };

    spi_device_transmit(dev->spi_handle, &t);
}

// 发送16位数据
static void send_data16(st7789v_t *dev, uint16_t data)
{
    uint8_t buf[2] = {data >> 8, data & 0xFF};
    send_data(dev, buf, 2);
}

// 初始化背光PWM
static void backlight_init(gpio_num_t bl_pin)
{
    // 配置PWM定时器
    ledc_timer_config_t timer_conf = {
        .duty_resolution = LEDC_TIMER_8_BIT,
        .freq_hz = 5000,
        .speed_mode = LEDC_LOW_SPEED_MODE,
        .timer_num = LEDC_TIMER_0};
    ledc_timer_config(&timer_conf);

    // 配置PWM通道
    ledc_channel_config_t channel_conf = {
        .channel = LEDC_CHANNEL_0,
        .duty = 0, // 初始关闭
        .gpio_num = bl_pin,
        .speed_mode = LEDC_LOW_SPEED_MODE,
        .timer_sel = LEDC_TIMER_0};
    ledc_channel_config(&channel_conf);
}

/**======================================PUBLIC========================================= */

/**
 * @brief 初始化ST7789V屏幕
 * @param dev 屏幕对象
 * @param miso MISO引脚
 * @param mosi MOSI引脚
 * @param sclk SCLK引脚
 * @param cs CS引脚
 * @param dc DC引脚
 * @param rst RST引脚
 * @param bl BL引脚
 * @param spi_freq SPI频率
 * @return esp_err_t 初始化结果
 */
esp_err_t st7789v_init(st7789v_t *dev,
                       gpio_num_t miso,
                       gpio_num_t mosi,
                       gpio_num_t sclk,
                       gpio_num_t cs,
                       gpio_num_t dc,
                       gpio_num_t rst,
                       gpio_num_t bl,
                       uint32_t spi_freq)
{
    // 保存引脚信息
    dev->rst_pin = rst;
    dev->dc_pin = dc;
    dev->bl_pin = bl;
    dev->rotation = 0;

    // 初始化控制引脚
    gpio_config_t io_conf = {
        .pin_bit_mask = (1ULL << dc) | (1ULL << rst) | (1ULL << bl),
        .mode = GPIO_MODE_OUTPUT,
        .pull_up_en = GPIO_PULLUP_DISABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_DISABLE};
    gpio_config(&io_conf);
    ESP_LOGI(TAG, "控制引脚初始化完成（DC:%d, RST:%d, BL:%d）", dc, rst, bl);

    // 初始化SPI总线
    spi_bus_config_t buscfg = {
        .miso_io_num = miso,
        .mosi_io_num = mosi,
        .sclk_io_num = sclk,
        .quadwp_io_num = -1,
        .quadhd_io_num = -1,
        .max_transfer_sz = TFT_WIDTH * TFT_HEIGHT * 2 + 8};
    esp_err_t ret = spi_bus_initialize(SPI2_HOST, &buscfg, SPI_DMA_CH_AUTO);
    if (ret != ESP_OK)
    {
        ESP_LOGE(TAG, "SPI总线初始化失败: %s", esp_err_to_name(ret));
        return ret;
    }
    ESP_LOGI(TAG, "SPI总线初始化完成（频率:%dHz）", spi_freq);

    // 配置SPI设备
    spi_device_interface_config_t devcfg = {
        .clock_speed_hz = spi_freq,
        .mode = 0,
        .spics_io_num = cs,
        .queue_size = 10,
        .flags = 0,
    };
    ret = spi_bus_add_device(SPI2_HOST, &devcfg, &dev->spi_handle);
    if (ret != ESP_OK)
    {
        ESP_LOGE(TAG, "添加SPI设备失败: %s", esp_err_to_name(ret));
        return ret;
    }
    ESP_LOGI(TAG, "SPI设备添加完成（CS:%d）", cs);

    // 硬件复位
    gpio_set_level(dev->rst_pin, 0);
    vTaskDelay(pdMS_TO_TICKS(100));
    gpio_set_level(dev->rst_pin, 1);
    vTaskDelay(pdMS_TO_TICKS(100));
    ESP_LOGI(TAG, "硬件复位完成");

    // 严格的初始化命令顺序（参考ST7789V数据手册）
    send_command(dev, ST7789_SWRESET); // 软件复位
    vTaskDelay(pdMS_TO_TICKS(150));
    ESP_LOGI(TAG, "发送软件复位命令");

    send_command(dev, ST7789_SLPOUT); // 退出睡眠
    vTaskDelay(pdMS_TO_TICKS(120));
    ESP_LOGI(TAG, "发送退出睡眠命令");

    // 强制设置显示方向（关键：覆盖默认扫描方向）
    send_command(dev, ST7789_MADCTL);
    uint8_t madctl = 0x00; // 尝试0x00/0x80/0x40/0xC0（见下方说明）
    send_data(dev, &madctl, 1);
    ESP_LOGI(TAG, "设置MADCTL（扫描方向）: 0x%02X", madctl);

    // 强制设置显示窗口（必须在像素格式之后，部分屏幕要求）
    send_command(dev, ST7789_COLMOD);     // 设置像素格式
    send_data(dev, (uint8_t[]){0x55}, 1); // 16位
    vTaskDelay(pdMS_TO_TICKS(10));
    ESP_LOGI(TAG, "设置像素格式为16位");

    // 反色
    send_command(dev, ST7789_INVON); // 开启反色
    vTaskDelay(pdMS_TO_TICKS(10));

    // 开启显示
    send_command(dev, ST7789_NORON); // 正常模式
    vTaskDelay(pdMS_TO_TICKS(10));
    send_command(dev, ST7789_DISPON); // 显示开启
    vTaskDelay(pdMS_TO_TICKS(10));
    ESP_LOGI(TAG, "开启显示");

    // 初始化背光
    backlight_init(bl);
    st7789v_set_brightness(dev, 100);
    ESP_LOGI(TAG, "背光初始化完成");

    ESP_LOGI(TAG, "初始化完成");
    return ESP_OK;
}

/**
 * @brief 设置屏幕旋转
 * @param dev 屏幕设备结构体
 * @param rotation 旋转角度（0, 1, 2, 3）
 * 0- 0度
 * 1- 90度
 * 2- 180度
 * 3- 270度
 */
void st7789v_set_rotation(st7789v_t *dev, uint8_t rotation)
{
    dev->rotation = rotation % 4;
    uint8_t madctl;

    switch (dev->rotation)
    {
    case 0: // 0度
        madctl = 0x00;
        break;
    case 1: // 90度
        madctl = 0x60;
        break;
    case 2: // 180度
        madctl = 0xC0;
        break;
    case 3: // 270度
        madctl = 0xA0;
        break;
    }

    send_command(dev, ST7789_MADCTL);
    send_data(dev, &madctl, 1);
}

/**
 * @brief 清屏
 * @param dev 屏幕设备结构体
 * @param color 颜色
 */
void st7789v_fill_screen(st7789v_t *dev, uint16_t color)
{
    st7789v_fill_rect(dev, 0, 0, TFT_WIDTH, TFT_HEIGHT, color);
}

/**
 * @brief 画点
 * @param dev 屏幕设备结构体
 * @param x x坐标
 * @param y y坐标
 * @param color 颜色
 */
void st7789v_draw_pixel(st7789v_t *dev, uint16_t x, uint16_t y, uint16_t color)
{
    // 检查坐标是否在范围内
    if (x >= TFT_WIDTH || y >= TFT_HEIGHT)
        return;

    st7789v_set_window(dev, x, y, x, y);
    send_data16(dev, color);
}

/**
 * @brief 画线
 * @param dev 屏幕设备结构体
 * @param x0 起始点x坐标
 * @param y0 起始点y坐标
 * @param x1 终止点x坐标
 * @param y1 终止点y坐标
 * @param color 颜色
 */
void st7789v_draw_line(st7789v_t *dev, uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint16_t color)
{
    int16_t dx = x1 - x0;
    int16_t dy = y1 - y0;
    int16_t sx = (dx > 0) ? 1 : -1;
    int16_t sy = (dy > 0) ? 1 : -1;

    dx = (dx < 0) ? -dx : dx;
    dy = (dy < 0) ? -dy : dy;

    int16_t err = dx - dy;
    int16_t x = x0, y = y0;

    while (1)
    {
        st7789v_draw_pixel(dev, x, y, color);
        if (x == x1 && y == y1)
            break;

        int16_t e2 = 2 * err;
        if (e2 > -dy)
        {
            err -= dy;
            x += sx;
        }
        if (e2 < dx)
        {
            err += dx;
            y += sy;
        }
    }
}

/**
 * @brief 画矩形
 * @param dev 屏幕设备结构体
 * @param x 左上角x坐标
 * @param y 左上角y坐标
 * @param w 宽度
 * @param h 高度
 * @param color 颜色
 */
void st7789v_draw_rect(st7789v_t *dev, uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t color)
{
    st7789v_draw_line(dev, x, y, x + w - 1, y, color);                 // 上
    st7789v_draw_line(dev, x, y + h - 1, x + w - 1, y + h - 1, color); // 下
    st7789v_draw_line(dev, x, y, x, y + h - 1, color);                 // 左
    st7789v_draw_line(dev, x + w - 1, y, x + w - 1, y + h - 1, color); // 右
}

/**
 * @brief 填充矩形
 * @param dev 屏幕设备结构体
 * @param x 左上角x坐标
 * @param y 左上角y坐标
 * @param w 宽度
 * @param h 高度
 * @param color 颜色
 */
void st7789v_fill_rect(st7789v_t *dev, uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t color)
{
    // 检查范围
    if (x >= TFT_WIDTH || y >= TFT_HEIGHT)
        return;
    if (x + w > TFT_WIDTH)
        w = TFT_WIDTH - x;
    if (y + h > TFT_HEIGHT)
        h = TFT_HEIGHT - y;

    // 设置显示窗口
    st7789v_set_window(dev, x, y, x + w - 1, y + h - 1);

    // 准备颜色数据（重复填充）
    uint32_t pixel_count = w * h;
    uint8_t color_buf[2 * 1024];               // 2KB缓冲区
    uint32_t buf_size = sizeof(color_buf) / 2; // 每个像素2字节

    // 填充缓冲区
    for (int i = 0; i < buf_size; i++)
    {
        color_buf[2 * i] = color >> 8;
        color_buf[2 * i + 1] = color & 0xFF;
    }

    // 发送数据
    gpio_set_level(dev->dc_pin, 1); // 数据模式
    while (pixel_count > 0)
    {
        uint32_t send_size = (pixel_count > buf_size) ? buf_size : pixel_count;

        spi_transaction_t t = {
            .length = send_size * 16, // 每个像素16位
            .tx_buffer = color_buf,
        };
        spi_device_transmit(dev->spi_handle, &t);

        pixel_count -= send_size;
    }
}

/**
 * @brief 设置背光亮度（0-100）
 * @param dev 屏幕设备结构体
 * @param brightness 亮度值（0-100）
 */
void st7789v_set_brightness(st7789v_t *dev, uint8_t brightness)
{
    if (brightness > 100)
        brightness = 100;
    uint8_t duty = (brightness * 255) / 100; // 转换为8位PWM占空比
    ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0, duty);
    ledc_update_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0);
}

/**
 * @brief 设置显示窗口范围（x0,y0）到（x1,y1）
 * @param dev 屏幕设备结构体
 * @param x0 左上角x坐标
 * @param y0 左上角y坐标
 * @param x1 右下角x坐标
 * @param y1 右下角y坐标
 */
void st7789v_set_window(st7789v_t *dev, uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1)
{
    // 1. 约束列地址在全局范围内（0 ~ ACTUAL_WIDTH-1）
    x0 = (x0 > TFT_WIDTH - 1) ? TFT_WIDTH - 1 : x0;
    x1 = (x1 > TFT_WIDTH - 1) ? TFT_WIDTH - 1 : x1;
    x0 = (x0 > x1) ? x1 : x0; // 确保x0 <= x1

    // 2. 约束行地址在全局范围内（START_ROW ~ END_ROW）
    // 真实为20～300
    uint16_t gram_y0 = START_ROW + y0;
    uint16_t gram_y1 = START_ROW + y1;
    // 确保转换后不超出全局行范围
    gram_y0 = (gram_y0 < START_ROW) ? START_ROW : gram_y0;
    gram_y1 = (gram_y1 > END_ROW) ? END_ROW : gram_y1;
    gram_y0 = (gram_y0 > gram_y1) ? gram_y1 : gram_y0; // 确保gram_y0 <= gram_y1

    // 3. 设置列地址（与全局范围一致）
    send_command(dev, ST7789_CASET);
    uint8_t ca_data[4] = {
        (x0 >> 8) & 0xFF, x0 & 0xFF,
        (x1 >> 8) & 0xFF, x1 & 0xFF};
    send_data(dev, ca_data, 4);

    // 4. 设置行地址（转换为GRAM实际地址后发送）
    send_command(dev, ST7789_RASET);
    uint8_t ra_data[4] = {
        (gram_y0 >> 8) & 0xFF, gram_y0 & 0xFF,
        (gram_y1 >> 8) & 0xFF, gram_y1 & 0xFF};
    send_data(dev, ra_data, 4);

    // 准备写入
    send_command(dev, ST7789_RAMWR);
}

/**
 * 发送RGB565格式的颜色数据到屏幕（适配LVGL双缓存，分块刷新）
 * @param dev 屏幕设备结构体
 * @param colors RGB565颜色数组（LVGL输出的像素数据）
 * @param count 像素数量（等于刷新区域的宽×高）
 */
void st7789v_send_colors(st7789v_t *dev, uint16_t *colors, uint32_t count)
{
    if (count == 0 || colors == NULL)
        return;

    // 1. 转换为uint8_t指针（方便直接传给send_data）
    uint8_t *color_bytes = (uint8_t *)colors;
    size_t total_bytes = count * 2; // 总字节数（每个像素2字节）

    // 2. 分块大小适配LVGL缓存
    const size_t max_chunk_bytes = TFT_WIDTH * BUF_LINE_CNT * 2; // 适配40行缓存的字节数
    size_t remaining = total_bytes;
    size_t pos = 0;

    while (remaining > 0)
    {
        // 计算当前块的字节数（不超过剩余字节和最大块大小）
        size_t chunk_bytes = remaining > max_chunk_bytes ? max_chunk_bytes : remaining;

        // 3. 复用send_data函数（已封装DC=1和SPI事务，减少代码冗余）
        send_data(dev, &color_bytes[pos], chunk_bytes);

        remaining -= chunk_bytes;
        pos += chunk_bytes;
    }
}
