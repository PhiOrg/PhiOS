#include <vga.h>
#include <idt.h>
#include <gdt.h>
#include <keyboard.h>

extern void enable_A20();

void phi_main(void)
{
        vga_clearScreen();

        idt_init();
        gdt_init();
        keyboard_init();
        enable_A20();

        return;
}

