CFLAGS = -std=gnu11 -c -m32 -nostdlib -nostdinc -fno-builtin -fno-stack-protector
INCLUDE = -I../include -I../../libc/include -I../arch/i386/include

all: vga.o keyboard.o

vga.o:
	gcc $(CFLAGS) vga.c $(INCLUDE)
keyboard.o:
	gcc $(CFLAGS) keyboard.c $(INCLUDE)

clean:
	-rm *.o
