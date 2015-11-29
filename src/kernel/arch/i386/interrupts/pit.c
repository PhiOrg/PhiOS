#include <pit.h>
#include <common.h>
#include <irq.h>
#include <isr.h>

void __pit_handler(Registers regs)
{
}

void pit_init(p_uint32 frequency)
{
    isr_registerInterruptHandler(IRQ0, __pit_handler);

    p_uint32 divisor = 1193180 / frequency;

    outb(0x43, 0x36);

    p_uint8 l = (p_uint8) (divisor & 0xFF);
    p_uint8 h = (p_uint8) ((divisor >> 8) & 0xFF);

    outb(0x40, l);
    outb(0x40, h);
}

