
all: main
%.o: %.c
	gcc -std=c99  -o $@ -c $< 
main: wav.o
	gcc -std=c99   -o main $^
clean:
	rm -f main *.o

run: all
	./main