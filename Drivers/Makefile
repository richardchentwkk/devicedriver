ARCH=x86

obj-m := chardev.o

ifeq ($(KERNELDIR),)
KERNELDIR=/lib/modules/2.6.32-57-generic/build
endif

all:
	make -C $(KERNELDIR) M=$(PWD) modules

clean:
	make -C $(KERNELDIR) M=$(PWD) clean

