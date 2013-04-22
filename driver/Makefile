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




run_test:
	./a.out
HOSTIP = 129.241.103.222

upload: default 
	#cp driver.ko driver_and_test/
	#cp a.out driver_and_test/
	#scp ./* root@$(HOSTIP):/game/driver

	#scp {driver.ko, a.out} root@$(HOSTIP):/dev

	scp ./*.* root@$(HOSTIP):/game/driver
	scp ./testProgram/* root@$(HOSTIP):/game/driver
	#scp ./test_driver.out root@$(HOSTIP):/dev
	#scp ./driver.ko andreul@login.stud.ntnu.no:/home/shomeb/a/andreul

	#scp ./driver.ko andreul@caracal.stud.ntnu.no:~/public_html
	#scp ./test_driver.out andreul@caracal.stud.ntnu.no:~/public_html



	

