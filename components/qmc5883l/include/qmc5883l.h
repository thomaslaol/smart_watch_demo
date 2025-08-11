#ifndef _QMC5883L_H_
#define _QMC5883L_H_

#include "esp_err.h"

typedef struct
{
    double angle;
} qmc5883l_data_t;

extern qmc5883l_data_t g_qmc5883l_data;

/**
 * @brief qmc5883l初始化
 *
 * 自动检测I2C总线是否已初始化，如果未初始化则自动初始化
 * 初始化成功后，自动启动任务
 * 任务每秒读取一次数据，并计算角度，存放于全局变量g_qmc5883l_data中
 *
 * 检测是否初始化iic->检测设备是否存在->软件复位->设置模式->配置->启动任务
 *
 * @param  void
 * @return esp_err_t
 */
esp_err_t qmc5883l_init(void);

#endif // _QMC5883L_H_