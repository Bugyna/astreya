#include "isr.h"
// This gets called from our ASM interrupt handler stub.

isr_t interrupt_handlers[256];

void register_interrupt_handler(u8int n, isr_t handler)
{
  interrupt_handlers[n] = handler;
}

void isr_handler(registers_t regs)
{
	printf("recieved interrupt: %d", regs.int_no);
	// printf("%d", regs.int_no);
	// monitor_put('\n');
}

void irq_handler(registers_t regs)
{
	// Send an EOI (end of interrupt) signal to the PICs.
	// If this interrupt involved the slave.
	if (regs.int_no >= 40)
	{
		// Send reset signal to slave.
		outb(0xA0, 0x20);
	}
	// Send reset signal to master. (As well as slave, if necessary).
	outb(0x20, 0x20);

	if (interrupt_handlers[regs.int_no] != 0)
	{
		isr_t handler = interrupt_handlers[regs.int_no];
		handler(regs);
	}
}



u16 read_irq_reg(u8 port)
{
	outb(0x20, port);
	outb(0xA0, port);
	return (inb(0xA0) << 8) | inb(0x20);
}

u16 pic_get_irr(void)
{
    return read_irq_reg(0x0A);
}
 
/* Returns the combined value of the cascaded PICs in-service register */
u16 pic_get_isr(void)
{
    return read_irq_reg(0x0B);
}

