#include <common.h>
#include <isr.h>
#include <vga.h>

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
    //vga_putString("recieved interrupt: ");
    //vga_putUnsignedNumber(regs.int_no);
    //vga_putChar('\n');

    if (interruptHandlers[regs.int_no] != 0)
        interruptHandlers[regs.int_no](regs);
}

