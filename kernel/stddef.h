


// #define size_t unsigned int
// #define u8 unsigned char
// #define u16 unsigned short
// #define u32 unsigned int
// #define u64 unsigned long int

// #define i8 signed char
// #define i16 short
// #define i32 int
// #define i64 long long int
#ifndef STDDEF_H
#define STDDEF_H

typedef unsigned int size_t;
typedef unsigned int   u32;
typedef          int   i32;
typedef unsigned short u16;
typedef          short i16;
typedef unsigned char  u8;
typedef          char  i8;

// Some nice typedefs, to standardise sizes across platforms.
// These typedefs are written for 32-bit X86.
typedef unsigned int   u32int;
typedef          int   s32int;
typedef unsigned short u16int;
typedef          short s16int;
typedef unsigned char  u8int;
typedef          char  s8int;

#endif