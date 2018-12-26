# By 71 2018 12-26
#

obj-m += vwk.o
vwk-objs = vnetwk.o trans.o

KERNEL_DIR=/lib/modules/$(shell uname -r)/build
PWD=$(shell pwd)

all:
    make -C $(KERNEL_DIR) SUBDIRS=$(PWD) modules
clean:
    -rm *.mod.c *.ko *.o