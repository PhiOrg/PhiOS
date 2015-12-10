#ifdef PhiArch_i386
#include <common.h>
#endif

void sys_shutdown(void)
{
    outw(0xB004, 0x2000);
}

