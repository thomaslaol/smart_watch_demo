#include "main.h"
#include "aht20.h"
#include "qmc5883l.h"
#include "esp_log.h"
#include "bmp280.h"
#include "mpu6050.h"
#include "jfh142.h"
#include "lcd_api.h"

#include "generated/gui_guider.h" // UI结构体
#include "custom/custom.h"        // 自定义初始化

#define LOG_LOCAL_LEVEL ESP_LOG_DEBUG



void aht20_task(void *pvParameters)
{
    float temperature = 0;
    float humidity = 0;
    if (aht20_init() == ESP_OK)
        printf("aht20_init完成\n");
    while (1)
    {
        aht20_get_value(&temperature, &humidity);
        // printf("温度：%f, 湿度：%f\n", temperature, humidity);
        vTaskDelay(pdMS_TO_TICKS(2000));
    }
}

void kmc5881l_task(void *pvParameters)
{
    double angle = 0;
    if (qmc5883l_init() == ESP_OK)
        printf("qmc5883l_init完成\n");
    while (1)
    {
        qmc5883l_get_angle(&angle);
        // printf("角度：%f\n", angle);
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

void bmp280_task(void *pvParameters)
{
    float temperature = 0;
    float pressure = 0;
    if (bmp280_init() == ESP_OK)
        printf("bmp280_init完成\n");
    while (1)
    {
        bmp280_get_data(&temperature, &pressure);
        // printf("温度：%.2f, 气压：%.2f\n", temperature, pressure);
        vTaskDelay(pdMS_TO_TICKS(2000));
    }
}

void mpu6050_task(void *pvParameters)
{
    unsigned long count = 0;
    mpu6050_init();
    while (1)
    {
        mpu6050_get_step(&count);
        // printf("步数：%lu\n", count);
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

TaskHandle_t aht20_task_handle = NULL;
TaskHandle_t kmc5883l_task_handle = NULL;
TaskHandle_t bmp280_task_handle = NULL;
TaskHandle_t mpu6050_task_handle = NULL;

void app_main(void)
{

    BaseType_t xReturned;
    xReturned = xTaskCreatePinnedToCore((TaskFunction_t)aht20_task, "aht20_task", 4096, NULL, 5, &aht20_task_handle, 1);
    if (xReturned != pdPASS)
    {
        ESP_LOGE("aht20_task", "Failed to create task");
    }

    ESP_LOGI("aht20_task", "Task created");

    xReturned = xTaskCreatePinnedToCore((TaskFunction_t)kmc5881l_task, "kmc5881l_task", 4096, NULL, 5, &kmc5883l_task_handle, 1);
    if (xReturned != pdPASS)
    {
        ESP_LOGE("kmc5881l_task", "Failed to create task");
    }
    ESP_LOGI("kmc5881l_task", "Task created");

    xReturned = xTaskCreatePinnedToCore((TaskFunction_t)bmp280_task, "bmp280_task", 4096, NULL, 5, &bmp280_task_handle, 1);
    if (xReturned != pdPASS)
    {
        ESP_LOGE("bmp280_task", "Failed to create task");
    }
    ESP_LOGI("bmp280_task", "Task created");

    xReturned = xTaskCreatePinnedToCore((TaskFunction_t)mpu6050_task, "mpu6050_task", 4096, NULL, 5, &mpu6050_task_handle, 1);
    if (xReturned != pdPASS)
    {
        ESP_LOGE("mpu6050_task", "Failed to create task");
    }
    ESP_LOGI("mpu6050_task", "Task created");

    esp_err_t ret = jfh142_init();
    if (ret != ESP_OK)
    {
        ESP_LOGE("jfh142_init", "jfh142_init失败");
        return;
    }

    lvgl_init();

    setup_ui(&guider_ui);

    // 5. 初始化你的自定义逻辑（刻度绘制等）
    custom_init(&guider_ui);
}
