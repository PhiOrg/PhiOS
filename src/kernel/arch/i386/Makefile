AFLAGS = -f elf32

all: a20.o | silent

a20.o: a20.asm
	@nasm $(AFLAGS) -o $@ $<

silent:
	@:

clean:
	-rm *.o
