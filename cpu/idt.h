#ifndef IDT_H
#define IDT_H
#include "types.h"
#define KERNEL_CS 0x08 // the IDT table takes a segment and a sub address
typedef struct{
    u16 low_offset; // lower address of the handler function
    u16 sel; // kernel segment
    u8 always0; 
    u8 flags; // bit 0-3: bits 1110 = 32 bit interrupt gate(count from right to left)
            // bit 4: 0 for interrupt gates
            // bits 5-6: level of caller: 0 kernel, 3 user
            //bit 7: whether interrupt is present or not
    u16 high_offset; // higher address of the handler function
} __attribute__((packed)) idt_gate_t; // must have 256 gates stored in the table

typedef struct {
    u16 limit; // size
    u32 base; // base address, pointer to the array of gates below
} __attribute__((packed)) idt_register_t; // registers the table, read by assembly code 'lidt'

#define IDT_ENTRIES 256
idt_gate_t idt[IDT_ENTRIES];
idt_register_t idt_reg;
void set_idt_gate(int n, u32 handler);
void set_idt();


#endif