#ifndef PhiOS_common
#define PhiOS_common

#include <sys/types.h>

void outb(p_cuint16, p_cuint8);
p_uint8 inb(p_cuint16);
p_uint16 inw(p_cuint16);

#endif

