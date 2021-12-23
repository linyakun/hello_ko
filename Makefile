
obj-m := hello.o

KERNELDIR ?= 

PWD := $(shell pwd)

all:
	#$(MAKE) -C $(KERNELDIR) ARCH=arm64 CROSS_COMPILE=aarch64-linux-gnu-  M=$(PWD) modules 
	$(MAKE) -C $(KERNELDIR)  M=$(PWD) modules

clean:
	rm -rf hello.mod.* 
	rm -rf modules.order
	rm -rf Module.symvers
	rm -rf hello.ko
	rm -rf hello.o
	rm -rf *.mod
	rm -rf .hello*
