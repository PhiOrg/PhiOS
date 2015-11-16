AFLAGS = -f elf32

all: kernel.o

kernel.o: kernel.asm
	nasm $(AFLAGS) -o $@ $<

clean:
	-rm *.o
