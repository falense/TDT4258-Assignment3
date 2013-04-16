
HOSTIP = 129.241.102.246

all: main

%.o: %.c
	gcc -std=c99  -o $@ -c $< -lm


main: screen.o sound.o main.o 
	gcc -std=c99 -O3 -g -o main $^


run: main
	./main 
	
show: run
	chmod 0777 testfile.dat
	cat testfile.dat
	
clean:
	rm -f media *.o

upload: all
	scp ./* root@$(HOSTIP):/game/media
