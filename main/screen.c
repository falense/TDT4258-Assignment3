


int screenDeviceID = -1;

#include "screen.h"

char *currentFrameBuffer;
char *nextFrameBuffer;

unsigned int pixelsChanged = 0;
unsigned int smartUpdateMinY = SCREENHEIGHT;
unsigned int smartUpdateMaxY = 0;

const unsigned int BLOCK_WIDTH = SCREENWIDTH/W_BLOCKS;
const unsigned int BLOCK_HEIGHT = SCREENHEIGHT/H_BLOCKS;

Bitmap ** tiles;
#define NUMTILES 10
void refreshScreen(char*buffer){

/*
	lseek(screenDeviceID, 0, SEEK_SET);
	write(screenDeviceID, buffer,SCREENWIDTH*SCREENHEIGHT*3);
	return;*/
	pixelsChanged = 0;	

	unsigned int smartUpdateDiffY = smartUpdateMaxY -smartUpdateMinY;
	unsigned int lengthUpdate = smartUpdateDiffY*3*SCREENWIDTH;



	lseek(screenDeviceID, SCREENWIDTH*smartUpdateMinY*3, SEEK_SET);
	ssize_t written = write(screenDeviceID, buffer+SCREENWIDTH*smartUpdateMinY*3,lengthUpdate);
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

	tiles = (Bitmap**)malloc(sizeof(Bitmap)*NUMTILES);
	tiles[0] = loadBitmap("./resources/images/food.bmp");
	tiles[1] = loadBitmap("./resources/images/ghost1.bmp");
	tiles[2] = loadBitmap("./resources/images/ghost2.bmp");
	tiles[3] = loadBitmap("./resources/images/ghost3.bmp");
	tiles[4] = loadBitmap("./resources/images/pacman.bmp");
	tiles[5] = loadBitmap("./resources/images/rock.bmp");
	tiles[6] = loadBitmap("./resources/images/ground.bmp");

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
	if (y >= SCREENHEIGHT || x >= SCREENWIDTH ) return;
	
	if (y < smartUpdateMinY) smartUpdateMinY = y;
	if (y > smartUpdateMaxY) smartUpdateMaxY = y;

	unsigned int index = 3*(y*SCREENWIDTH+x);
	
	currentFrameBuffer[index] = c.blue;
	currentFrameBuffer[index+1] = c.green;
	currentFrameBuffer[index+2] = c.red;
	pixelsChanged++;
	
}



void setBlock(unsigned int bx,unsigned int by, Block b){
	int baseX = bx*BLOCK_WIDTH;
	int baseY = by*BLOCK_HEIGHT;
	Color c;
	int simpleBlock = 1;
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
		default:
			simpleBlock = 0;
			break;
			

	}
	if (simpleBlock){
		for (unsigned int i = 0; i < BLOCK_WIDTH; i++){
			for (unsigned int j = 0; j < BLOCK_HEIGHT; j++){
				setPixel(i+baseX,j+baseY,c);
			}
		}
	}
	else{
		Bitmap * image;
		switch(b){
			case Food:
				image = tiles[0];
				break;
			case Ghost1:
				image = tiles[1];
				break;
			case Ghost2:
				image = tiles[2];
				break;
			case Ghost3:
				image = tiles[3];
				break;
			case Pacman:
				image = tiles[4];
				break;
			case Rock:
				image = tiles[5];
				break;
			case Ground:
				image = tiles[6];
				break;
		}
		if (!image){
			printf("No bitmap was loaded during block write\n");
			return;
		}
		for (unsigned int i = 0; i < BLOCK_WIDTH; i++){
			for (unsigned int j = 0; j < BLOCK_HEIGHT; j++){
				Color d = getPixel(i,j,image);
				setPixel(i+baseX,j+baseY,d);
			}
		}
		
		free(image);
	}
}

void clearScreen(Color c){
	for(int i = 0; i < SCREENWIDTH; i++)
		for(int j = 0; j < SCREENHEIGHT; j++)
			setPixel(i,j,c);
	refreshScreen(currentFrameBuffer);
}
void clearScreenB(){
	Color c = {.red = 0, .green = 0, .blue = 0};
	
	clearScreen(c);
	//clearScreen(c);

}
