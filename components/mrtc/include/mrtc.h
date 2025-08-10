#ifndef _RTC_H_
#define _RTC_H_
#include <stdint.h>

// void mrtc_set_time(int year, int mon, int mday, int hour, int min, int sec);
void mrtc_set_time(int64_t second);
void mrtc_get_time(void);

#endif // _RTC_H_