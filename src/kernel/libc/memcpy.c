#include <memcpy.h>

void libc_memcpy(const char *source, char *destination, p_uint32 length)
{
    if (source == 0 || destination == 0)
        return;

    for (p_uint32 i = 0; i < length; i++)
        destination[i] = source[i];
}

