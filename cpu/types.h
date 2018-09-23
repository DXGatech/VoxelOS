#ifndef TYPES_H
#define TYPES_H

typedef unsigned int u32;
typedef int s32;
typedef unsigned short u16;
typedef short s16;
typedef unsigned char u8;
typedef char s8;

#define low_16(address) (u16)((address) & 0xFFFF) // cut the high address(left side) fom this section and prevents leakage with 0xFFFF
#define high_16(address) (u16)(((address) >> 16) & 0xFFFF) // high and low combine to form the ultimate address

#endif