#ifndef _game_h
#define _game_h


//#include "sound.h"
#include "screen.h"
#include "bmp.h"
#include "ledbuttons.h"

#define startingPosX 10
#define startingPosY 11
#define FOOD_SCORE 70
#define startingLives 3
#define TRUE 1
#define FALSE 0

enum Direction {Left, Right, Up, Down};
typedef enum Direction Direction;

Block player1Block = Yellow;
Block neutralGroundBlock = Blue;
Block obstacleBlock = Black;
Block ghost1Block = White;
Block ghost2Block = White;
Block ghost3Block = White;
Block foodBlock = Red;

char foodChar = '*';

struct Position{
	int x;
	int y;
};
typedef struct Position Position;

Position player1Pos;
Position ghost1Pos;
Position ghost2Pos;
Position ghost3Pos;

int remainingFood;
int score;
int remainingLives;

Block gameBoard[W_BLOCKS][H_BLOCKS];
char foodLocation[W_BLOCKS][H_BLOCKS];
char changedFlag[W_BLOCKS][H_BLOCKS];
int ghost1WalkCount[W_BLOCKS][H_BLOCKS];
int ghost2WalkCount[W_BLOCKS][H_BLOCKS];
int ghost3WalkCount[W_BLOCKS][H_BLOCKS];

const Position startingPosition = {.x=startingPosX, .y=startingPosY};

void initMainLoop();
void fillBoard();
void renderBoard();
void printBoard();
void setBoardBlock(unsigned int x, unsigned int y, Block b);
void mainLoop();
void interpretButtonInput(char driverInput);
void naive_wait(int wait);
Direction determineGhostMove(Position ghostPosition);
void drawBoard();
void foodObtained();
void setLifeBar(int lives);
void hitByGhost();
void levelCleared();
void walkIntoGhost(int x, int y);
double distanceToPlayer(Position pos);


#endif

