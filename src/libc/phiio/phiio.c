#include <phiio.h>
#include <vga.h>
#include <phistr.h>
#include <rtc.h>

static void __printk_time(const RTC *rtc)
{
    if (rtc->days < 10)
        printk("0%u.", rtc->days);
    else
        printk("%u.", rtc->days);

    if (rtc->months < 10)
        printk("0%u.", rtc->months);
    else
        printk("%u.", rtc->months);

    printk("%u ", rtc->centuries * 100 + rtc->years);

    if (rtc->hours < 10)
        printk("0%u:", rtc->hours);
    else
        printk("%u:", rtc->hours);

    if (rtc->minutes < 10)
        printk("0%u:", rtc->minutes);
    else
        printk("%u:", rtc->minutes);

    if (rtc->seconds < 10)
        printk("0%u", rtc->seconds);
    else
        printk("%u", rtc->seconds);
}

void printk(str) const char str[];
{
    p_uint32 *p = (p_uint32*) &str;
    int strlen = phistr_len(str);
    p++;

    if (strlen == 1)
    {
        vga_putString(str);
        return;
    }

    for (p_uint32 i = 1; i < strlen; i++)
    {
        if (str[i - 1] == '%' && (str[i] == 'p' || str[i] == 's' ||
            str[i] == 'c' || str[i] == 'd' || str[i] == 'u' || str[i] == 't'))
        {
            switch (str[i])
            {
                case 's':
                    vga_putString((const char*)*p);
                    p++;
                    break;
                case 'd':
                    vga_putSignedNumber((p_sint32)*p);
                    p++;
                    break;
                case 'u':
                    vga_putUnsignedNumber((p_uint32)*p);
                    p++;
                     break;
                case 'c':
                    vga_putChar((char)*p);
                    p++;
                    break;
                case 'p':
                    vga_putAddress((p_size_t)*p, 1, 1);
                    p++;
                    break;
                case 't':
                    __printk_time((RTC*)*p);
                    p++;
                    break;
            }
            i++;
        }
        else
            vga_putChar(str[i - 1]);
    }

    if (str[strlen - 2] != '%')
    {
        vga_putChar(str[strlen - 1]);
    }
    else
    {
        p_uint32 s = strlen - 1;
        if (str[s] != 'p' && str[s] != 'c' && str[s] != 'd' && str[s] != 'u' &&
            str[s] != 's' && str[s] != 't')
            vga_putChar(str[s]);
    }

}

