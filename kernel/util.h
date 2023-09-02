#pragma once

#include "stdlib.h"
#include "stddef.h"



#define BYTE unsigned char

#define FB_COMMAND_PORT         0x3D4
#define FB_DATA_PORT            0x3D5

#define FB_HIGH_BYTE_COMMAND    14
#define FB_LOW_BYTE_COMMAND     15

// Copy len bytes from src to dest.
void outb(u16int port, u8int value);
u8int inb(u16int port);
u16int inw(u16int port);
void memcpy(void* dest, const u8int *src, u32int len);
void memset(void *dest, u8int val, u32int len);
int strcmp(char *str1, char *str2);
char *strcpy(char *dest, const char *src);
char *strcat(char *dest, const char *src);
void mem_copy(char* source, char* dest, int bytes);
size_t strlen(const char* str);
int itoa(int value, char *sp);
int ascii_to_int(char n[]);
#define KERN_ERR(x, ...) printf(x, __VA_ARGS__)

// Hardware text mode color constants.
enum vga_color {
	VGA_COLOR_BLACK = 0,
	VGA_COLOR_BLUE = 1,
	VGA_COLOR_GREEN = 2,
	VGA_COLOR_CYAN = 3,
	VGA_COLOR_RED = 4,
	VGA_COLOR_MAGENTA = 5,
	VGA_COLOR_BROWN = 6,
	VGA_COLOR_LIGHT_GREY = 7,
	VGA_COLOR_DARK_GREY = 8,
	VGA_COLOR_LIGHT_BLUE = 9,
	VGA_COLOR_LIGHT_GREEN = 10,
	VGA_COLOR_LIGHT_CYAN = 11,
	VGA_COLOR_LIGHT_RED = 12,
	VGA_COLOR_LIGHT_MAGENTA = 13,
	VGA_COLOR_LIGHT_BROWN = 14,
	VGA_COLOR_WHITE = 15,
};
 
u8 vga_entry_color(enum vga_color fg, enum vga_color bg);
u16 vga_entry(unsigned char uc, u8 color);
 
static const size_t VGA_WIDTH = 80;
static const size_t VGA_HEIGHT = 25;

i16 row_index;
i16 column_index;
u8 terminal_color;
u16* terminal_buffer;
 

void setcolor(u8 color);
void putentryat(char c, u8 color, size_t x, size_t y);
void set_cursor(u16 pos);
void move_cursor(u16 x, u16 y);
void putchar(char c);
void write(const char* data, size_t size);
void writestring(const char* data);
void clear();
void clear_line(u16 y);
void clear_from(u16 x, u16 y);
#define va_list __builtin_va_list
void printf(const char* fmt, ...);
