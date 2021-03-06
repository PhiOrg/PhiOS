#include <idt.h>
#include <common.h>
#include <irq.h>

extern void a_idt_flush(p_uint32);

idt_entry_t idt_entries[256];
idt_ptr_t   idt_ptr;

static void __idt_setGate(p_uint8 num, p_uint32 base, p_uint16 sel, p_uint8 flags)
{
    idt_entries[num].base_lo = base & 0xFFFF;
    idt_entries[num].base_hi = (base >> 16) & 0xFFFF;
    idt_entries[num].sel     = sel;
    idt_entries[num].always0 = 0;

    /************************************************************************
     * We must uncomment the OR below when we get to using user-mode.       *
     * It sets the interrupt gate's privilege level to 3.                   *
     ************************************************************************/
    idt_entries[num].flags   = flags /* | 0x60 */;
}

static void __idt_memset(char *ptr, p_size_t size)
{
    for (p_size_t i = 0; i < size; i++)
        ptr[i] = 0;
}

void idt_init(void)
{
    idt_ptr.limit = sizeof(idt_entry_t) * 256 -1;
    idt_ptr.base  = (p_uint32)&idt_entries;

    __idt_memset((char*)&idt_entries, sizeof(idt_entry_t)*256);

    // Remap the irq table.
    outb(0x20, 0x11);
    outb(0xA0, 0x11);
    outb(0x21, 0x20);
    outb(0xA1, 0x28);
    outb(0x21, 0x04);
    outb(0xA1, 0x02);
    outb(0x21, 0x01);
    outb(0xA1, 0x01);
    outb(0x21, 0x0);
    outb(0xA1, 0x0);

    __idt_setGate( 0, (p_uint32)isr0 , 0x08, 0x8E);
    __idt_setGate( 1, (p_uint32)isr1 , 0x08, 0x8E);
    __idt_setGate( 2, (p_uint32)isr2 , 0x08, 0x8E);
    __idt_setGate( 3, (p_uint32)isr3 , 0x08, 0x8E);
    __idt_setGate( 4, (p_uint32)isr4 , 0x08, 0x8E);
    __idt_setGate( 5, (p_uint32)isr5 , 0x08, 0x8E);
    __idt_setGate( 6, (p_uint32)isr6 , 0x08, 0x8E);
    __idt_setGate( 7, (p_uint32)isr7 , 0x08, 0x8E);
    __idt_setGate( 8, (p_uint32)isr8 , 0x08, 0x8E);
    __idt_setGate( 9, (p_uint32)isr9 , 0x08, 0x8E);
    __idt_setGate(10, (p_uint32)isr10, 0x08, 0x8E);
    __idt_setGate(11, (p_uint32)isr11, 0x08, 0x8E);
    __idt_setGate(12, (p_uint32)isr12, 0x08, 0x8E);
    __idt_setGate(13, (p_uint32)isr13, 0x08, 0x8E);
    __idt_setGate(14, (p_uint32)isr14, 0x08, 0x8E);
    __idt_setGate(15, (p_uint32)isr15, 0x08, 0x8E);
    __idt_setGate(16, (p_uint32)isr16, 0x08, 0x8E);
    __idt_setGate(17, (p_uint32)isr17, 0x08, 0x8E);
    __idt_setGate(18, (p_uint32)isr18, 0x08, 0x8E);
    __idt_setGate(19, (p_uint32)isr19, 0x08, 0x8E);
    __idt_setGate(20, (p_uint32)isr20, 0x08, 0x8E);
    __idt_setGate(21, (p_uint32)isr21, 0x08, 0x8E);
    __idt_setGate(22, (p_uint32)isr22, 0x08, 0x8E);
    __idt_setGate(23, (p_uint32)isr23, 0x08, 0x8E);
    __idt_setGate(24, (p_uint32)isr24, 0x08, 0x8E);
    __idt_setGate(25, (p_uint32)isr25, 0x08, 0x8E);
    __idt_setGate(26, (p_uint32)isr26, 0x08, 0x8E);
    __idt_setGate(27, (p_uint32)isr27, 0x08, 0x8E);
    __idt_setGate(28, (p_uint32)isr28, 0x08, 0x8E);
    __idt_setGate(29, (p_uint32)isr29, 0x08, 0x8E);
    __idt_setGate(30, (p_uint32)isr30, 0x08, 0x8E);
    __idt_setGate(31, (p_uint32)isr31, 0x08, 0x8E);

    __idt_setGate(32, (p_uint32)irq0, 0x08, 0x8E);
    __idt_setGate(33, (p_uint32)irq1, 0x08, 0x8E);
    __idt_setGate(34, (p_uint32)irq2, 0x08, 0x8E);
    __idt_setGate(35, (p_uint32)irq3, 0x08, 0x8E);
    __idt_setGate(36, (p_uint32)irq4, 0x08, 0x8E);
    __idt_setGate(37, (p_uint32)irq5, 0x08, 0x8E);
    __idt_setGate(38, (p_uint32)irq6, 0x08, 0x8E);
    __idt_setGate(39, (p_uint32)irq7, 0x08, 0x8E);
    __idt_setGate(40, (p_uint32)irq8, 0x08, 0x8E);
    __idt_setGate(41, (p_uint32)irq9, 0x08, 0x8E);
    __idt_setGate(42, (p_uint32)irq10, 0x08, 0x8E);
    __idt_setGate(43, (p_uint32)irq11, 0x08, 0x8E);
    __idt_setGate(44, (p_uint32)irq12, 0x08, 0x8E);
    __idt_setGate(45, (p_uint32)irq13, 0x08, 0x8E);
    __idt_setGate(46, (p_uint32)irq14, 0x08, 0x8E);
    __idt_setGate(47, (p_uint32)irq15, 0x08, 0x8E);

    a_idt_flush((p_uint32)&idt_ptr);
}

