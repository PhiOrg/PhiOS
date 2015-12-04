#include <vga.h>
#include <keyboard.h>
#include <multiboot.h>
#include <pmm.h>
#include <bitmap.h>
#include <phiio.h>
#include <vmm.h>

#ifdef PhiArch_i386
#include <idt.h>
#include <gdt.h>
#include <pit.h>
#endif

extern PageDirectory *vmm_kernelDirectory;

void phi_main(Multiboot *p, p_uint32 init_stack)
{
    vga_clearScreen();

    idt_init();
    gdt_init();
    keyboard_init();
    enable_A20();

    pmm_init(p->mem_lower + p->mem_upper);
    vmm_init();
    pit_init(50);

    vmm_allocPage(0xA0001000, 1, vmm_kernelDirectory);
    vmm_allocPage(0xC0001000, 1, vmm_kernelDirectory);
    vmm_allocPage(0xF0001000, 1, vmm_kernelDirectory);
    vmm_allocPage(0xB0001000, 1, vmm_kernelDirectory);
    vmm_allocPage(0xD0001000, 1, vmm_kernelDirectory);
    vmm_freePage(0xA0001000, vmm_kernelDirectory);

    p_uint8 *asd = (p_uint8*)0xA0001000;
    *asd = 5;

    return;
}

