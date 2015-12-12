CFLAGS = -std=gnu11 -c -DPhiOS32 -DPhiArch_i386 -m32 -nostdlib -nostdinc -fno-builtin -fno-stack-protector
INCLUDE = -Iinclude -I../libc/include -I../PhiAPI/include -Iarch/i386/include

all: phi_main.o | silent

phi_main.o: phi_main.c
	@gcc $(CFLAGS) -o $@ $< $(INCLUDE)

silent:
	@:

clean:
	-rm *.o
