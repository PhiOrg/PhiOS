#include <vga.h>
#include <idt.h>
#include <gdt.h>
#include <keyboard.h>
#include <multiboot.h>

extern void enable_A20();

void phi_main(Multiboot *p, p_uint32 init_stack)
{
    vga_clearScreen();

    idt_init();
    gdt_init();
    keyboard_init();
    enable_A20();

    return;
}

