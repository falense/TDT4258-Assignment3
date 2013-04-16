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

HOSTIP = 129.241.103.212

upload: default
	scp ./* root@$(HOSTIP):/game/driver
	scp ./driver.ko root@$(HOSTIP):/dev
