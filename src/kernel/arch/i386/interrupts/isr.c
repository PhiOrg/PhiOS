#include <common.h>
#include <isr.h>
#include <vga.h>

// This gets called from ASM interrupt handler stub.
void isr_handler(Registers regs)
{
    vga_putString("recieved interrupt: ");
    vga_putUnsignedNumber(regs.int_no);
    vga_putChar('\n');
}

