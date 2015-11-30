#include <phiio.h>
#include <vga.h>
#include <phistr.h>

void printk(str) char str[];
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
            str[i] == 'c' || str[i] == 'd' || str[i] == 'u'))
        {
            switch (str[i])
            {
                case 's':
                    vga_putString((const char*)*p);
                    p++;
                    break;
                case 'd':
                    vga_putSignedNumber(*p);
                    p++;
                    break;
                case 'u':
                    vga_putUnsignedNumber(*p);
                    p++;
                     break;
                case 'c':
                    vga_putChar(*p);
                    p++;
                    break;
                case 'p':
                    vga_putAddress(*p, 1, 1);
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
        if (str[s] != 'p' && str[s] != 'c' && str[s] != 'd' && str[s] != 'u')
            vga_putChar(str[s]);
    }

}

