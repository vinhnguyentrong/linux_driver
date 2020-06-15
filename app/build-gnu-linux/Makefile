CC = g++
ROOT_DIR = /root/linux_driver/
INCLUDE += -I(ROOT_DIR)/app/include
SRC_PATH = $(ROOT_DIR)/app/src

SRC += $(SRC_PATH)/main.cpp
ELF_TARGET = main.elf
VPATH = $(ROOT_DIR)/app/src

all: main.c
	CC $(INCLUDE) $(SRC) -o $(ELF_TARGET)

clean:
	rm $(ELF_TARGET)