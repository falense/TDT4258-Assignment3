
all: button_test led_test
button_test: button_test.c
	avr32-linux-gcc -o button_test button_test.c
led_test: led_test.c
	avr32-linux-gcc -o led_test led_test.c
HOSTIP = 129.241.103.222
upload: all
	scp ./* root@$(HOSTIP):/game/driver
