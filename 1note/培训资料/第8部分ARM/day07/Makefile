CC=arm-linux-gcc
OC=arm-linux-objcopy
CFLAG=-nostdlib -c
OFLAG=-nostartfiles -nostdlib -e main -T cmd.lds
BFLAG=-O binary
OBJS=start.o led.o uart.o nand.o irq.o dram.o vector.o stack.o setmmu_table.o
ELF=cmd
BIN=cmd.bin

$(BIN):$(ELF)
	$(OC) $(BFLAG) $< $@
$(ELF):$(OBJS)
	$(CC) $(OFLAG) $^ -o $@
%.o:%.S
	$(CC) $(CFLAG) $<
%.o:%.s
	$(CC) $(CFLAG) $<
%.o:%.c
	$(CC) $(CFLAG) $<

clean:
	rm -rf $(OBJS) $(ELF) $(BIN)



