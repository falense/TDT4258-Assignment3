#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>

int main(int argc, char *argv[]){
	//char *path = argv[0];
	int soundDeviceID = open("/dev/driver",O_RDWR );

	if(soundDeviceID < 0)
	{
		printf("Didnt manage to open sound device.");
		exit(0);
	}
		;  // handle error

char byte;
read(soundDeviceID, &byte,1);
printf("Read byte %d\n",byte);

	int i;
	int a,b;

	for (i = 0; i < 256; i++){
for(a=0;a<2502;a++)
   for(b=0;b<2550;b++){
 int test = a+b;
}
	    	char byte = (char)(i%256);
	    	printf("Byte value is 0x%x\n",byte);
		ssize_t written = write(soundDeviceID, &byte,1);
	  	if(written <= 0){
			printf("Writing to driver failed (%d).\n",written);
		}	
	  
	  }
  	close(soundDeviceID);
	return 0;
}


