[bits 16]
pSwitch:
    cli
    lgdt [descriptor]
    mov eax, cr0
    or eax, 0x1 ; set the first bit of cr0as 1 to activate 32bit mode
    mov cr0, eax
    jmp CODE_ADDR:init
    
[bits 32]
init:
    ; make sure that all segment pointers are ready for protected mode
    mov ax, DATA_ADDR
    mov ds, ax
    mov ss, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    
    mov ebp, 0x90000 ; top of the stack
    mov esp, ebp
    
    call PM_BEGIN
    
    
    
    
    