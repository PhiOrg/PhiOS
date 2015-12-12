ifndef VERBOSE
    MAKEFLAGS += --no-print-directory
endif

FLAGS = -m elf_i386 -T kernel/arch/i386/linker.ld -o
OBJS = kernel/arch/i386/boot/kernel.o \
       kernel/phi_main.o \
       kernel/vga/vga.o \
       kernel/keyboard/keyboard.o \
       kernel/arch/i386/io/common.o \
       kernel/arch/i386/a20.o \
       kernel/arch/i386/interrupts/pit.o \
       kernel/arch/i386/interrupts/gdt.o \
       kernel/arch/i386/interrupts/idt.o \
       kernel/arch/i386/interrupts/irq.o \
       kernel/arch/i386/interrupts/isr.o \
       kernel/arch/i386/interrupts/interrupts.o \
       kernel/arch/i386/interrupts/a_gdt.o \
       kernel/arch/i386/interrupts/a_idt.o \
       kernel/arch/i386/interrupts/a_interrupt.o \
       kernel/memory/pmm.o \
       kernel/memory/kheap.o \
       kernel/memory/bitmap.o \
       kernel/memory/vmm.o \
       kernel/memory/heap.o \
       kernel/system/sys.o \
       kernel/system/rtc.o \
       libc/phimem/phimem.o \
       libc/phistr/phistr.o \
       libc/phiio/phiio.o

myApp:
	@tput setaf 2
	@echo "COMPILING LIBC"
	
	@echo "Compiling phimem"
	@tput sgr 0
	@cd libc/phimem; make
	
	@tput setaf 2
	@echo "Compiling phistr"
	@tput sgr 0
	@cd libc/phistr; make
	
	@tput setaf 2
	@echo "Compiling phiio"
	@tput sgr 0
	@cd libc/phiio; make
	
	
	
	@tput setaf 2
	@echo "\nCOMPILING KERNEL"
	
	@echo "Compiling kernel"
	@tput sgr 0
	@cd kernel; make
	
	@tput setaf 2
	@echo "Compiling i386"
	@tput sgr 0
	@cd kernel/arch/i386; make
	
	@tput setaf 2
	@echo "Compiling vga"
	@tput sgr 0
	@cd kernel/vga; make
	
	@tput setaf 2
	@echo "Compiling keyboard"
	@tput sgr 0
	@cd kernel/keyboard; make
	
	@tput setaf 2
	@echo "Compiling memory"
	@tput sgr 0
	@cd kernel/memory; make
	
	@tput setaf 2
	@echo "Compiling system"
	@tput sgr 0
	@cd kernel/system; make
	
	@tput setaf 2
	@echo "Compiling io"
	@tput sgr 0
	@cd kernel/arch/i386/io; make
	
	@tput setaf 2
	@echo "Compiling interrupts"
	@tput sgr 0
	@cd kernel/arch/i386/interrupts; make
	
	@tput setaf 2
	@echo "Compiling boot"
	@tput sgr 0
	@cd kernel/arch/i386/boot; make
	
	
	@echo ""
	
	
	@tput setaf 2
	@echo "Linking ..."
	@tput sgr 0
	@ld $(FLAGS) PhiOS.elf $(OBJS)
	
	
	@tput setaf 2
	@echo ""
	@echo "Creating .iso"
	@tput sgr 0
	@cp PhiOS.elf ../isodir/boot/PhiOS.elf
	@grub-mkrescue -o PhiOS.iso ../isodir

clean:
	cd libc/phimem; make clean
	cd libc/phistr; make clean
	cd libc/phiio; make clean
	cd kernel; make clean
	cd kernel/arch/i386; make clean
	cd kernel/vga; make clean
	cd kernel/keyboard; make clean
	cd kernel/memory; make clean
	cd kernel/system; make clean
	cd kernel/arch/i386/io; make clean
	cd kernel/arch/i386/interrupts; make clean
	cd kernel/arch/i386/boot; make clean
	rm PhiOS.elf
	rm PhiOS.iso
