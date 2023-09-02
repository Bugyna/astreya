
#ifndef UTIL_H
#define UTIL_H
#include "util.h"
#include "stdlib.h"
#include "stddef.h"


void outb(u16int port, u8int value)
{
	asm volatile ("outb %1, %0" : : "dN" (port), "a" (value));
}

u8int inb(u16int port)
{
   u8int ret;
   asm volatile("inb %1, %0" : "=a" (ret) : "dN" (port));
   return ret;
}

u16int inw(u16int port)
{
   u16int ret;
   asm volatile ("inw %1, %0" : "=a" (ret) : "dN" (port));
   return ret;
}


void disable_interrupts()
{
	asm volatile ("cli");
}

void enable_interrupts()
{
	asm volatile ("sti");
}

// Copy len bytes from src to dest.
void memcpy(void* dest, const u8int *src, u32int len)
{
	const u8int *sp = (const u8int *)src;
	u8int *dp = (u8int *)dest;
	for(; len != 0; len--) *dp++ = *sp++;
}

// Write len copies of val into dest.
void memset(void *dest, u8int val, u32int len)
{
	u8int *temp = (u8int *)dest;
	for ( ; len != 0; len--) *temp++ = val;
}

// Compare two strings. Should return -1 if 
// str1 < str2, 0 if they are equal or 1 otherwise.
int strcmp(char *str1, char *str2)
{
	  int i = 0;
	  int failed = 0;
	  while(str1[i] != '\0' && str2[i] != '\0')
	  {
		  if(str1[i] != str2[i])
		  {
			  failed = 1;
			  break;
		  }
		  i++;
	  }
	  // why did the loop exit?
	  if( (str1[i] == '\0' && str2[i] != '\0') || (str1[i] != '\0' && str2[i] == '\0') )
		  failed = 1;
  
	  return failed;
}

// Copy the NULL-terminated string src into dest, and
// return dest.
char *strcpy(char *dest, const char *src)
{
	do
	{
	  *dest++ = *src++;
	}
	while (*src != 0);
}

// Concatenate the NULL-terminated string src onto
// the end of dest, and return dest.
char *strcat(char *dest, const char *src)
{
	while (*dest != 0)
	{
		*dest = *dest++;
	}

	do
	{
		*dest++ = *src++;
	}
	while (*src != 0);
	return dest;
}

void mem_copy(char* source, char* dest, int bytes)
{
	for (int i = 0; i < bytes; i++) {
		dest[i] = source[i];
	}
}

size_t strlen(const char* str) 
{
	size_t len = 0;
	while (str[len])
		len++;
	return len;
}

int itoa(int value, char *sp)
{
	char tmp[16];// be careful with the length of the buffer
	char *tp = tmp;
	int i;
	unsigned v;
	

	int sign = (value < 0);	
	if (sign)
		v = -value;
	else
		v = (unsigned)value;

	while (v || tp == tmp)
	{
		i = v % 10;
		v /= 10;
		if (i < 10)
		  *tp++ = i+'0';
		else
		  *tp++ = i + 'a' - 10;
	}

	int len = tp - tmp;

	if (sign) 
	{
		*sp++ = '-';
		len++;
	}

	while (tp > tmp)
		*sp++ = *--tp;

	*sp++ = '\0';

	return len;
}

int utoa(unsigned int value, char *sp)
{
	char tmp[16];// be careful with the length of the buffer
	char *tp = tmp;
	unsigned int i;
	unsigned v;
	v = value;

	while (v || tp == tmp)
	{
		i = v % 10;
		v /= 10;
		if (i < 10)
		  *tp++ = i+'0';
		else
		  *tp++ = i + 'a' - 10;
	}

	int len = tp - tmp;

	while (tp > tmp)
		*sp++ = *--tp;

	*sp++ = '\0';

	return len;
}

int ascii_to_int(char n[])
{
	int ret = 0;
	size_t i = 0;
	if (n[0] == '-') { i = 1; }
	
	for (size_t i = 0; i < strlen(n); i++) {
		ret = ret * 10 + n[i] - '0';
	}
	return ret;
}


 
u8 vga_entry_color(enum vga_color fg, enum vga_color bg) 
{
	return fg | bg << 4;
}
 
u16 vga_entry(unsigned char uc, u8 color) 
{
	return (u16) uc | (u16) color << 8;
}
 
void setcolor(u8 color) 
{
	terminal_color = color;
}
 
void putentryat(char c, u8 color, size_t x, size_t y) 
{
	const size_t index = y * VGA_WIDTH + x;
	terminal_buffer[index] = vga_entry(c, color);
	// move_cursor(index+1);
}

void set_cursor(u16 pos)
{
	outb (FB_COMMAND_PORT, FB_HIGH_BYTE_COMMAND);
	outb (FB_DATA_PORT,	((pos >> 8) & 0x00FF));
	outb (FB_COMMAND_PORT, FB_LOW_BYTE_COMMAND);
	outb (FB_DATA_PORT,	pos & 0x00FF);
}

void move_cursor(u16 x, u16 y)
{
	set_cursor(y * VGA_WIDTH + x);
	column_index = x;
	row_index = y;
}
 
void putchar(char c) 
{

	switch (c)
	{
		case '\n':
			column_index = 0;
			if (row_index++ > 25)
				clear();
			move_cursor(column_index, row_index);
			break;

		case '\b':
			if (column_index-1 >= 0) {
				// printf("column_index: %d", column_index);
				column_index -= 1;
				putentryat(' ', terminal_color, column_index, row_index);
				move_cursor(column_index, row_index);
			}
				// row_index -= 1;
			break;

		default:
			putentryat(c, terminal_color, column_index++, row_index);
			if (column_index == VGA_WIDTH) {
				column_index = 0;
				if (row_index == VGA_HEIGHT)
					row_index = 0;
			}
			move_cursor(column_index, row_index);
	}
}
 
void write(const char* data, size_t size) 
{
	for (size_t i = 0; i < size; i++)
		putchar(data[i]);
}
 
void writestring(const char* data) 
{
	write(data, strlen(data));
}

void clear()
{
	for (int i = 0; i < 80*25; i++)
	{
		terminal_buffer[i] = ' ';
	}
	row_index = 0;
	column_index = 0;
}

void clear_line(u16 y)
{
	for (int i = y*25; i < 80*(y+1); i++)
	{
		terminal_buffer[i] = ' ';
	}
	column_index = 0;
	row_index = y;
}


void clear_from(u16 x, u16 y)
{
	for (int i = y*25+x; i < 80*(y+1); i++)
	{
		terminal_buffer[i] = ' ';
	}
	column_index = x;
	row_index = y;
}


void printf(const char* fmt, ...) 
{
	va_list list;
	__builtin_va_start(list, fmt);
	bool next = false;
	char tmp[100];

	for (const char* c = fmt; *c != '\0'; c++)
	{
		if (*c == '\0') break;
		if (*c == '%' && !next) next = true;
		else if (next) {
			switch (*c)
			{
				case 'd':
					itoa(__builtin_va_arg(list, int), tmp);
					writestring(tmp);
				break;

				case 'u':
					utoa(__builtin_va_arg(list, unsigned int), tmp);
					writestring(tmp);
				break;

				case 'x':
					utoa(__builtin_va_arg(list, unsigned int), tmp);
					writestring(tmp);
				break;
				

				case 'c':
					putchar((char)__builtin_va_arg(list, int));
			}
			next = false;
		}
		else {
			putchar(*c);
		}
	}
	__builtin_va_end(list);
}


#endif

