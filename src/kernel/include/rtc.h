#ifndef PhiOS_rtc
#define PhiOS_rtc

#include <sys/types.h>

typedef struct rtc
{
    p_uint8 seconds;
    p_uint8 minutes;
    p_uint8 hours;
    p_uint8 days;
    p_uint8 months;
    p_uint8 years;
    p_uint8 centuries;
} RTC;

void rtc_init(void);
void rtc_read(void);
RTC* rtc_getRTC(void);

#endif

