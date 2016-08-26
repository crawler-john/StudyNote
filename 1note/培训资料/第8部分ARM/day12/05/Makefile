KERNEL ?= /home/student/dyhy1502/linux-2.6.35.7


obj-m	+= led_drv.o

default:
	$(MAKE) -C $(KERNEL) M=$(PWD) modules
install:
	$(MAKE) -C $(KERNEL) M=$(PWD) INSTALL_MOD_PATH=/home/student/workdir/rootfs modules_install
clean:
	rm -rf *.o *.ko* *.mod* *.sy* *.ord* .*cmd .*versions


