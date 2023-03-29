CC=gcc
# AS=as
AS=nasm
CFLAGS= -m32 -ffreestanding -O2 -Wall -Wextra -nostdlib -nostdinc -fno-builtin -fno-stack-protector
# ASFLAGS= --32 -nostdlib
ASFLAGS=-f elf32
LDFLAGS= -melf_i386 -T linker.ld

OBJECTS=boot.o kernel.o util.o descriptor_tables.o isr.o interrupts.o gdt.o timer.o keyboard.o


os: $(OBJECTS)
	ld $(LDFLAGS) $(OBJECTS) -o ../build/myos.bin

clean:
	-rm *.o

.s.o:
	$(AS) $(ASFLAGS) $<


%.o: %.c *.h
	$(CC) $(CFLAGS) -c $< -o $@

# clean:
	# rm ../build/*.o
