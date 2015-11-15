CFLAGS = -std=gnu11 -c -DPhiOS32 -m32 -nostdlib -nostdinc -fno-builtin -fno-stack-protector
INCLUDE = -I../../../include -I../include -I../../../../libc/include -I../../../../PhiAPI/include

all: common.o

common.o:
	gcc $(CFLAGS) common.c $(INCLUDE)

clean:
	-rm *.o
