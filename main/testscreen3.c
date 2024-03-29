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
Block board[W_BLOCKS][H_BLOCKS];
int boardFlag[W_BLOCKS][H_BLOCKS];

struct Position{
	int x;
	int y;
};
typedef struct Position Position;

Position playerPos;
void fillBoard(){
	for (int i = 0; i < W_BLOCKS; i++){
		for(int j = 0; j < H_BLOCKS; j++){
			board[i][j] = Ground;
			boardFlag[i][j] = 1;
		}
	}

	for (int i = 0; i < H_BLOCKS*W_BLOCKS/4; i++){
		int x = rand()%W_BLOCKS;
		int y = rand()%H_BLOCKS;
		board[x][y] = Red;
	}
	for(int j = 0; j < H_BLOCKS; j++){
		board[0][j] = Rock;
		board[W_BLOCKS-1][j] = Rock;
	}
	for (int i = 0; i < W_BLOCKS; i++){
		board[i][0] = Rock;
		board[i][H_BLOCKS-1] = Rock;
	}
	for (int i = 0; i < H_BLOCKS*W_BLOCKS/4; i++){
		int x = rand()%W_BLOCKS;
		int y = rand()%H_BLOCKS;
		board[x][y] = Rock;
	}

	int x = (rand()%(W_BLOCKS-2))+1;
	int y = (rand()%(H_BLOCKS-2))+1;
	playerPos.x = x;
	playerPos.y = y;
	board[x][y] = Pacman;
}
void printBoard(){
	
	for (int i = 0; i < W_BLOCKS; i++){
		for(int j = 0; j < H_BLOCKS; j++){
			if(boardFlag[i][j] == 1){
			 setBlock(i,j,board[i][j]);
			boardFlag[i][j] = 0;			
			}
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
	while(board[playerPos.x+x][playerPos.y+y] == Rock){
		 x = rand()%3-1;
		 y = rand()%3-1;
		while(x == 0 && y == 0){
		x = rand()%3-1;
		y = rand()%3-1;
		}
		
	}
	boardFlag[playerPos.x][playerPos.y] = 1;
	boardFlag[playerPos.x+x][playerPos.y+y] = 1;

	board[playerPos.x][playerPos.y] = Ground;
	board[playerPos.x+x][playerPos.y+y] = Pacman;
	playerPos.x = playerPos.x+x;
	playerPos.y = playerPos.y+y;


}

int main(){
	initScreen();
	lcdTest();
	while(1){
		fillBoard();
		printBoard();
		for (int i = 0; i < 1000; i++){
			playerStep();
			printBoard();
		}
	}
	closeScreen();

}
