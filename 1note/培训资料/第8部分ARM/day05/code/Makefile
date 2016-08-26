cmd.bin:cmd
	arm-linux-objcopy -O binary cmd cmd.bin
cmd:start.o uart.o led.o nand.o
	arm-linux-gcc -nostartfiles -nostdlib -e start -Ttext 20004000 start.o led.o uart.o nand.o -o cmd
start.o:start.S
	arm-linux-gcc -nostdlib -c start.S
led.o:led.S
	arm-linux-gcc -nostdlib -c led.S
uart.o:uart.c
	arm-linux-gcc -nostdlib -c uart.c
nand.o:nand.c
	arm-linux-gcc -nostdlib -c nand.c

clean:
	rm -rf *.o cmd cmd.bin
