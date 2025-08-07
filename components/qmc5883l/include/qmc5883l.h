#ifndef _QMC5883L_H_
#define _QMC5883L_H_

#include "esp_err.h"

#define QMC5883L_I2C_ADDR 0x0D
#define QMC5883L_MODE_REG 0x0B   // 模式寄存器地址
#define QMC5883L_CONFIG_REG 0x09 // 配置寄存器地址

/**
 * @brief qmc5883l初始化
 * @param  void
 * @return esp_err_t
 */
esp_err_t qmc5883l_init(void);

/**
 * @brief qmc5883l读取角度
 * @param angle 角度值存放地址
 * @return esp_err_t
 */
esp_err_t qmc5883l_get_angle(double *angle);

#endif // _QMC5883L_H_