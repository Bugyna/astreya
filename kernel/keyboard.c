#include "keyboard.h"
#include "isr.h"

static unsigned char ascii_map[128] =
{
    0,  27, '1', '2', '3', '4', '5', '6', '7', '8',	/* 9 */
  '9', '0', '-', '=', '\b',	/* Backspace */
  '\t',			/* Tab */
  'q', 'w', 'e', 'r',	/* 19 */
  't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',	/* Enter key */
    0,			/* 29   - Control */
  'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';',	/* 39 */
 '\'', '`',   0,		/* Left shift */
 '\\', 'z', 'x', 'c', 'v', 'b', 'n',			/* 49 */
  'm', ',', '.', '/',   0,				/* Right shift */
  '*',
    0,	/* Alt */
  ' ',	/* Space bar */
    0,	/* Caps lock */
    0,	/* 59 - F1 key ... > */
    0,   0,   0,   0,   0,   0,   0,   0,
    0,	/* < ... F10 */
    0,	/* 69 - Num lock*/
    0,	/* Scroll Lock */
    0,	/* Home key */
    0,	/* Up Arrow */
    0,	/* Page Up */
  '-',
    0,	/* Left Arrow */
    0,
    0,	/* Right Arrow */
  '+',
    0,	/* 79 - End key*/
    0,	/* Down Arrow */
    0,	/* Page Down */
    0,	/* Insert Key */
    0,	/* Delete Key */
    0,   0,   0,
    0,	/* F11 Key */
    0,	/* F12 Key */
    0,	/* All other keys are undefined */
};

bool SHIFT_MOD = 0;
bool CTRL_MOD = 0;



static void keyboard_callback(registers_t regs)
{
	// printf("tick: %d %d\n", (u8)inb(0x60), inb(KEYBOARD_STATUS_PORT));

	int status = inb(KEYBOARD_STATUS_PORT);
	char keycode = inb(KEYBOARD_DATA_PORT);
	// printf("t: %d %d %d %d\n", status, status & 0x01, keycode, keycode & 0x0F);
	// printf("keycode: %d", keycode);
	outb(0x20, 0x20);

	if (keycode == 42 || keycode == -86) SHIFT_MOD = !SHIFT_MOD;
	
	else if (keycode > -1)
	{
		if (SHIFT_MOD) {
			char c = ascii_map[keycode];
			putchar(c - 32);
		}
		else
			putchar(ascii_map[keycode]);
	}
}

void init_keyboard()
{
	// outb(0x20, 0x11);
	// outb(0x21 , 0xFD);
   register_interrupt_handler(IRQ1, &keyboard_callback);
   // outb(0x43, 0x36);
} 
