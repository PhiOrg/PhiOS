CFLAGS = -std=gnu11 -c -m32 -nostdlib -nostdinc -fno-builtin -fno-stack-protector
INCLUDE = -Iinclude -I../arch/i386/include

all: memcpy.o

memcpy.o:
	gcc $(CFLAGS) memcpy.c $(INCLUDE)

clean:
	-rm *.o
