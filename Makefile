ifneq ($(KERNELRELEASE),)
	obj-m := first_kernel_module.o
else
	KERNELDIR ?= ~/linux
	PWD := $(shell pwd)
default:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules
endif
