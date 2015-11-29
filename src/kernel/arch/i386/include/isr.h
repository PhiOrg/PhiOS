/*
 *  isr.h -- interrupt service routines
 */
#ifndef PhiOS_isr
#define PhiOS_isr

#include <sys/types.h>

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

typedef struct registers
{
   p_u32int ds;                  // Data segment selector
   p_u32int edi, esi, ebp, esp, ebx, edx, ecx, eax; // Pushed by pusha.
   p_u32int int_no, err_code;    // Interrupt number and error code (if applicable)
   p_u32int eip, cs, eflags, useresp, ss; // Pushed by the processor automatically.
} Registers;

typedef void (*isrFunction)(Registers);

void isr_registerInterruptHandler(p_cuint8, isrFunction);

void isr_handler(Registers);

#endif

