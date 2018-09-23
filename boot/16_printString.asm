printString:
    pusha ; prevents unwanted register mod
    
    
start: ; loop through the strings
    mov al, [bx] ; strings are stored in EBX
    cmp al, 0 ; if no string
    je done
    
    mov ah, 0x0e ; interrupt 13's 14th function
    int 0x10 ; ; output
    add bx, 1 ; to the next character
    jmp start
    
done:
    popa
    ret