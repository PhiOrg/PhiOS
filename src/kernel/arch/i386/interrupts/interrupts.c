#include <interrupts.h>
#include <idt.h>
#include <gdt.h>

void interrupts_init(void)
{
    idt_init();
    gdt_init();
}

