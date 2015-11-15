#include <vga.h>
#include <keyboard.h>
#include <multiboot.h>

#ifdef PhiArchi386
#include <idt.h>
#include <gdt.h>
#endif

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

