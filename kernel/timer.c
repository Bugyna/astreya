// timer.c -- Initialises the PIT, and handles clock updates.
// Written for JamesM's kernel development tutorials.

#include "util.h"
#include "timer.h"
#include "isr.h"

u32int tick = 0;

static void timer_callback(registers_t regs)
{
	// regs
	// BYTE d = inb(0x71);
	tick++;
	u16 oy = row_index, ox = column_index;
	move_cursor(20, 1);
	clear_line(1);
	// printf("tick: %d", (int)(tick / 100));

	outb(0x70, (1 << 7) | 0x0B);
	int x = inb(0x71);
	
	outb(0x70, (1 << 7) | 0x00);
	x = inb(0x71);
	printf("tick: %d %d %d", (int)(tick), x, ((x >> 4) & 0xF) * 10 + (x & 0xF));
	
	// char x = inb(0x71);
	// printf("what: %d\n", x);
	move_cursor(ox, oy);
	outb(0x70, 0x0C);	// select register C
	inb(0x71);
}



void init_timer(u32int frequency)
{	
	// Firstly, register our timer callback.
	// register_interrupt_handler(IRQ0, &timer_callback);
	register_interrupt_handler(IRQ8, &timer_callback);

	// The value we send to the PIT is the value to divide it's input clock
	// (1193180 Hz) by, to get our required frequency. Important to note is
	// that the divisor must be small enough to fit into 16-bits.
	u32int divisor = 1193180 / frequency;

	// Send the command byte.
	outb(0x43, 0x36);

	// Divisor has to be sent byte-wise, so split here into upper/lower bytes.
	u8int l = (u8int)(divisor & 0xFF);
	u8int h = (u8int)( (divisor>>8) & 0xFF );

	// Send the frequency divisor.
	outb(0x40, l);
	outb(0x40, h);



	disable_interrupts();

	/*
		CMOS_SECOND = 0x0
		CMOS_MINUTE = 0x2
		CMOS_HOUR = 0x4
		CMOS_WEEKDAY = 0x6
		CMOS_DAY = 0x7
		CMOS_MONTH = 0x8
		CMOS_YEAR = 0x9
	*/
	for (int i = 0; i < 9; i++)
	{
		outb(0x70, 0x80 + i); // go through CMOS time registers
		outb(0x71, 0); // set them to zero
	}
	enable_interrupts();
	

	disable_interrupts();
	outb(0x70, 0x8B); // select register B, and disable NMI
	char prev = inb(0x71); // read the current value of register B
	outb(0x70, 0x8B); // set the index again (a read will reset the index to register D)
	outb(0x71, prev | 0x40); // write the previous value ORed with 0x40. This turns on bit 6 of register B
	enable_interrupts();
	


	// outb(0x70, 0x0C);	// select register C
	// inb(0x71);

} 