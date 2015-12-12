CFLAGS = -std=gnu11 -c -DPhiOS32 -DPhiArch_i386 -m32 -nostdlib -nostdinc -fno-builtin -fno-stack-protector
INCLUDE = -I../include -I../../libc/include -I../../PhiAPI/include -I../arch/i386/include

all: vga.o | silent

vga.o: vga.c
	@gcc $(CFLAGS) -o $@ $< $(INCLUDE)

silent:
	@:

clean:
	-rm *.o
