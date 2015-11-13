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

void idt_init(void);

#endif

