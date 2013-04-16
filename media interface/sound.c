
int soundDeviceID = -1;

#include "sound.h"
void initSound(){
///dev/ttyPA1
	soundDeviceID = open("/dev/dsp",O_WRONLY );

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
void writeSoundValue(char *buffer, unsigned int length){
	ssize_t written = write(soundDeviceID, buffer,length);
	if(written >= 0)
		;  // handle successful write (which might be a partial write!)
	else if(errno == EWOULDBLOCK)
		printf("Error writing");
	else printf("Error writing");
}

