gcc -ffreestanding -c basic.c -o basic.o
objdump -d basic.o
ld -o basic.bin -Ttext 0x0 --oformat binary basic.o


