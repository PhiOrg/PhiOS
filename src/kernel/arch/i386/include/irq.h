/*
 * irq.h -- intrerrupt requests
 */
#ifndef PhiOS_irq
#define PhiOS_irq

#include <isr.h>

#define IRQ0 32 // Programmable Interrupt Timer Interrupt (handled)
#define IRQ1 33 // Keyboard Interrupt (handled)
#define IRQ2 34 // Cascade (used internally by the two PICs. never raised)
#define IRQ3 35 // COM2 (if enabled)
#define IRQ4 36 // COM1 (if enabled)
#define IRQ5 37 // LPT2 (if enabled)
#define IRQ6 38 // Floppy Disk
#define IRQ7 39 // LPT1 / Unreliable "spurious" interrupt (usually)
#define IRQ8 40 // CMOS real-time clock (if enabled)
#define IRQ9 41 // Free for peripherals / legacy SCSI / NIC
#define IRQ10 42 // Free for peripherals / SCSI / NIC
#define IRQ11 43 // Free for peripherals / SCSI / NIC
#define IRQ12 44 // PS2 Mouse
#define IRQ13 45 // FPU / Coprocessor / Inter-processor
#define IRQ14 46 // Primary ATA Hard Disk
#define IRQ15 47 // Secondary ATA Hard Disk

extern void irq0 ();
extern void irq1 ();
extern void irq2 ();
extern void irq3 ();
extern void irq4 ();
extern void irq5 ();
extern void irq6 ();
extern void irq7 ();
extern void irq8 ();
extern void irq9 ();
extern void irq10();
extern void irq11();
extern void irq12();
extern void irq13();
extern void irq14();
extern void irq15();

void irq_handler(Registers);

#endif

