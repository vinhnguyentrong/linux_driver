ROOT_DIR = /root/linux_driver/
EXTRA_CFLAGS += -Wall
EXTRA_CFLAGS += -I$(ROOT_DIR)/kernel/include

obj-m += virtual_driver.o

KDIR=/lib/modules/`uname -r`/build
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