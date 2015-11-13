#ifndef PhiOS_isr
#define PhiOs_isr

#include <common.h>

typedef struct registers
{
   p_u32int ds;                  // Data segment selector
   p_u32int edi, esi, ebp, esp, ebx, edx, ecx, eax; // Pushed by pusha.
   p_u32int int_no, err_code;    // Interrupt number and error code (if applicable)
   p_u32int eip, cs, eflags, useresp, ss; // Pushed by the processor automatically.
} Registers;

#endif

