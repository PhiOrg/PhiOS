#include <common.h>
#include <isr.h>

isrFunction interruptHandlers[256];

void isr_registerInterruptHandler(p_cuint8 position, isrFunction function)
{
    interruptHandlers[position] = function;
}

/*
 * This is called from ASM interrupt handler.
 */
void isr_handler(Registers regs)
{
    if (interruptHandlers[regs.int_no] != 0)
        interruptHandlers[regs.int_no](regs);
}

