#include <rtc.h>
#include <kheap.h>

#ifdef PhiArch_i386
#include <common.h>
#include <interrupts.h>
#endif

RTC *rtc = P_NULL;

#define CMOS_ADDRESS    0x70
#define CMOS_DATA       0x71

#define SECONDS_KEY     0x00
#define MINUTES_KEY     0x02
#define HOURS_KEY       0x04
#define DAYS_KEY        0x07
#define MONTHS_KEY      0x08
#define YEARS_KEY       0x09
#define CENTURIES_KEY   0x32

static p_uint8 __rtc_checkIfUpdateIsInProgress()
{
    interrupts_cli();

    outb(CMOS_ADDRESS, 0x0A);
    p_uint8 ret = inb(CMOS_DATA) & 0x80;

    interrupts_sti();

    return ret;
}

static p_uint8 __rtc_getRegisterValue(p_uint8 reg)
{
    interrupts_cli();

    while (__rtc_checkIfUpdateIsInProgress());

    outb(CMOS_ADDRESS, reg);
    p_uint8 ret = inb(CMOS_DATA);

    interrupts_sti();

    return ret;
}

void rtc_init()
{
    rtc = (RTC*) kheap_kmalloc(sizeof(RTC));

    rtc_read();
}

void rtc_read()
{
    if (rtc == P_NULL)
        return;

    rtc->seconds    = __rtc_getRegisterValue(SECONDS_KEY);
    rtc->minutes    = __rtc_getRegisterValue(MINUTES_KEY);
    rtc->hours      = __rtc_getRegisterValue(HOURS_KEY);
    rtc->days       = __rtc_getRegisterValue(DAYS_KEY);
    rtc->months     = __rtc_getRegisterValue(MONTHS_KEY);
    rtc->years      = __rtc_getRegisterValue(YEARS_KEY);
    rtc->centuries  = __rtc_getRegisterValue(CENTURIES_KEY);

    p_uint8 registerB = __rtc_getRegisterValue(0x0B);

    if (!(registerB & 0x04))
    {
        rtc->hours      = (rtc->hours       & 0x0F) + (rtc->hours       / 16) * 10;
        rtc->seconds    = (rtc->seconds     & 0x0F) + (rtc->seconds     / 16) * 10;
        rtc->minutes    = (rtc->minutes     & 0x0F) + (rtc->minutes     / 16) * 10;
        rtc->days       = (rtc->days        & 0x0F) + (rtc->days        / 16) * 10;
        rtc->months     = (rtc->months      & 0x0F) + (rtc->months      / 16) * 10;
        rtc->years      = (rtc->years       & 0x0F) + (rtc->years       / 16) * 10;
        rtc->centuries  = (rtc->centuries   & 0x0F) + (rtc->centuries   / 16) * 10;
    }

    if (!(registerB & 0x02) && (rtc->hours & 0x80))
        rtc->hours = ((rtc->hours & 0x7F) + 12) % 24;
}

RTC* rtc_getRTC()
{
    return rtc;
}

