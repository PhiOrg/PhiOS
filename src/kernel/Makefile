CFLAGS = -std=gnu11 -c -DPhiOS32 -DPhiArchi386 -m32 -nostdlib -nostdinc -fno-builtin -fno-stack-protector
INCLUDE = -Iinclude -I../libc/include -I../PhiAPI/include -Iarch/i386/include

all: phi_main.o

phi_main.o:
	gcc $(CFLAGS) phi_main.c $(INCLUDE)

clean:
	-rm *.o
