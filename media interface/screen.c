
#include "screen.h"

void initScreen(){

	 screenDeviceID = open("/dev/fb0",O_RDWR | O_NONBLOCK);

	if(screenDeviceID < 0)
	{
		printf("Didnt manage to open screen block device.");
		exit(0);
	}
		;  // handle error

	char a = ' ';
	for(unsigned int i = 0; i < SCREENHEIGHT; i++)
		for (unsigned int j = 0; j < SCREENWIDTH; j++)
			write(screenDeviceID,&a,1);
}
void closeScreen(){
	close(screenDeviceID);
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
	//printf("Pixel (%d,%d)\n",x,y);
	char t[3];
	t[0] = c.red;
	t[1] = c.green;
	t[2] = c.blue;
	writeScreen(t, 4*(x*SCREENWIDTH+y), 3);
}



void setBlock(unsigned int bx,unsigned int by, Block b){
	int baseX = bx*BLOCK_HEIGHT;
	int baseY = by*BLOCK_WIDTH;
	Color c = {0,0,0};
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
}
void clearScreen(){
	Color c = {.red = 0, .green = 0, .blue = 0};
	clearScreen(c);

}
