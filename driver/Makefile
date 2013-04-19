###############################################################################
#
# Linux kjernemodul Makefile
#
###############################################################################

# navn på kjernemodul (navnet på C-fila men uten ".c")
MODULE = driver

ifneq ($(KERNELRELEASE),)
obj-m := ${MODULE}.o

else

# sti til linux-kildekoden
KERNELDIR := ../linux/

default:
	$(MAKE) -C $(KERNELDIR) M=$$PWD modules

endif

.PHONY : clean
clean:
	rm -rf *.o *.ko .*.cmd *.mod.* .tmp*  Module.symvers modules.order Module.symvers modules.order

test:
	gcc -Wall -m32 test_driver.c
run_test:
	./a.out

HOSTIP = 129.241.103.212

upload: default test
	scp ./* root@$(HOSTIP):/game/driver
	scp ./driver.ko root@$(HOSTIP):/dev
