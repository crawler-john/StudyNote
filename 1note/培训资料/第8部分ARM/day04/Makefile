cmd.bin:cmd
	arm-linux-objcopy -O binary cmd cmd.bin
cmd:start.o uart.o led.o
	arm-linux-gcc -nostartfiles -nostdlib -e start -Ttext 20008000 start.o led.o uart.o -o cmd
start.o:start.S
	arm-linux-gcc -nostdlib -c start.S
led.o:led.S
	arm-linux-gcc -nostdlib -c led.S
uart.o:uart.c
	arm-linux-gcc -nostdlib -c uart.c

clean:
	rm -rf *.o cmd cmd.bin
