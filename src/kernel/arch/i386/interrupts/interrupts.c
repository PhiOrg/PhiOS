#include <interrupts.h>
#include <idt.h>
#include <gdt.h>
#include <isr.h>

extern isrFunction interruptHandlers[];

static void __interrupts_memset(char *ptr, p_cuint32 size)
{
    for (p_uint32 i = 0; i < size; i++)
        ptr[i] = 0;
}

void interrupts_init(void)
{
    idt_init();
    gdt_init();

    __interrupts_memset((char*)&interruptHandlers, sizeof(isrFunction) * 256);
}

