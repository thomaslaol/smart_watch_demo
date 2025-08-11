/**bjy:使用st7789v驱动直接显示屏幕，测试使用 */
#if 0
#include "lcd.h"
#include "st7789v.h"
#include "esp_log.h"

static const char *TAG = "lcd";

// 1. 显示文本（使用简单的8x8点阵字体）
// 8x8 ASCII字符点阵（以字符'A'为例，完整字体需扩展）
const uint8_t font8x8[][8] = {
    {0x00, 0x18, 0x3C, 0x66, 0x66, 0x7E, 0x66, 0x00}, // 'A'
    {0x00, 0x7E, 0x66, 0x66, 0x7E, 0x66, 0x66, 0x7E}, // 'B'
    // 更多字符需自行添加...
};

// 绘制单个字符（8x8）
void draw_char_8x8(st7789v_t *dev, uint16_t x, uint16_t y, char c, uint16_t color, uint16_t bg_color)
{
    if (c < 'A' || c > 'Z')
        return; // 仅支持A-Z
    uint8_t idx = c - 'A';

    for (int row = 0; row < 8; row++)
    {
        uint8_t data = font8x8[idx][row];
        for (int col = 0; col < 8; col++)
        {
            if (data & (1 << (7 - col)))
            {
                st7789v_draw_pixel(dev, x + col, y + row, color);
            }
            else if (bg_color != 0xFFFF)
            { // 0xFFFF作为透明色
                st7789v_draw_pixel(dev, x + col, y + row, bg_color);
            }
        }
    }
}

// 绘制字符串（8x8）
void draw_string_8x8(st7789v_t *dev, uint16_t x, uint16_t y, const char *str, uint16_t color, uint16_t bg_color)
{
    while (*str)
    {
        draw_char_8x8(dev, x, y, *str, color, bg_color);
        x += 8; // 字符宽度+间距
        str++;
    }
}

// 2. 绘制圆形（Bresenham算法）
void draw_circle(st7789v_t *dev, uint16_t x0, uint16_t y0, uint16_t r, uint16_t color)
{
    int16_t x = r, y = 0;
    int16_t err = 0;

    while (x >= y)
    {
        st7789v_draw_pixel(dev, x0 + x, y0 + y, color);
        st7789v_draw_pixel(dev, x0 + y, y0 + x, color);
        st7789v_draw_pixel(dev, x0 - y, y0 + x, color);
        st7789v_draw_pixel(dev, x0 - x, y0 + y, color);
        st7789v_draw_pixel(dev, x0 - x, y0 - y, color);
        st7789v_draw_pixel(dev, x0 - y, y0 - x, color);
        st7789v_draw_pixel(dev, x0 + y, y0 - x, color);
        st7789v_draw_pixel(dev, x0 + x, y0 - y, color);

        if (err <= 0)
        {
            y++;
            err += 2 * y + 1;
        }
        if (err > 0)
        {
            x--;
            err -= 2 * x + 1;
        }
    }
}

// 3. 显示简单图片（20x20像素的笑脸图标）
const uint16_t smiley[20][20] = {
    {0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0},
    {0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0},
    // 省略中间数据，实际使用时需补充完整20x20像素数据
    {0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0}};

void draw_image_20x20(st7789v_t *dev, uint16_t x, uint16_t y)
{
    for (int i = 0; i < 20; i++)
    {
        for (int j = 0; j < 20; j++)
        {
            if (smiley[i][j])
            {
                st7789v_draw_pixel(dev, x + j, y + i, TFT_YELLOW);
            }
        }
    }
}

