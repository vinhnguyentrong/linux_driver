EXTRA_CFLAGS = -Wall
obj-m += virtual_driver.o													   \
		 vird_func.o

KDIR=/lib/modules/`uname -r`/build
BUILD_DIR ?= $(PWD)/build-gnu-linux
SRC_DIR = /root/linux_driver/kernel/src
# BUILD_DIR_MAKEFILE ?= $(PWD)/build-gnu-linux/Makefile
# -M=$(PWD) Muc chua Makefile
default:
	make -C $(KDIR) M=$(PWD) src=$(SRC_DIR) modules
clean:
	make -C $(KDIR) M=$(PWD) src=$(SRC_DIR) clean
install:
	make -C $(KDIR) M=$(PWD) src=$(SRC_DIR) modules
	insmod virtual_driver.ko
uninstall:
	make -C $(KDIR) M=$(PWD) src=$(SRC_DIR) clean
	rmmod virtual_driver