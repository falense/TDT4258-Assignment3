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

test_driver.o: test_driver.c
	gcc -c -o test_driver.o test_driver.c

test_driver: test_driver.o
	ld test_driver.o −o test_driver


run_test:
	./a.out

HOSTIP = 129.241.103.242

upload: default test_driver
	#cp driver.ko driver_and_test/
	#cp a.out driver_and_test/
	#scp ./* root@$(HOSTIP):/game/driver

	#scp {driver.ko, a.out} root@$(HOSTIP):/dev

	scp ./driver.ko root@$(HOSTIP):/dev
	scp ./test_driver.out root@$(HOSTIP):/dev
	#scp ./driver.ko andreul@login.stud.ntnu.no:/home/shomeb/a/andreul

	

