
all: main
%.o: %.c
	gcc -std=c99  -o $@ -c $< 
main: qdbmp.c bmp.o
	gcc -std=c99   -o main $^
clean:
	rm -f main *.o

run: all
	./main test.bmp test2.bmp