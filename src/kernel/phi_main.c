#include <vga.h>
#include <idt.h>
#include <gdt.h>

void phi_main(void)
{
        const char *a = "hello\n";

        vga_clearScreen();
        vga_putString(a);

        idt_init();
        gdt_init();
        asm volatile ("int $0x3");
        asm volatile ("int $0x4");

        return;
}

