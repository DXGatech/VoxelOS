startGDT:
    dd 0x0
    dd 0x0 ; 8 bit null descriptor double word

seg_code:
    dw 0xffff ; limit of the segment
    dw 0x0 ; base dw 16 bits
    db 0x0 ; base db 8 bits, so that total value is 24 bits
    db 10011010b ; (1 present) (00 privilege) (1 code descriptor) (1 code) (0 conforming) (1 readable) (0 accessed)  -> 10011010b
    db 11001111b ; (1 granularity) (32bit default 1) (64bit seg 0) (AVL 0) + segment size 1111 -> 11001111b 
    db 0x0 ; 24 - 31 bits, 32 en total

seg_data:
    dw 0xffff
    dw 0x0
    db 0x0
    db 10010010b ; (1 present) (00 privilege) (1 code descriptor) (0 code) (0 downward expansion) (1 writable) (0 accessed) -> 00101111b
    db 11001111b ; same with the code segment's secondary flags
    db 0x0

end:  ; for GDT descriptor calculation

descriptor:
    dw end - startGDT - 1 ; always one less of the true size
    dd startGDT ; start address
    
CODE_ADDR equ seg_code - startGDT ; we'll need the segment addresses
DATA_ADDR equ seg_data - startGDT




