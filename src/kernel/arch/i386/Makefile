CFLAGS = -std=gnu11 -c -DPhiOS32 -m32 -nostdlib -nostdinc -fno-builtin -fno-stack-protector
INCLUDE = -Iinclude -I../../libc/include -I../../PhiAPI/include
AFLAGS = -f elf32

all: a20.o phi_main.o

phi_main.o:
	gcc $(CFLAGS) phi_main.c $(INCLUDE)
a20.o:
	nasm $(AFLAGS) a20.asm

clean:
	-rm *.o
