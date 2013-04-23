
HOSTIP = 129.241.103.209
#MAKE = avr32-linux-gcc
MAKE = gcc

all: main testall

%.o: %.c
	$(MAKE) -std=c99  -g -O3 -o  $@ -c $< 
main: screen.o sound.o ledbuttons.o main.o 
	$(MAKE) -std=c99 -O3 -g -o main.prog $^

run: main
	./main 
	
	
clean:
	rm -f *.prog *.o

upload: all
	scp ./*.prog root@$(HOSTIP):/game/

testboard: testboard.o screen.o  sound.o  ledbuttons.o wav.o bmp.o ./libs/qdbmp.o
	$(MAKE) -std=c99 -O3 -g -o testboard.prog $^

testbmp: testbmp.o  bmp.o ./libs/qdbmp.o
	$(MAKE) -std=c99 -O3 -g -o testbmp.prog $^

testledbuttons:  testledbuttons.o  ledbuttons.o
	$(MAKE) -std=c99 -O3 -g -o testledbuttons.prog $^

testscreen:  testscreen.o  screen.o
	$(MAKE) -std=c99 -O3 -g -o testscreen.prog $^

testsound:  testsound.o  sound.o wav.o
	$(MAKE) -std=c99 -O3 -g -o testsound.prog $^


testwav:  testwav.o  wav.o
	$(MAKE) -std=c99 -O3 -g -o testwav.prog $^

runtestwav: testwav
	./testwav.prog

runtestbmp: testbmp
	./testbmp.prog
testall: testboard testbmp testledbuttons testscreen testsound testwav


