
#include "sound.h"

void initSound(){
///dev/ttyPA1
	soundDeviceID = open("/dev/dsp",O_RDWR | O_NONBLOCK);

	if(soundDeviceID < 0)
	{
		printf("Didnt manage to open sound device.");
		exit(0);
	}
		;  // handle error
}
void closeSound(){
	close(soundDeviceID);

}
void writeSoundValue(unsigned int value){
	char data = value%256;
	ssize_t written = write(soundDeviceID, &data,1);
	if(written >= 0)
		;  // handle successful write (which might be a partial write!)
	else if(errno == EWOULDBLOCK)
		printf("Error writing");
	else printf("Error writing");
}

