#include <gdt.h>
#include <common.h>

extern void a_gdt_flush(p_uint32);

gdt_entry_t gdt_entries[5];
gdt_ptr_t   gdt_ptr;

// Set the value of one GDT entry.
static void __gdt_setGate(p_sint32 num, p_uint32 base, p_uint32 limit,
                          p_uint8 access, p_uint8 gran)
{
   gdt_entries[num].base_low    = (base & 0xFFFF);
   gdt_entries[num].base_middle = (base >> 16) & 0xFF;
   gdt_entries[num].base_high   = (base >> 24) & 0xFF;

   gdt_entries[num].limit_low   = (limit & 0xFFFF);
   gdt_entries[num].granularity = (limit >> 16) & 0x0F;

   gdt_entries[num].granularity |= gran & 0xF0;
   gdt_entries[num].access      = access;
}

void gdt_init(void)
{
   gdt_ptr.limit = (sizeof(gdt_entry_t) * 5) - 1;
   gdt_ptr.base  = (p_uint32)&gdt_entries;

   __gdt_setGate(0, 0, 0, 0, 0);                // Null segment
   __gdt_setGate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF); // Code segment
   __gdt_setGate(2, 0, 0xFFFFFFFF, 0x92, 0xCF); // Data segment
   __gdt_setGate(3, 0, 0xFFFFFFFF, 0xFA, 0xCF); // User mode code segment
   __gdt_setGate(4, 0, 0xFFFFFFFF, 0xF2, 0xCF); // User mode data segment

   a_gdt_flush((p_uint32)&gdt_ptr);
}

