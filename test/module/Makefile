ifeq ($(module),)
obj-m := tasklist.o
module-objs := tasklist.o
else
obj-m := $(module).o
module-objs := $(module).o
endif

KERNEL_DIR := /lib/modules/`uname -r`/build
PWD := $(shell pwd)

default:
	make -C $(KERNEL_DIR) M=$(PWD) modules

clean:
	rm -f *.o *.cmd *.ko *.mod.c *.tmp_versions module
