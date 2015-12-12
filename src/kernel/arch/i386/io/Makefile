CFLAGS = -std=gnu11 -c -DPhiOS32 -m32 -nostdlib -nostdinc -fno-builtin -fno-stack-protector
INCLUDE = -I../../../include -I../include -I../../../../libc/include -I../../../../PhiAPI/include

all: common.o | silent

common.o: common.c
	@gcc $(CFLAGS) -o $@ $< $(INCLUDE)

silent:
	@:

clean:
	-rm *.o
