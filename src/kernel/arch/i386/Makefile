AFLAGS = -f elf32

all: a20.o

a20.o: a20.asm
	nasm $(AFLAGS) -o $@ $<

clean:
	-rm *.o
