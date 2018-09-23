[org 0x7c00]
    mov bp, 0x8000 ; stack base pointer
    mov sp, bp ; stack pointer
    mov bx, 0x9000 ; where the data from the disk will begin
    mov dh, 2 ; the number of sectors to read

    call loadDisk
    
    mov dx, [0x9000] ; display the data on sector 1
    call print_hex
    call printString

    mov dx, [0x9000 + 512] ; display sector 2
    call print_hex

    jmp $ ; infinite loop

%include "16_printString.asm"
%include "16_boot_sect_print_hex.asm"
%include "16_bootDisk.asm"

times 510 - ($-$$) db 0
dw 0xaa55

times 256 dw 0xdada ; 256 * 2 = 512, sector 1
times 256 dw 0xface ; 256 * 2 = 512, sector 2

