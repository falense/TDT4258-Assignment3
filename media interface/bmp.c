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
struct Bitmap{
	int width;
	int height;
	char *pixels;
	unsigned int fileSize;
	unsigned int pixelArrayOffset;
};
typedef struct Bitmap Bitmap;

Bitmap* loadBitmap(char * filename){

	bitmapFileID = open(filename,O_RDONLY);

	if(bitmapFileID < 0)
	{
		printf("Didnt manage to open screen block device.");
		return NULL;
	}
	Bitmap * image = (Bitmap*)malloc(sizeof(Bitmap));
	
	lseek(bitmapFileID, 2, SEEK_SET);
	ssize_t bytesread = write(bitmapFileID, (void*)image.fileSize,4);
	printf("%d",image.fileSize);
	
	
	lseek(bitmapFileID, 10, SEEK_SET);
	ssize_t bytesread = write(bitmapFileID, (void*)image.pixelArrayOffset,4);
	printf("%d",image.fileSize);
	
	close(bitmapFileID);
}

void saveBitmap(char *filename, Bitmap * image){

	 bitmapFileID = open(filename,O_WRONLY);

	if(bitmapFileID < 0)
	{
		printf("Didnt manage to open screen block device.");
		return NULL;
	}
	
	
	ssize_t written = write(soundDeviceID, &data,1);
	if(written >= 0)
		;  // handle successful write (which might be a partial write!)
	else if(errno == EWOULDBLOCK)
		printf("Error writing");
	else printf("Error writing");
	
	close(bitmapFileID);

}
void setPixel(unsigned int x, unsigned int y, Color c){
	if (x >= SCREENHEIGHT || y >= SCREENWIDTH ) return;
	//printf("Pixel (%d,%d)\n",x,y);
	char t[3];
	t[0] = c.red;
	t[1] = c.green;
	t[2] = c.blue;
}



int main(){
	loadBitmap("test.bmp");
	
}