
HOSTIP = 129.241.103.209
#MAKE = avr32-linux-gcc
MAKE = gcc

all: main testbmp testboard

%.o: %.c
	$(MAKE) -std=c99  -o  $@ -c $< 
main: screen.o sound.o ledbuttons.o main.o 
	$(MAKE) -std=c99 -O3 -g -o main.prog $^

run: main
	./main 
	
show: run
	chmod 0777 testfile.dat
	cat testfile.dat
	
clean:
	rm -f *.prog *.o

upload: all
	scp ./* root@$(HOSTIP):/game/media

testboard: screen.o  sound.o  ledbuttons.o 
	$(MAKE) -std=c99 -O3 -g -o testboard.prog $^

testbmp: testbmp.o  bmp.o ./libs/qdbmp.o
	$(MAKE) -std=c99 -O3 -g -o testbmp.prog $^

testledbuttons:  testledbuttons.o  ledbuttons.o
	$(MAKE) -std=c99 -O3 -g -o testledbuttons.prog $^

testscreen:  testscreen.o  screen.o
	$(MAKE) -std=c99 -O3 -g -o testscreen.prog $^

testsound:  testsound.o  sound.o
	$(MAKE) -std=c99 -O3 -g -o testsound.prog $^



