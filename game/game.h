#ifndef _game_h
#define _game_h


//#include "sound.h"
#include "screen.h"
#include "bmp.h"
#include "ledbuttons.h"

#define startingPosX 10
#define startingPosY 11

#define ghost1StartX 9
#define ghost2StartX 10
#define ghost3StartX 11
#define ghost1StartY 8 
#define ghost2StartY 8
#define ghost3StartY 8

#define FOOD_SCORE 100
#define startingLives 8
#define TRUE 1
#define FALSE 0

enum Direction {Left, Right, Up, Down, NoMove};
typedef enum Direction Direction;

Block player1Block = Pacman;
Block neutralGroundBlock = Ground;
Block obstacleBlock = Rock;
Block ghost1Block = Ghost1;
Block ghost2Block = Ghost2;
Block ghost3Block = Ghost3;
Block foodBlock = Food;

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
int timeStep;

Block gameBoard[W_BLOCKS][H_BLOCKS];
char foodLocation[W_BLOCKS][H_BLOCKS];
char changedFlag[W_BLOCKS][H_BLOCKS];
unsigned char ghost1WalkCount[W_BLOCKS][H_BLOCKS];
unsigned char ghost2WalkCount[W_BLOCKS][H_BLOCKS];
unsigned char ghost3WalkCount[W_BLOCKS][H_BLOCKS];

const Position startingPosition = {.x=startingPosX, .y=startingPosY};
const Position ghost1StartPosition = {.x=ghost1StartX, .y=ghost1StartY};
const Position ghost2StartPosition = {.x=ghost2StartX, .y=ghost2StartY};
const Position ghost3StartPosition = {.x=ghost3StartX, .y=ghost3StartY};

void initMainLoop();
void fillBoard();
void renderBoard();
void printBoard();
void setBoardBlock(unsigned int x, unsigned int y, Block b);
void mainLoop();
void interpretButtonInput(char driverInput);
int naive_wait(int wait);
Direction determineGhostMove(Position ghostPosition, Block ghost);
void drawBoard();
void foodObtained();
void setLifeBar(int lives);
void hitByGhost();
void levelCleared();
int walkIntoGhost(int x, int y);
int distanceToPlayer(Position pos);
void flagForRender(int x, int y);


#endif

