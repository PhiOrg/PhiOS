CFLAGS = -std=gnu11 -c -DPhiOS32 -m32 -nostdlib -nostdinc -fno-builtin -fno-stack-protector
INCLUDE = -I../include -I../../kernel/arch/i386/include -I../../PhiAPI/include

all: phimem.o

phimem.o:
	gcc $(CFLAGS) phimem.c $(INCLUDE)

clean:
	-rm *.o
