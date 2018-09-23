#include "../cpu/isr.h"
#include "../drivers/screen.h"
#include "kernel.h"
#include "../libc/string.h"

void main(){
    isr_install();
    irq_install();

    kprint("INTERRUPT SERVICE REQUESTS AND INTERRUPT REQUEST INSTALLED");

}

void user_input(char *input){
    if(strcmp(input, "END") == 0){
        kprint("STOPPING THE CPU\n");
        asm volatile("hlt"); // halt the cpu
    }
    kprint(input);
    kprint("\n> ");
}