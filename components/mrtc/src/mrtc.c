#include "mrtc.h"
#include "sys/time.h"
#include "esp_log.h"
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

mrtc_time_t g_mrtc_data;
static const char *TAG = "mrtc";

static void mrtc_task(void *pvParameters);
static mrtc_time_t *mrtc_get_time(void);

esp_err_t mrtc_init(void)
{
    // 创建mrtc任务
    BaseType_t xReturned = xTaskCreatePinnedToCore(mrtc_task, "mrtc_task", 4096, NULL, 4, NULL,0);
    if (xReturned != pdPASS)
    {
        ESP_LOGE(TAG, "create mrtc task failed");
        return ESP_FAIL;
    }
    return ESP_OK;
}

char *mrtc_get_time_str(void)
{
    static char time_str[8] = {0};
    sprintf(time_str, "%02d:%02d", g_mrtc_data.hour, g_mrtc_data.minute);
    return time_str;
}

char *mrtc_get_sec_str(void)
{
    static char sec_str[8] = {0};
    sprintf(sec_str, ":%02d", g_mrtc_data.second);
    return sec_str;
}

char *mrtc_get_date_str(void)
{
    static char date_str[12] = {0};
    sprintf(date_str, "%02ld/%02ld/%02ld", g_mrtc_data.year, g_mrtc_data.month, g_mrtc_data.day);
    return date_str;
}

char *mrtc_get_week_str(void)
{
    static char week_str[12] = {0};
    switch (g_mrtc_data.weekday)
    {
    case 1:
        sprintf(week_str, "星期一");
        break;
    case 2:
        sprintf(week_str, "星期二");
        break;
    case 3:
        sprintf(week_str, "星期三");
        break;
    case 4:
        sprintf(week_str, "星期四");
        break;
    case 5:
        sprintf(week_str, "星期五");
        break;
    case 6:
        sprintf(week_str, "星期六");
        break;
    case 7:
        sprintf(week_str, "星期日");
        break;
    default:
        break;
    }
    return week_str;
}

static void mrtc_task(void *pvParameters)
{
    while (1)
    {
        mrtc_get_time();
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}

static mrtc_time_t *mrtc_get_time(void)
{
    struct tm *datetime;

    time_t second = time(NULL);
    datetime = localtime(&second);

    g_mrtc_data.year = datetime->tm_year + 1900;
    g_mrtc_data.month = datetime->tm_mon + 1;
    g_mrtc_data.day = datetime->tm_mday;
    g_mrtc_data.hour = datetime->tm_hour;
    g_mrtc_data.minute = datetime->tm_min;
    g_mrtc_data.second = datetime->tm_sec;
    g_mrtc_data.weekday = datetime->tm_wday;

    // ESP_LOGI(TAG, "year: %d, month: %d, day: %d, hour: %d, minute: %d, second: %d, weekday: %d",
            //  g_mrtc_data.year,
            //  g_mrtc_data.month,
            //  g_mrtc_data.day,
            //  g_mrtc_data.hour,
            //  g_mrtc_data.minute,
            //  g_mrtc_data.second,
            //  g_mrtc_data.weekday);
            
    return &g_mrtc_data;
}
