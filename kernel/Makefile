CC=gcc
# AS=as
AS=nasm
CFLAGS= -m32 -ffreestanding -O2 -Wall -Wextra -nostdlib -nostdinc -fno-builtin -fno-stack-protector
# ASFLAGS= --32 -nostdlib
ASFLAGS=-f elf32
LDFLAGS= -melf_i386 -T linker.ld

OBJECTS=boot.o kernel.o util.o descriptor_tables.o isr.o interrupts.o gdt.o timer.o keyboard.o
# OBJECTS=../build/boot.o ../build/kernel.o ../build/util.o ../build/descriptor_tables.o \
 # ../build/isr.o ../build/interrupts.o ../build/gdt.o ../build/timer.o ../build/keyboard.o

all: os clean

os: $(OBJECTS)
	ld $(LDFLAGS) $(OBJECTS) -o ../build/kernel.elf
	cp ../build/kernel.elf ../iso/boot/kernel.elf

clean:
	-rm *.o
	-rm ../build/*.o

%.o: %.s
	$(AS) $(ASFLAGS) $< -o $@


%.o: %.c *.h
	$(CC) $(CFLAGS) -c $< -o $@

# clean:
	# rm ../build/*.o
