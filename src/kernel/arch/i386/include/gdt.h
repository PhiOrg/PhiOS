#ifndef PhiOS_gdt
#define PhiOS_gdt

#include <common.h>

// This structure contains the value of one GDT entry.
// We use the attribute 'packed' to tell GCC not to change
// any of the alignment in the structure.
struct gdt_entry_struct
{
   p_uint16 limit_low;           // The lower 16 bits of the limit.
   p_uint16 base_low;            // The lower 16 bits of the base.
   p_uint8  base_middle;         // The next 8 bits of the base.
   p_uint8  access;              // Access flags, determine what ring this segment can be used in.
   p_uint8  granularity;
   p_uint8  base_high;           // The last 8 bits of the base.
} __attribute__((packed));

struct gdt_ptr_struct
{
   p_uint16 limit;               // The upper 16 bits of all selector limits.
   p_uint32 base;                // The address of the first gdt_entry_t struct.
} __attribute__((packed));

typedef struct gdt_entry_struct gdt_entry_t;
typedef struct gdt_ptr_struct gdt_ptr_t;

void gdt_init(void);

#endif

