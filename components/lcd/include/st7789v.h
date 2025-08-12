#ifndef ST7789V_H
#define ST7789V_H

#include <stdint.h>
#include <esp_err.h>
#include "driver/spi_master.h"
#include "driver/gpio.h"

// 硬件引脚定义
#define LCD_RST 13
#define LCD_SCL 15 // SPI SCK
#define LCD_SDA 14 // SPI MOSI
#define LCD_CS 16
#define LCD_DC 17
#define LCD_BL 18
#define LCD_MISO -1 // 不使用MISO

// 颜色定义（RGB565格式）
#define TFT_BLACK 0x0000
#define TFT_WHITE 0xFFFF
#define TFT_RED 0xF800
#define TFT_GREEN 0x07E0
#define TFT_BLUE 0x001F
#define TFT_YELLOW 0xFFE0
#define TFT_CYAN 0x07FF
#define TFT_MAGENTA 0xF81F
#define TFT_PURPLE 0x8010

// 屏幕参数
#define TFT_WIDTH 240
#define TFT_HEIGHT 280
#define GRAM_HEIGHT 320 // ST7789V内置GRAM高度
#define START_ROW 20
#define END_ROW (START_ROW + TFT_HEIGHT - 1)
#define BUF_LINE_CNT 60 // 缓冲区行数

// ST7789V命令定义
#define ST7789_NOP 0x00
#define ST7789_SWRESET 0x01
#define ST7789_RDDID 0x04
#define ST7789_RDDST 0x09
#define ST7789_SLPIN 0x10
#define ST7789_SLPOUT 0x11
#define ST7789_PTLON 0x12
#define ST7789_NORON 0x13
#define ST7789_INVOFF 0x20
#define ST7789_INVON 0x21
#define ST7789_DISPOFF 0x28
#define ST7789_DISPON 0x29
#define ST7789_CASET 0x2A
#define ST7789_RASET 0x2B
#define ST7789_RAMWR 0x2C
#define ST7789_RAMRD 0x2E
#define ST7789_PTLAR 0x30
#define ST7789_COLMOD 0x3A
#define ST7789_MADCTL 0x36

//  屏幕驱动结构体
typedef struct
{
    spi_device_handle_t spi_handle; // SPI设备句柄
    gpio_num_t rst_pin;             // 复位引脚
    gpio_num_t dc_pin;              // 数据/命令引脚
    gpio_num_t bl_pin;              // 背光引脚
    uint8_t rotation;               // 屏幕旋转（0-3）
} st7789v_t;

// 屏幕设备结构体
extern st7789v_t tft;

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
                       uint32_t spi_freq);

/**
 * @brief 设置屏幕旋转
 * @param dev 屏幕设备结构体
 * @param rotation 旋转角度（0, 1, 2, 3）
 * 0- 0度
 * 1- 90度
 * 2- 180度
 * 3- 270度
 */
void st7789v_set_rotation(st7789v_t *dev, uint8_t rotation);

/**
 * @brief 清屏
 * @param dev 屏幕设备结构体
 * @param color 颜色
 */
void st7789v_fill_screen(st7789v_t *dev, uint16_t color);

/**
 * @brief 画点
 * @param dev 屏幕设备结构体
 * @param x x坐标
 * @param y y坐标
 * @param color 颜色
 */
void st7789v_draw_pixel(st7789v_t *dev, uint16_t x, uint16_t y, uint16_t color);

/**
 * @brief 画线
 * @param dev 屏幕设备结构体
 * @param x0 起始点x坐标
 * @param y0 起始点y坐标
 * @param x1 终止点x坐标
 * @param y1 终止点y坐标
 * @param color 颜色
 */
void st7789v_draw_line(st7789v_t *dev, uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint16_t color);

/**
 * @brief 画矩形
 * @param dev 屏幕设备结构体
 * @param x 左上角x坐标
 * @param y 左上角y坐标
 * @param w 宽度
 * @param h 高度
 * @param color 颜色
 */
void st7789v_draw_rect(st7789v_t *dev, uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t color);

/**
 * @brief 填充矩形
 * @param dev 屏幕设备结构体
 * @param x 左上角x坐标
 * @param y 左上角y坐标
 * @param w 宽度
 * @param h 高度
 * @param color 颜色
 */
void st7789v_fill_rect(st7789v_t *dev, uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t color);

/**
 * @brief 设置背光亮度（0-100）
 * @param dev 屏幕设备结构体
 * @param brightness 亮度值（0-100）
 */
void st7789v_set_brightness(st7789v_t *dev, uint8_t brightness);

/**
 * @brief 设置显示窗口范围（x0,y0）到（x1,y1）
 * @param dev 屏幕设备结构体
 * @param x0 左上角x坐标
 * @param y0 左上角y坐标
 * @param x1 右下角x坐标
 * @param y1 右下角y坐标
 */
void st7789v_set_window(st7789v_t *dev, uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1);

/**
 * 发送RGB565格式的颜色数据到屏幕（适配LVGL双缓存，分块刷新）
 * @param dev 屏幕设备结构体
 * @param colors RGB565颜色数组（LVGL输出的像素数据）
 * @param count 像素数量（等于刷新区域的宽×高）
 */
void st7789v_send_colors(st7789v_t *dev, uint16_t *colors, uint32_t count);

#endif