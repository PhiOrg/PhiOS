AFLAGS = -f elf32

all: a20.o page.o

a20.o: a20.asm
	nasm $(AFLAGS) -o $@ $<

page.o: page.asm
	nasm $(AFLAGS) -o $@ $<

clean:
	-rm *.o
