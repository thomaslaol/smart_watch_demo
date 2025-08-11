#include "main.h"

void app_main(void)
{

    //蓝牙
    esp_err_t ret = ble_time_sync_init("ESP32-Time-Sync");
    CHEKRET(ret, "ble_time_sync_init");

    //mrtc
    ret = mrtc_init();
    CHEKRET(ret, "mrtc_init");

    //温湿度
    ret = aht20_init();
    CHEKRET(ret, "aht20_init");

    //大气压
    ret = bmp280_init();
    CHEKRET(ret, "bmp280_init");

    //心率血氧
    ret = jfh142_init();
    CHEKRET(ret, "jfh142_init");

    //加速度步测
    ret = mpu6050_init();
    CHEKRET(ret, "mpu6050_init");

    //地磁
    ret = qmc5883l_init();
    CHEKRET(ret, "qmc5883l_init");

    //屏幕ui
    ret = app_init();
    CHEKRET(ret, "app_init");
}
