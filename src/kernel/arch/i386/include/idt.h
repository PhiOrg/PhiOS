/*
 * idt.h -- interrupt descriptor table
 */
#ifndef PhiOS_idt
#define PhiOS_idt

#include <sys/types.h>

// A struct describing an interrupt gate.
struct idt_entry_struct
{
    p_uint16 base_lo;             // The lower 16 bits of the address to jump to when this interrupt fires.
    p_uint16 sel;                 // Kernel segment selector.
    p_uint8  always0;             // This must always be zero.
    p_uint8  flags;               // More flags. See documentation.
    p_uint16 base_hi;             // The upper 16 bits of the address to jump to.
} __attribute__((packed));

typedef struct idt_entry_struct idt_entry_t;

// A struct describing a pointer to an array of interrupt handlers.
// This is in a format suitable for giving to 'lidt'.
struct idt_ptr_struct
{
    p_uint16 limit;
    p_uint32 base;                // The address of the first element in our idt_entry_t array.
} __attribute__((packed));

typedef struct idt_ptr_struct idt_ptr_t;

// These extern directives let us access the addresses of our ASM ISR handlers.
extern void isr0 ();
extern void isr1 ();
extern void isr2 ();
extern void isr3 ();
extern void isr4 ();
extern void isr5 ();
extern void isr6 ();
extern void isr7 ();
extern void isr8 ();
extern void isr9 ();
extern void isr10();
extern void isr11();
extern void isr12();
extern void isr13();
extern void isr14();
extern void isr15();
extern void isr16();
extern void isr17();
extern void isr18();
extern void isr19();
extern void isr20();
extern void isr21();
extern void isr22();
extern void isr23();
extern void isr24();
extern void isr25();
extern void isr26();
extern void isr27();
extern void isr28();
extern void isr29();
extern void isr30();
extern void isr31();

void idt_init(void);

#endif

