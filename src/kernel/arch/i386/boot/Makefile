AFLAGS = -f elf32

all: kernel.o

kernel.o:
	nasm $(AFLAGS) kernel.asm

clean:
	-rm *.o
