
all: main
%.o: %.c
	gcc -std=c99  -o $@ -c $< 
clean:
	rm -f *.o test2.bmp bmptest

run: all
	./main test.bmp test2.bmp

testbmp: testbmp.o qdbmp.o
	gcc -std=c99   -o bmptest $^
runbmptest: testbmp
	./bmptest test.bmp test2.bmp

testall: runbmptest

