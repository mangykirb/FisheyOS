#!/bin/bash
set -e
rm -f boot.bin kernel.bin kernel.o kernel_entry.o video.o os.bin
nasm -f bin bootloader/boot.asm -o boot.bin
gcc -m32 -ffreestanding -fno-pie -fno-pic -fno-stack-protector -nostdlib -c kernel/kernel.c -o kernel.o
nasm -f elf32 bootloader/kernel_entry.asm -o kernel_entry.o
ld -m elf_i386 -T linker.ld -o kernel.bin --oformat binary kernel_entry.o kernel.o 
cat boot.bin kernel.bin > os.bin
qemu-system-i386 -drive format=raw,file=os.bin
# tryna save up some space yk