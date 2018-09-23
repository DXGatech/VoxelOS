/usr/bin/nasm -f bin ./32_main.asm -o 32_main.bin

qemu-system-x86_64 ./32_main.bin

