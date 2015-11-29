CFLAGS = -std=gnu11 -c -DPhiOS32 -m32 -nostdlib -nostdinc -fno-builtin -fno-stack-protector
AFLAGS = -f elf32
INCLUDE = -I../../../include -I../include -I../../../../PhiAPI/include -I../../../../lib/include

all: pit.o gdt.o idt.o isr.o irq.o interrupts.o a_gdt.o a_idt.o a_interrupt.o

pit.o: pit.c
	gcc $(CFLAGS) -o $@ $< $(INCLUDE)

gdt.o: gdt.c
	gcc $(CFLAGS) -o $@ $< $(INCLUDE)

idt.o: idt.c
	gcc $(CFLAGS) -o $@ $< $(INCLUDE)

isr.o: isr.c
	gcc $(CFLAGS) -o $@ $< $(INCLUDE)

irq.o: irq.c
	gcc $(CFLAGS) -o $@ $< $(INCLUDE)

interrupts.o: interrupts.c
	gcc $(CFLAGS) -o $@ $< $(INCLUDE)

a_gdt.o: a_gdt.asm
	nasm $(AFLAGS) -o $@ $<

a_idt.o: a_idt.asm
	nasm $(AFLAGS) -o $@ $<

a_interrupt.o: a_interrupt.asm
	nasm $(AFLAGS) -o $@ $<

clean:
	-rm *.o
