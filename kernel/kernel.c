// #include "stdio.h"
#include "util.h"
#include "descriptor_tables.h"

void initialize(void)
{
	row_index = 0;
	column_index = 0;
	terminal_color = vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
	terminal_buffer = (u16*) 0xB8000;
	for (size_t y = 0; y < VGA_HEIGHT; y++) {
		for (size_t x = 0; x < VGA_WIDTH; x++) {
			const size_t index = y * VGA_WIDTH + x;
			terminal_buffer[index] = vga_entry(' ', terminal_color);
		}
	}
}
 
void kernel_main(struct mboot* mboot_ptr) 
{
	init_descriptor_tables();
	initialize();
	setcolor(13);

	// writestring("Hello, kernel World!\n");
	// clear();
	// char s[300];
	printf("dddick %d penis\n", 200);
	// int i = 20;
	// itoa(i, s);
	// writestring(s);
	writestring("Hello, kernel World!\n");
	putchar('\n');
	putchar('>');
	asm volatile ("int $0x3");
	putchar('\n');

	asm volatile("sti");
	// init_timer(50); // Initialise timer to 50Hz 
	init_keyboard();
	asm volatile("sti");
	// asm volatile ("int $0x3");
	// asm volatile ("int $0x4"); 
}




