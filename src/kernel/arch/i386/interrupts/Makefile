CFLAGS = -std=gnu11 -c -DPhiOS32 -m32 -nostdlib -nostdinc -fno-builtin -fno-stack-protector
AFLAGS = -f elf32
INCLUDE = -I../../../../libc/include -I../include -I../../../include

all: gdt.o idt.o isr.o irq.o interrupts.o a_gdt.o a_idt.o a_interrupt.o

gdt.o:
	gcc $(CFLAGS) gdt.c $(INCLUDE)

idt.o:
	gcc $(CFLAGS) idt.c $(INCLUDE)

isr.o:
	gcc $(CFLAGS) isr.c $(INCLUDE)

irq.o:
	gcc $(CFLAGS) irq.c $(INCLUDE)

interrupts.o:
	gcc $(CFLAGS) interrupts.c $(INCLUDE)

a_gdt.o:
	nasm $(AFLAGS) a_gdt.asm

a_idt.o:
	nasm $(AFLAGS) a_idt.asm

a_interrupt.o:
	nasm $(AFLAGS) a_interrupt.asm

clean:
	-rm *.o
