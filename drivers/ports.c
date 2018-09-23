#include "./ports.h"
/*// al is intermediary
unsigned char port_byte_in(unsigned short port){
    unsigned char result;
    __asm__("in %%dx, %%al" : "=a" (result) : "d" (port)); // % is an escape character also used to refer to registers. Thus, two are needed
    // "in"'s syntax is in reverse order with nasm 32bit assembly, and it reads the content of the address specified by dx
    return result;
}

void port_byte_out(unsigned short port, unsigned char data){
    __asm__("out %%al, %%dx" : : "a" (data), "d" (port)); // the middle section is empty since there's no need to set any variables in kernel
    // update the content of dx with al. dx should the the address to place the data contained in al
}

unsigned short port_word_in(unsigned short port){
    unsigned short result;
    __asm__("in %%dx, %%al" : "=a" (result) : "d" (port));
}

void port_word_out(unsigned short port, unsigned short data){
    __asm__("out %%al, %%dx" : : "a" (data), "d" (port));
}

*/



/**
 * Read a byte from the specified port
 */
unsigned char port_byte_in (unsigned short port) {
    unsigned char result;
    /* Inline assembler syntax
     * !! Notice how the source and destination registers are switched from NASM !!
     *
     * '"=a" (result)'; set '=' the C variable '(result)' to the value of register e'a'x
     * '"d" (port)': map the C variable '(port)' into e'd'x register
     *
     * Inputs and outputs are separated by colons
     */
    __asm__("in %%dx, %%al" : "=a" (result) : "d" (port));
    return result;
}

void port_byte_out (unsigned short port, unsigned char data) {
    /* Notice how here both registers are mapped to C variables and
     * nothing is returned, thus, no equals '=' in the asm syntax 
     * However we see a comma since there are two variables in the input area
     * and none in the 'return' area
     */
    __asm__("out %%al, %%dx" : : "a" (data), "d" (port));
}

unsigned short port_word_in (unsigned short port) {
    unsigned short result;
    __asm__("in %%dx, %%ax" : "=a" (result) : "d" (port));
    return result;
}

void port_word_out (unsigned short port, unsigned short data) {
    __asm__("out %%ax, %%dx" : : "a" (data), "d" (port));
}
