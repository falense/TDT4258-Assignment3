//http://servv89pn0aj.sn.sourcedns.com/~gbpprorg/guerrilla.net/reference/dsp/prog_dsp.htm

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
#include "screen.h"
#include "ledbuttons.h"
//#include "game.h"

#include "testgame.h"



int main() {
	//mainLoop();
	testfunc();
	/*
	initLedButtons();
	//mainLoop();

	closeLedButtons();
	*/
	//return 0;
}

 /*
Block board[H_BLOCKS][W_BLOCKS];

struct Position{
	int x;
	int y;
};
typedef struct Position Position;

Position playerPos;
void fillBoard(){
	for (int i = 0; i < H_BLOCKS; i++){
		for(int j = 0; j < W_BLOCKS; j++){
			board[i][j] = White;
		}
	}

	for (int i = 0; i < H_BLOCKS*W_BLOCKS/4; i++){
		int x = rand()%H_BLOCKS;
		int y = rand()%W_BLOCKS;
		board[x][y] = Red;
	}

	for(int j = 0; j < W_BLOCKS; j++){
		board[0][j] = Black;
		board[H_BLOCKS-1][j] = Black;
	}
	for (int i = 0; i < H_BLOCKS; i++){
		board[i][0] = Black;
		board[i][W_BLOCKS-1] = Black;
	}
	for (int i = 0; i < H_BLOCKS*W_BLOCKS/4; i++){
		int x = rand()%H_BLOCKS;
		int y = rand()%W_BLOCKS;
		board[x][y] = Black;
	}

	int x = (rand()%(H_BLOCKS-2))+1;
	int y = (rand()%(W_BLOCKS-2))+1;
	playerPos.x = x;
	playerPos.y = y;
	board[x][y] = Yellow;
}
void printBoard(){
	
	for (int i = 0; i < H_BLOCKS; i++){
		for(int j = 0; j < W_BLOCKS; j++){
			 setBlock(i,j,board[i][j]);
		}
	}
refreshScreen(currentFrameBuffer);	
}
void lcdTest(){

	printf("Screen (%dx%d).\n",SCREENWIDTH, SCREENHEIGHT);
	printf("Blocks (%dx%d).\n",W_BLOCKS, H_BLOCKS);
	printf("Block size (%dx%d).\n",BLOCK_WIDTH, BLOCK_HEIGHT);
	Color w = {.red = 255,.green = 0,.blue = 0};
	for (int c = 0; c < H_BLOCKS; c++){
			if (c % 2 == 0) setBlock(c,c,Red);
			else setBlock(c,c,Blue);
	}
		refreshScreen(currentFrameBuffer);
}
void playerStep(){
	
	int x = rand()%3-1;
	int y = rand()%3-1;
	while(board[playerPos.x+x][playerPos.y+y] == Black){
		 x = rand()%3-1;
		 y = rand()%3-1;
		while(x == 0 && y == 0){
		x = rand()%3-1;
		y = rand()%3-1;
		}
		
	}
	board[playerPos.x][playerPos.y] = White;
	board[playerPos.x+x][playerPos.y+y] = Yellow;
	playerPos.x = playerPos.x+x;
	playerPos.y = playerPos.y+y;


}

int main(){
	initScreen();
	initSound();
	initLedButtons();
	lcdTest();
	while(1){
		fillBoard();
		printBoard();
		
		for (int i = 0; i < 100; i++){
			setLeds((char)i);
			setFrequency(120*(i%20));
			playerStep();
			printBoard();
			playSounds();
			if (readButtons() & 0x01 > 0) break;
		}
	}
	closeLedButtons();
	closeScreen();
	closeSound();

}
*/
