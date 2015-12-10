#include <phimem.h>

void phimem_cpy(const void *source, void *destination, p_size_t length)
{
    if (source == P_NULL || destination == P_NULL)
        return;

    const char *s = (char*) source;
    char *d = (char*) destination;
    while (length--)
    {
        *d = *s;
        d++;
        s++;
    }
}

void phimem_swap(void *a, void *b, p_size_t length)
{
    if (a == P_NULL || b == P_NULL)
        return;

    char *x = (char*) a, *y = (char*) b, t;

    while (length--)
    {
        t = *x;
        *x = *y;
        *y = t;
        x++;
        y++;
    }
}

void phimem_set(void *a, p_size_t length)
{
    if (a == P_NULL)
        return;

    char *x = (char*) a;

    while (length--)
    {
        *x = 0;
        x++;
    }
}

