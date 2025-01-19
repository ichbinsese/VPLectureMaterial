all: bin

bin: firmware
	arm-none-eabi-objcopy -O binary firmware.elf firmware.bin
	dd if=/dev/zero of=flash.bin bs=4096 count=4096
	dd if=firmware.bin of=flash.bin bs=4096 conv=notrunc

firmware: main.o startup.o
	arm-none-eabi-ld -nostdlib -o firmware.elf -Map firmware.map -T firmware.ld main.o startup.o

startup.o: startup.s
	arm-none-eabi-as -mcpu=cortex-m4 -mthumb -g -o startup.o startup.s

main.o: main.c
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -c -g3 -O0 -o main.o main.c

clean:
	rm -f firmware.elf *.bin *.o *.map