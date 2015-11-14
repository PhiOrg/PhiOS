gcc -m32 -std=gnu99 -c -o ../bin/phi_main.o kernel/phi_main.c -Ilibc/include -Ikernel/include -Ikernel/arch/i386/include
gcc -m32 -std=gnu99 -nostdlib -fno-stack-protector -c -o ../bin/vga.o kernel/drivers/vga.c -Ilibc/include -Ikernel/include -Ikernel/arch/i386/include
gcc -m32 -std=gnu99 -c -o ../bin/keyboard.o kernel/drivers/keyboard.c -Ilibc/include -Ikernel/include -Ikernel/arch/i386/include
gcc -m32 -std=gnu99 -c -o ../bin/memcpy.o libc/memcpy.c -Ilibc/include -Ikernel/include -Ikernel/arch/i386/include
gcc -m32 -std=gnu99 -c -o ../bin/common.o kernel/arch/i386/io/common.c -Ilibc/include -Ikernel/include -Ikernel/arch/i386/include
gcc -m32 -std=gnu99 -c -o ../bin/gdt.o kernel/arch/i386/interrupts/gdt.c -Ilibc/include -Ikernel/include -Ikernel/arch/i386/include
gcc -m32 -std=gnu99 -c -o ../bin/idt.o kernel/arch/i386/interrupts/idt.c -Ilibc/include -Ikernel/include -Ikernel/arch/i386/include
gcc -m32 -std=gnu99 -c -o ../bin/isr.o kernel/arch/i386/interrupts/isr.c -Ilibc/include -Ikernel/include -Ikernel/arch/i386/include
gcc -m32 -std=gnu99 -c -o ../bin/irq.o kernel/arch/i386/interrupts/irq.c -Ilibc/include -Ikernel/include -Ikernel/arch/i386/include
gcc -m32 -std=gnu99 -c -o ../bin/interrupts.o kernel/arch/i386/interrupts/interrupts.c -Ilibc/include -Ikernel/include -Ikernel/arch/i386/include

nasm -f elf32 kernel/arch/i386/boot/kernel.asm -o ../bin/kernel.o
nasm -f elf32 kernel/arch/i386/a20.asm -o ../bin/a20.o
nasm -f elf32 kernel/arch/i386/interrupts/a_gdt.asm -o ../bin/a_gdt.o
nasm -f elf32 kernel/arch/i386/interrupts/a_idt.asm -o ../bin/a_idt.o
nasm -f elf32 kernel/arch/i386/interrupts/a_interrupt.asm -o ../bin/a_interrupt.o

ld -m elf_i386 -T link.ld -o ../bin/kernel.elf ../bin/kernel.o ../bin/phi_main.o ../bin/vga.o ../bin/memcpy.o ../bin/common.o ../bin/gdt.o ../bin/idt.o ../bin/isr.o ../bin/a_gdt.o ../bin/a_idt.o ../bin/a_interrupt.o ../bin/interrupts.o ../bin/irq.o ../bin/keyboard.o ../bin/a20.o
