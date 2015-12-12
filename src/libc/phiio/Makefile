CFLAGS = -std=gnu11 -c -DPhiOS32 -m32 -nostdlib -nostdinc -fno-builtin -fno-stack-protector
INCLUDE = -I../include -I../../kernel/arch/i386/include -I../../PhiAPI/include -I../../kernel/include

all: phiio.o | silent

phiio.o: phiio.c
	@gcc $(CFLAGS) -o $@ $< $(INCLUDE)

silent:
	@:

clean:
	-rm *.o
