CFLAGS = -std=gnu11 -c -m32 -nostdlib -nostdinc -fno-builtin -fno-stack-protector
INCLUDE = -I../libc/include -Iinclude -Iarch/i386/include

all: phi_main.o

phi_main.o:
	gcc $(CFLAGS) phi_main.c $(INCLUDE)

clean:
	-rm *.o
