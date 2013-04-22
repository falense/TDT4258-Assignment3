#ifndef _game_h
#define _game_h

/*
  #include "sound.h"
  #include "screen.h"

  */

enum Block {White, Black, Blue, Red, Green,Yellow};
typedef enum Block Block;



#define H_BLOCKS 10
#define W_BLOCKS 10

#define FOOD_SCORE 70
#define MAX_BULLET_DISTANCE 400


enum Direction {Left, Right, Up, Down};
typedef enum Direction Direction;



Block player1Block = Blue;
Block player2Block = Yellow;
Block neutralGroundBlock = Green;
Block fireBlock = Red;
Block obstacleBlock = Black;
Block foodBlock = White;

/*

char player1Char = '@';
char player2Char = '&';
char neutralGroundChar = 'G';
char fireChar = 'F';
char obstacleChar = '#';
 
*/

struct Position{
	int x;
	int y;
};
typedef struct Position Position;

double player2Degrees;

Position player1Pos;
Position bulletPos;

int remainingFood;
int score;
//bool shotsFired;

//0-100
int charge;

Block gameBoard[H_BLOCKS][W_BLOCKS];
char symbolBoard[H_BLOCKS][W_BLOCKS];

//0 is SW7, 1 is SW6 etc etc
char buttonsPressed[8];

void initMainLoop();
void fillBoard();
void renderBoard();
void printBoard();
void testGame();
void setBoardBlock(unsigned int x, unsigned int y, Block b);
void adjustReticule(Direction d);
void tankCharge();
int getDistanceToTravel();
void moveBullet();
void mainLoop();
void interpretButtonInput(char driverInput);
void naive_wait(int wait);
void tankFire();


#endif

