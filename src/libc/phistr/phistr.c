#include <phistr.h>

p_size_t phistr_len(const char *str)
{
    if (str == P_NULL)
        return 0;

    p_size_t size = 0;
    for (; *str != 0; str++)
        size++;

    return size;
}

p_sint8 pshistr_cmp(const char *a, const char *b)
{
    if (!a || !b)
        return -2;

    while (*a == *b)
    {
        if (*a == 0)
            return 0;
        a++;
        b++;
    }

    return (p_uint8) *a < (p_uint8) *b ? -1 : 1;
}

void phistr_rev(char *str)
{
    if (!str)
        return;
    if (!*str)
        return;

    char t;
    for (char *a = str, *b = str + (phistr_len(str) - 1); a < b; a++, b++)
    {
        t = *a;
        *a = *b;
        *b = t;
    }
}

