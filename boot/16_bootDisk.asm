loadDisk:
    pusha ; in case the function automatically resets the registers, we save their values on the stack
    push dx ; savedx, so that it can be used to store parameters
    
    mov ah, 0x02 ; the second option for interrupt 13
    mov al, dh ; al contains the amount of sectors to read
    mov cl, 0x02 ; read the second sector
    mov ch, 0x00 ; read cylinder 0
    mov dh, 0x00 ; read the front side
    
    int 0x13 ; the main program stores bx, the starting address for the loaded data
    jc ERROR_DISK ; jump of BOIS encounters an error
    
    pop dx
    ; the number of loaded sectors is stored in al, compare it with the number we wanted to read
    cmp al, dh ;
    jne ERROR_SECTOR ; different sector amount, error
    popa ; restore the values of all registers
    ret
    
ERROR_DISK:
    mov bx, DISK_ERR
    call printString
    mov dh, ah ; drive number and error code
    call print_hex
    jmp err_loop
    
ERROR_SECTOR:
    mov bx, SEC_ERR
    call printString
    
err_loop:
    jmp $
    
DISK_ERR: db "error reading destination disk"
SEC_ERR: db "sector reading corruption"
    
    
    
    
    
    
    
    
    
    
    