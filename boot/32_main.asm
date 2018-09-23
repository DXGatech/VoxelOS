[org 0x7c00]
KERNEL_OFFSET equ 0x1000

    mov [BOOT_DRIVE], dl
    mov bp, 0x9000
    mov sp, bp
    
    mov bx, REAL_MSG
    call printString
    
    call load_kernel
    call pSwitch
    jmp $
    
    %include "32_printString.asm"
    %include "GDT.asm"
    %include "16_printString.asm"
    %include "32_switch.asm"
    %include "16_bootDisk.asm"
    %include "16_boot_sect_print_hex.asm"
    
[bits 16]
load_kernel:
    mov bx, MSG_LOAD_KERNEL
    call printString
    call print_hex
    mov bx, KERNEL_OFFSET
    mov dh, 2
    mov dl, [BOOT_DRIVE]
    call loadDisk
    ret
    
    
[bits 32]
PM_BEGIN:
    mov ebx, PROT_MSG
    call t_printString
    call KERNEL_OFFSET
    jmp $
    
    
BOOT_DRIVE db 0
REAL_MSG db "Entering 16bit environment", 0
PROT_MSG db "32bit environment loaded", 0
MSG_LOAD_KERNEL db "Loading kernel into memory", 0

times 510-($-$$) db 0
dw 0xaa55

    
    
    
    
    
    
    
    