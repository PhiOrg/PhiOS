CFLAGS = -std=gnu11 -c -DPhiOS32 -m32 -nostdlib -nostdinc -fno-builtin -fno-stack-protector
INCLUDE = -I../include -I../../kernel/arch/i386/include -I../../PhiAPI/include

all: phimem.o | silent

phimem.o: phimem.c
	@gcc $(CFLAGS) -o $@ $< $(INCLUDE)

silent:
	@:

clean:
	-rm *.o
