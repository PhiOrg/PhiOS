CFLAGS = -std=gnu11 -c -DPhiOS32 -DPhiArchi386 -m32 -nostdlib -nostdinc -fno-builtin -fno-stack-protector
INCLUDE = -I../include -I../../libc/include -I../../PhiAPI/include -I../arch/i386/include

all: vga.o

vga.o:
	gcc $(CFLAGS) vga.c $(INCLUDE)

clean:
	-rm *.o
