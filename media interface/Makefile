all: media

media: media.c
	gcc -std=c99 -O3 -g -o media media.c -lm

run: media
	./media
	
show: run
	chmod 0777 testfile.dat
	cat testfile.dat
	
clean:
	rm -f media 