#ifndef _RTC_H_
#define _RTC_H_

#include <stdint.h>
#include "esp_err.h"

typedef struct {
    uint32_t year;
    uint32_t month;
    uint32_t day;
    uint32_t hour;
    uint32_t minute;
    uint32_t second;
    uint32_t weekday;
} mrtc_time_t;

esp_err_t mrtc_init(void);

char *mrtc_get_time_str(void);

char *mrtc_get_sec_str(void);

char *mrtc_get_date_str(void);

char *mrtc_get_week_str(void);

#endif // _RTC_H_