void lcd_init(void)
{
    // 1. 初始化屏幕
    esp_err_t ret = st7789v_init(
        &tft,
        LCD_MISO,
        LCD_SDA,
        LCD_SCL,
        LCD_CS,
        LCD_DC,
        LCD_RST,
        LCD_BL,
        40000000 // 40MHz SPI频率
    );
    if (ret != ESP_OK)
    {
        printf("屏幕初始化失败！\n");
        return;
    }

    // 2. 清屏（黑色）
    st7789v_fill_screen(&tft, TFT_WHITE);
    // st7789v_fill_screen(&tft, TFT_RED);
    // st7789v_fill_screen(&tft, TFT_GREEN);

    // vTaskDelay(pdMS_TO_TICKS(500));

    // // 3. 绘制彩色矩形
    // st7789v_fill_rect(&tft, 10, 10, 60, 40, TFT_RED);
    // st7789v_fill_rect(&tft, 80, 10, 60, 40, TFT_GREEN);
    // st7789v_fill_rect(&tft, 150, 10, 60, 40, TFT_BLUE);
    // vTaskDelay(pdMS_TO_TICKS(1000));

    // // 4. 绘制线条和圆形
    // st7789v_draw_line(&tft, 0, 60, 239, 60, TFT_WHITE); // 水平线
    // draw_circle(&tft, 120, 100, 30, TFT_CYAN);          // 圆形
    // vTaskDelay(pdMS_TO_TICKS(1000));

    // 5. 显示文本
    // st7789v_fill_rect(&tft, 0, 140, 240, 30, TFT_BLACK); // 清除区域
    // draw_string_8x8(&tft, 10, 140, "HELLO ST7789V", TFT_WHITE, TFT_BLACK);
    // vTaskDelay(pdMS_TO_TICKS(1500));

    // // 6. 显示图片
    // st7789v_fill_rect(&tft, 0, 180, 240, 40, TFT_BLACK); // 清除区域
    // draw_image_20x20(&tft, 110, 180);                    // 显示笑脸
    // vTaskDelay(pdMS_TO_TICKS(1500));

    // // 7. 调节背光亮度
    // for (int i = 50; i <= 100; i += 10)
    // {
    //     st7789v_set_brightness(&tft, i);
    //     vTaskDelay(pdMS_TO_TICKS(200));
    // }

    // 颜色测试
    // st7789v_fill_screen(&tft, TFT_YELLOW); // 应显示红色
    // st7789v_fill_screen(&tft, TFT_GREEN); // 应显

    // vTaskDelay(1000);
    // st7789v_fill_screen(&tft, TFT_GREEN); // 应显示绿色
    // vTaskDelay(1000);
    // st7789v_fill_screen(&tft, TFT_BLUE); // 应显示蓝色
    // vTaskDelay(1000);
    // // 分辨率测试

    // st7789v_fill_rect(&tft, 0, 0, 100, 100, TFT_RED);      // 左上角：应显示红色
    // st7789v_fill_rect(&tft, 100, 0, 100, 100, TFT_GREEN);  // 右上角：应显示绿色
    // st7789v_fill_rect(&tft, 0, 100, 100, 100, TFT_YELLOW); // 左下角：应显示黄色
    // st7789v_fill_rect(&tft, 100, 100, 100, 100, TFT_PURPLE); // 下角：应
    st7789v_draw_line(&tft, 50, 20, TFT_WIDTH - 1, TFT_WIDTH - 1, TFT_YELLOW);
    st7789v_draw_line(&tft, 50, 40, TFT_WIDTH - 1, TFT_HEIGHT - 1, TFT_RED);
    st7789v_draw_line(&tft, 10, 30, 230, 30, TFT_RED);
    st7789v_fill_rect(&tft, 0, 2, 240, 10, TFT_GREEN);
    // vTaskDelay(1000);

    // // 字符测试
    // draw_string_8x8(&tft, 10, 140, "ABAAC", TFT_WHITE, TFT_BLACK);
    // vTaskDelay(pdMS_TO_TICKS(1500));

    // // // 旋转测试
    // st7789v_set_rotation(&tft, 1);
    // vTaskDelay(1000);
    // draw_string_8x8(&tft, 10, 140, "ABAAC", TFT_WHITE, TFT_BLACK);
    // vTaskDelay(pdMS_TO_TICKS(1500));
    // st7789v_set_rotation(&tft, 3);
}


#endif
