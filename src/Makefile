FLAGS = -m elf_i386 -T kernel/arch/i386/linker.ld -o
OBJS = kernel/arch/i386/boot/kernel.o \
       kernel/arch/i386/phi_main.o \
       kernel/arch/i386/vga/vga.o \
       kernel/arch/i386/keyboard/keyboard.o \
       kernel/arch/i386/io/common.o \
       kernel/arch/i386/a20.o \
       kernel/arch/i386/interrupts/gdt.o \
       kernel/arch/i386/interrupts/idt.o \
       kernel/arch/i386/interrupts/irq.o \
       kernel/arch/i386/interrupts/isr.o \
       kernel/arch/i386/interrupts/interrupts.o \
       kernel/arch/i386/interrupts/a_gdt.o \
       kernel/arch/i386/interrupts/a_idt.o \
       kernel/arch/i386/interrupts/a_interrupt.o \
       kernel/libc/memcpy.o

myApp:
	@echo "Compiling libc"
	cd kernel/libc; make
	@echo "\nCompiling kernel"
	cd kernel/arch/i386; make
	cd kernel/arch/i386/vga; make
	cd kernel/arch/i386/keyboard; make
	cd kernel/arch/i386/io; make
	cd kernel/arch/i386/interrupts; make
	cd kernel/arch/i386/boot; make
	ld $(FLAGS) PhiOS.elf $(OBJS)
	cp PhiOS.elf ../isodir/boot/PhiOS.elf
	grub-mkrescue -o PhiOS.iso ../isodir

clean:
	cd kernel/libc; make clean
	cd kernel/arch/i386; make clean
	cd kernel/arch/i386/vga; make clean
	cd kernel/arch/i386/keyboard; make clean
	cd kernel/arch/i386/io; make clean
	cd kernel/arch/i386/interrupts; make clean
	cd kernel/arch/i386/boot; make clean
	rm PhiOS.elf
	rm PhiOS.iso
