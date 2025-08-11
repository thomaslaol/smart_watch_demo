#include "main.h"

void app_main(void)
{
    esp_err_t ret = ble_time_sync_init("ESP32-Time-Sync");
    CHEKRET(ret, "ble_time_sync_init");

    ret = aht20_init();
    CHEKRET(ret, "aht20_init");

    ret = bmp280_init();
    CHEKRET(ret, "bmp280_init");

    ret = jfh142_init();
    CHEKRET(ret, "jfh142_init");

    ret = mpu6050_init();
    CHEKRET(ret, "mpu6050_init");

    ret = qmc5883l_init();
    CHEKRET(ret, "qmc5883l_init");

    lvgl_init();

    setup_ui(&guider_ui);

    custom_init(&guider_ui);
}
