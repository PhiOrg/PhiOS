#include <irq.h>
#include <common.h>

extern isrFunction interruptHandlers[];

void irq_handler(Registers regs)
{
    if (regs.int_no >= 40)
        outb(0xA0, 0x20);

    outb(0x20, 0x20);

    if (interruptHandlers[regs.int_no] != 0)
        interruptHandlers[regs.int_no](regs);
}

