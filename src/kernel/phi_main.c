#include <vga.h>
#include <keyboard.h>
#include <multiboot.h>
#include <pmm.h>
#include <bitmap.h>
#include <phiio.h>
#include <vmm.h>
#include <rtc.h>
#include <heap.h>

#ifdef PhiArch_i386
#include <idt.h>
#include <gdt.h>
#include <pit.h>
#include <common.h>
#endif

extern void enable_A20();

extern PageDirectory *vmm_kernelDirectory;
extern p_size_t kheap_placementAddress;
extern p_size_t kernel_end;

int v[1024];
void phi_main(Multiboot *p, p_uint32 init_stack)
{
    vga_clearScreen();

    idt_init();
    gdt_init();
    keyboard_init();
    enable_A20();

    rtc_init();

    pmm_init(p->mem_lower + p->mem_upper);
    vmm_init();
    pit_init(50);

    Heap *heap = heap_create(vmm_kernelDirectory);
    char *c = heap_malloc(heap, 10);
    printk("%p\n", heap->head);
    printk("%p %p\n", heap, &(heap->size));
    printk("%p %p\n", &(heap->used), &(heap->head));

    printk("%p\n", c);

    return;
}

