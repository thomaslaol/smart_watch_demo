#include "mrtc.h"
// #include "time.h"
#include "sys/time.h"
#include "esp_log.h"

static const char *TAG = "mrtc";

void mrtc_set_time(int64_t second)
{
    // struct tm datetime;
    // /* 设置时间 */
    // datetime.tm_year = year - 1900;
    // datetime.tm_mon = mon - 1;
    // datetime.tm_mday = mday;
    // datetime.tm_hour = hour;
    // datetime.tm_min = min;
    // datetime.tm_sec = sec;
    // datetime.tm_isdst = -1;
    // /* 获取 1970.1.1 以来的总秒数 */
    // time_t second = mktime(&datetime);

    struct timeval val = {.tv_sec = (time_t)second, .tv_usec = 0};
    /* 设置当前时间 */
    settimeofday(&val, NULL);
}

void mrtc_get_time(void)
{
    struct tm *datetime;
    time_t second;
    /* 返回自(1970.1.1 00:00:00 UTC)经过的时间(秒) */
    time(&second);

    // ESP_LOGI(TAG, "time: %lld", second);

    datetime = localtime(&second);

    ESP_LOGI(TAG, "time: %d-%d-%d %d:%d:%d",
             datetime->tm_year + 1900,
             datetime->tm_mon + 1,
             datetime->tm_mday,
             datetime->tm_hour,
             datetime->tm_min,
             datetime->tm_sec);
}