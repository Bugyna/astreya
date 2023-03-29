#pragma once

// extern void (*__preinit_array_start []) (void) __attribute__((weak));
// extern void (*__preinit_array_end []) (void) __attribute__((weak));
// extern void (*__init_array_start []) (void) __attribute__((weak));
// extern void (*__init_array_end []) (void) __attribute__((weak));
// extern void (*__fini_array_start []) (void) __attribute__((weak));
// extern void (*__fini_array_end []) (void) __attribute__((weak));
// #define va_list __builtin_va_list


// int printf(const char* fmt, ...) 
// {
	// va_list list;
	// __builtin_va_start(list, fmt);
	// int a = __builtin_va_arg(list, int);

	// // for (char* c = fmt; *c != '\0'; c++)
	// // {
		
	// // }
	// __builtin_va_end(list);
	// return a;
// }