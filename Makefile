ifneq ($(KERNELRELEASE),)
# kbuild part of makefile
obj-m  := mykb.o

else
# normal makefile
	KDIR ?= /lib/modules/`uname -r`/build

default:
	$(MAKE) -C $(KDIR) M=$$PWD

modules_install: default
	$(MAKE) -C $(KDIR) M=$$PWD modules_install 

clean:
	$(MAKE) -C $(KDIR) M=$$PWD clean

endif