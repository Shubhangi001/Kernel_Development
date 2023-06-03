ifneq ($(KERNELRELEASE),)
	obj-m := hello.o
else
	KERNELDIR ?= ~/linux
	PWD := $(shell pwd)
default:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules
endif
