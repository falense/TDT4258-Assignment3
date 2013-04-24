//http://servv89pn0aj.sn.sourcedns.com/~gbpprorg/guerrilla.net/reference/dsp/prog_dsp.htm

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "screen.h"

void lcdTest(){

	printf("Screen (%dx%d).\n",SCREENWIDTH, SCREENHEIGHT);
	printf("Blocks (%dx%d).\n",W_BLOCKS, H_BLOCKS);
	printf("Block size (%dx%d).\n",BLOCK_WIDTH, BLOCK_HEIGHT);
	memset(currentFrameBuffer, 10, SCREENWIDTH*SCREENHEIGHT*3);
	refreshScreen(currentFrameBuffer);
/*
	Color w = {.red = 255,.green = 0,.blue = 0};
	for (int c = 0; c < H_BLOCKS; c++){
			if (c % 2 == 0) setBlock(c,c,Red);
			else setBlock(c,c,Blue);
	}*/
	memset(currentFrameBuffer, (unsigned char)255, SCREENWIDTH*SCREENHEIGHT*3);
		refreshScreen(currentFrameBuffer);
}

int main(){
	initScreen();
	lcdTest();
	Bitmap * b = loadBitmap("./resources/images/test.bmp");
	printf("Height: %d Width: %d\n",b->height, b->width);
	int x,y;
	for (x = 0; x < 10; x++){
		for(y = 0; y < 10; y++){
			Color *c = getPixel(x,y,b);
			printf("Red %d Green %d Blue %d\n",c->red,c->green,c->blue);
			free(c);
		}
	}
	for (x = 0; x < b->height; x++){
		for(y = 0; y < b->width; y++){
			Color *c = getPixel(x,y,b);
			setPixel(x,y,c);
			free(c);
		}
	}
		refreshScreen(currentFrameBuffer);
	finalizeBitmap(b);
	closeScreen();

}
