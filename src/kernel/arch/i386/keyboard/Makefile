CFLAGS = -std=gnu11 -c -DPhiOS32 -m32 -nostdlib -nostdinc -fno-builtin -fno-stack-protector
INCLUDE = -I../include -I../../../libc/include -I../../../PhiAPI/include

all: keyboard.o

keyboard.o:
	gcc $(CFLAGS) keyboard.c $(INCLUDE)

clean:
	-rm *.o
