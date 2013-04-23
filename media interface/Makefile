
HOSTIP = 129.241.103.209
MAKE = avr32-linux-gcc

all: main

%.o: %.c
	$(MAKE) -std=c99  -o $@ -c $< 


main: screen.o sound.o ledbuttons.o main.o 
	$(MAKE) -std=c99 -O3 -g -o main $^


run: main
	./main 
	
show: run
	chmod 0777 testfile.dat
	cat testfile.dat
	
clean:
	rm -f media *.o

upload: all
	scp ./* root@$(HOSTIP):/game/media
