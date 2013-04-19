//http://en.wikipedia.org/wiki/BMP_file_format

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <linux/soundcard.h>


#include "sound.h"
struct Sound{
	int width;
	int height;
	char *pixels;
	unsigned int fileSize;
	unsigned int pixelArrayOffset;
};
typedef struct Sound Sound;

Sound* loadSound(char * filename){

	soundFileID = open(filename,O_RDONLY);

	if(soundFileID < 0)
	{
		printf("Didnt manage to open screen block device.");
		return NULL;
	}
	Sound * image = (Sound*)malloc(sizeof(Sound));
	
	lseek(bitmapFileID, 10, SEEK_SET);
	ssize_t bytesread = write(soundFileID, (void*)image.pixelArrayOffset,4);
	printf("%d",image.fileSize);
	
	close(soundFileID);
}



int main(){
	loadSound("test.wav");
	
}