


int screenDeviceID = -1;

#include "screen.h"

char *currentFrameBuffer;
char *nextFrameBuffer;

unsigned int pixelsChanged = 0;
unsigned int smartUpdateMinX = SCREENHEIGHT;
unsigned int smartUpdateMaxX = 0;

const unsigned int BLOCK_WIDTH = SCREENWIDTH/W_BLOCKS;
const unsigned int BLOCK_HEIGHT = SCREENHEIGHT/H_BLOCKS;
void refreshScreen(char*buffer){
	pixelsChanged = 0;	

	unsigned int smartUpdateDiffX = smartUpdateMaxX -smartUpdateMinX;
	unsigned int lengthUpdate = smartUpdateDiffX*3*SCREENWIDTH;


	lseek(screenDeviceID, SCREENWIDTH*smartUpdateMinX*3, SEEK_SET);
	ssize_t written = write(screenDeviceID, buffer+SCREENWIDTH*smartUpdateMinX*3,lengthUpdate);
	if(written >= 0)
		;  // handle successful write (which might be a partial write!)
	else if(errno == EWOULDBLOCK)
		printf("Error writing");
	else printf("Error writing");
}
void initScreen(){

	 screenDeviceID = open("/dev/fb0",O_RDWR | O_NONBLOCK);

	if(screenDeviceID < 0)
	{
		printf("Didnt manage to open screen block device.");
		exit(0);
	}
		;  // handle error
	currentFrameBuffer = (char*)malloc(sizeof(char)*SCREENWIDTH*SCREENHEIGHT*3);
	nextFrameBuffer = (char*)malloc(sizeof(char)*SCREENWIDTH*SCREENHEIGHT*3);
	clearScreenB();
}
void closeScreen(){
	close(screenDeviceID);
	free(currentFrameBuffer);
	free(nextFrameBuffer);
}


void writeScreen(char* data, unsigned int start, unsigned int size){
	//printf("\tStart %d, size %d\n",start,size);

	lseek(screenDeviceID, start, SEEK_SET);
	ssize_t written = write(screenDeviceID, data,size);
	if(written >= 0)
		;  // handle successful write (which might be a partial write!)
	else if(errno == EWOULDBLOCK)
		printf("Error writing");
	else printf("Error writing");


}
void setPixel(unsigned int x, unsigned int y, Color c){
	if (x >= SCREENHEIGHT || y >= SCREENWIDTH ) return;
	
	if (x < smartUpdateMinX) smartUpdateMinX = x;
	if (x > smartUpdateMaxX) smartUpdateMaxX = x;

	unsigned int index = 3*(x*SCREENWIDTH+y);
	
	currentFrameBuffer[index] = c.blue;
	currentFrameBuffer[index+1] = c.green;
	currentFrameBuffer[index+2] = c.red;
	pixelsChanged++;
	
}



void setBlock(unsigned int bx,unsigned int by, Block b){
	int baseX = bx*BLOCK_HEIGHT;
	int baseY = by*BLOCK_WIDTH;
Color c;
	switch(b){
		case Black:
			c.red = 0;
			c.green = 0;
			c.blue = 0;
			break;
		case White:
			c.red = 255;
			c.green = 255;
			c.blue = 255;
			break;
		case Blue:
			c.red = 0;
			c.green = 0;
			c.blue = 255;
			break;
		case Red:
			c.red = 255;
			c.green = 0;
			c.blue = 0;
			break;
		case Yellow:
			c.red = 255;
			c.green = 255;
			c.blue = 0;
			break;
			

	}
	for (unsigned int i = 0; i < BLOCK_HEIGHT; i++){
		for (unsigned int j = 0; j < BLOCK_WIDTH; j++){
			setPixel(i+baseX,j+baseY,c);
		}
	}
}

void clearScreen(Color c){
	for(int i = 0; i < SCREENHEIGHT; i++)
		for(int j = 0; j < SCREENWIDTH; j++)
			setPixel(i,j,c);
	refreshScreen(currentFrameBuffer);
}
void clearScreenB(){
	Color c = {.red = 0, .green = 0, .blue = 0};
	
	clearScreen(c);
	//clearScreen(c);

}