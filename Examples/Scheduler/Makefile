all: bin

bin: firmware
	arm-none-eabi-objcopy -O binary firmware.elf firmware.bin
	dd if=/dev/zero of=flash.bin bs=1024 count=512
	dd if=firmware.bin of=flash.bin bs=1024 conv=notrunc

firmware: main.o Scheduler.o startup.o
	arm-none-eabi-ld -nostdlib -o firmware.elf -Map firmware.map -T firmware.ld main.o Scheduler.o startup.o

startup.o: startup.s
	arm-none-eabi-as -mcpu=cortex-m4 -g -o startup.o startup.s

main.o: main.c
	arm-none-eabi-gcc -mcpu=cortex-m4 -c -g3 -O0 -o main.o main.c
	
Scheduler.o: Scheduler.c
	arm-none-eabi-gcc -mcpu=cortex-m4 -c -g3 -O0 -o Scheduler.o Scheduler.c

clean:
	rm -f firmware.elf *.bin *.o *.map