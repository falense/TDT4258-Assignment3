
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "media.h"

void initScreen(){
///dev/ttyPA1
#ifdef DEBUG
	 fileHandle = open("testfile.dat",O_CREAT | O_RDWR);
#endif
/*
#ifndef DEBUG
	 fileHandle = open("/dev/ttyPA1",O_RDWR | O_NONBLOCK);
#endif
*/

	if(fileHandle < 0)
	{
		printf("Didnt manage to open screen block device.");
		exit(0);
	}
		;  // handle error

	char a = ' ';
	for(unsigned int i = 0; i < SCREENHEIGHT; i++)
		for (unsigned int j = 0; j < SCREENWIDTH; j++)
			write(fileHandle,&a,1);
}
void closeScreen(){

	close(fileHandle);
}


void writeScreen(char* data, unsigned int start, unsigned int size){
	//printf("\tStart %d, size %d\n",start,size);

	lseek(fileHandle, start, SEEK_SET);
	ssize_t written = write(fileHandle, data,size);
	if(written >= 0)
		;  // handle successful write (which might be a partial write!)
	else if(errno == EWOULDBLOCK)
		printf("Error writing");
	else printf("Error writing");


}
void setPixel(unsigned int x, unsigned int y, Color c){
	if (x >= SCREENHEIGHT || y >= SCREENWIDTH ) return;
	//printf("Pixel (%d,%d)\n",x,y);
	char t[3];
	t[0] = c.red;
	t[1] = c.green;
	t[2] = c.blue;
	writeScreen(t, 3*(x*SCREENWIDTH+y), 3);
}



void setBlock(unsigned int bx,unsigned int by, Block b){
	int baseX = bx*BLOCK_HEIGHT;
	int baseY = by*BLOCK_WIDTH;
	Color c = {'a','b','c'};
	for (unsigned int i = 0; i < BLOCK_HEIGHT; i++){
		for (unsigned int j = 0; j < BLOCK_WIDTH; j++){
			setPixel(i+baseX,j+baseY,c);
		}
	}
}


int main(){
	initScreen();
	printf("Screen (%dx%d).\n",SCREENWIDTH, SCREENHEIGHT);
	printf("Blocks (%dx%d).\n",W_BLOCKS, H_BLOCKS);
	printf("Block size (%dx%d).\n",BLOCK_WIDTH, BLOCK_HEIGHT);
	
	setBlock(1,1,White);
	//setBlock(1,2,White);
	closeScreen();

}