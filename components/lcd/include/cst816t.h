#ifndef CST816T_H
#define CST816T_H

#include "esp_err.h"

// 引脚定义
#define CST816T_SDA_PIN GPIO_NUM_11
#define CST816T_SCL_PIN GPIO_NUM_12
#define CST816T_INT_PIN GPIO_NUM_9
#define CST816T_RST_PIN GPIO_NUM_10

// CST816T配置参数
#define CST816T_ADDR 0x15         // I2C地址
#define I2C_MASTER_FREQ_HZ 100000 // I2C频率，降低到100K提高稳定性

// 寄存器地址定义
#define CST816T_GESTURE_ID     0x01
#define CST816T_FINGER_NUM     0x02
#define CST816T_XPOS_H         0x03
#define CST816T_XPOS_L         0x04
#define CST816T_YPOS_H         0x05
#define CST816T_YPOS_L         0x06
#define CST816T_CHIP_ID        0xA7

// 屏幕分辨率（240×280）
#define X_MAX 240
#define Y_MAX 280

// 手势定义
typedef enum
{
    GESTURE_NONE = 0x00,
    GESTURE_SLIDE_UP = 0x01,
    GESTURE_SLIDE_DOWN = 0x02,
    GESTURE_SLIDE_LEFT = 0x03,
    GESTURE_SLIDE_RIGHT = 0x04,
    GESTURE_SINGLE_CLICK = 0x05,
    GESTURE_DOUBLE_CLICK = 0x0B,
    GESTURE_LONG_PRESS = 0x0C
} cst816t_gesture_t;

// 触摸数据结构
typedef struct
{
    uint8_t touch_num;         // 触摸点数
    cst816t_gesture_t gesture; // 手势
    uint16_t x;                // X坐标
    uint16_t y;                // Y坐标
} cst816t_data_t;

// 函数声明
esp_err_t cst816t_init(void);
void cst816t_start_verify(void);
void cst816t_start_verify(void);

#endif // CST816T_H
