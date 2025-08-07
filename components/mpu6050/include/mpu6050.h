#ifndef _MPU6050_H_
#define _MPU6050_H_

#include <stdint.h>

int mpu6050_init(void);
int mpu6050_get_step(unsigned long *count);

#endif // _MPU6050_H_