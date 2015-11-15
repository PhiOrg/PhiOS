CFLAGS = -std=gnu11 -c -DPhiOS32 -m32 -nostdlib -nostdinc -fno-builtin -fno-stack-protector
INCLUDE = -I../../../../libc/include -I../include -I../../../include

all: common.o

common.o:
	gcc $(CFLAGS) common.c $(INCLUDE)

clean:
	-rm *.o
