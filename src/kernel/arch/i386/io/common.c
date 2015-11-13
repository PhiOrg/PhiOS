#include <common.h>

/*
 * Write to port.
 */
void outb(p_cuint16 port, p_cuint8 value)
{
    asm volatile ("outb %1, %0" : : "dN" (port), "a" (value));
}

/*
 * Read from port.
 */
p_uint8 inb(p_cuint16 port)
{
    p_uint8 ret;
    asm volatile ("inb %1, %0" : "=a" (ret) : "dN" (port));
    return ret;
}

/*
 * Read from port.
 */
p_uint16 inw(p_cuint16 port)
{
    p_uint16 ret;
    asm volatile ("inw %1, %0" : "=a" (ret) : "dN" (port));
    return ret;
}

