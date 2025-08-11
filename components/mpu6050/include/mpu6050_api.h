#ifndef _MPU6050_API_H_
#define _MPU6050_API_H_

#include "esp_err.h"

typedef struct {
    uint32_t step_count;
} mpu6050_step_t;

extern mpu6050_step_t g_mpu6050_step;

/**
 * @brief mpu6050初始化
 *
 * 自动检测I2C总线是否已初始化，如果没有则初始化
 * 初始化成功后，将自动启动DMP固件，并设置采样率为100Hz，加速度计量程为±2g，加速度计高通滤波（5Hz截止）
 * 自动启动任务，每1秒更新一次步数，并存放在s_mpu6050_data中
 *
 * 检测是初始化iic总线->初始化mpu6050-启动DMP固件-设置采样率-设置加速度计量程-设置加速度计高通滤波-启动任务
 *
 * @param  无
 * @return esp_err_t 操作结果（ESP_OK表示成功）
 */
esp_err_t mpu6050_init(void);

char *mpu6050_get_step_str(void);

#endif // _MPU6050_API_H_