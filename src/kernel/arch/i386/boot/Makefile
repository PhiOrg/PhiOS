AFLAGS = -f elf32

all: kernel.o | silent

kernel.o: kernel.asm
	@nasm $(AFLAGS) -o $@ $<

silent:
	@:

clean:
	-rm *.o
