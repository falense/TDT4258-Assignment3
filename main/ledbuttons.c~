
int ledButtonsDeviceID = -1;

#include "sound.h"
void initLedButtons(){
///dev/ttyPA1
	ledButtonsDeviceID = open("/dev/driver",O_RDWR );

	if(ledButtonsDeviceID < 0)
	{
		printf("Didnt manage to STK1000 device driver.");
		exit(0);
	}
}
void closeLedButtons(){
	close(ledButtonsDeviceID);
}
void setLeds(char leds){
	ssize_t written = write(ledButtonsDeviceID, &leds,1);
	if(written >= 0)
		;  // handle successful write (which might be a partial write!)
	else if(errno == EWOULDBLOCK)
		printf("Error writing");
	else printf("Error writing");
}
char readButtons(){
char buttons;
ssize_t bytesread = read(ledButtonsDeviceID, &buttons,1);
	if(bytesread >= 0)
		return buttons;
	else if(errno == EWOULDBLOCK)
		printf("Error writing");
	else printf("Error writing");
	return 0;
}
