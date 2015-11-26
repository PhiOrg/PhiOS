CFLAGS = -std=gnu11 -c -DPhiOS32 -DPhiArchi386 -m32 -nostdlib -nostdinc -fno-builtin -fno-stack-protector
INCLUDE = -I../include -I../../libc/include -I../../PhiAPI/include -I../arch/i386/include

all: pmm.o kheap.o bitmap.o

pmm.o: pmm.c
	gcc $(CFLAGS) -o $@ $< $(INCLUDE)

kheap.o: kheap.c
	gcc $(CFLAGS) -o $@ $< $(INCLUDE)

bitmap.o: bitmap.c
	gcc $(CFLAGS) -o $@ $< $(INCLUDE)

clean:
	-rm *.o
