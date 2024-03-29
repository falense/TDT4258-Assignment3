
#ifndef SCREEN_HEADER
#define SCREEN_HEADER


#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bmp.h"


enum Block {White, Black, Blue, Red, Green,Yellow, Food,Ghost1,Ghost2,Ghost3,Pacman,Rock,Ground};
typedef enum Block Block;

extern int screenDeviceID;

#define SCREENHEIGHT 240
#define SCREENWIDTH 320

#define H_BLOCKS 16
#define W_BLOCKS 21	

extern const unsigned int BLOCK_WIDTH;
extern const unsigned int BLOCK_HEIGHT;

extern char *currentFrameBuffer;
extern char  *nextFrameBuffer;

#define DEBUG 1


void initScreen();
void closeScreen();
void writeScreen(char* data, unsigned int start, unsigned int size);
void setPixel(unsigned int x, unsigned int y, Color c);
void setBlock(unsigned int bx,unsigned int by, Block b);


void clearScreen(Color c);
void clearScreenB();

void refreshScreen(char*buffer);

char* blockToData(Block b);
#endif
