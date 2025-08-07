#ifndef _BMP280_H_
#define _BMP280_H_

#define BMP280_I2C_ADDR 0x77
#define BMP280_REG_ID 0xD0
#define BMP280_CHIP_ID 0x58

#define BMP280_REG_CTRL_MEAS 0xF4

#include <stdint.h>
#include "esp_err.h"

// 定义校准数据结构体（全局或通过参数传递）
typedef struct __attribute__((packed)) {
    uint16_t dig_T1;  // 字节0-1
    int16_t  dig_T2;  // 字节2-3
    int16_t  dig_T3;  // 字节4-5
    uint16_t dig_P1;  // 字节6-7
    int16_t  dig_P2;  // 字节8-9
    int16_t  dig_P3;  // 字节10-11
    int16_t  dig_P4;  // 字节12-13
    int16_t  dig_P5;  // 字节14-15
    int16_t  dig_P6;  // 字节16-17
    int16_t  dig_P7;  // 字节18-19
    int16_t  dig_P8;  // 字节20-21
    int16_t  dig_P9;  // 字节22-23
} bmp280_calib_data_t;

esp_err_t bmp280_init(void);
esp_err_t bmp280_get_data(float *temp, float *pres);

#endif // _BMP280_H_