#ifndef _game_h
#define _game_h

#include "screen.h"
#include "bmp.h"
#include "ledbuttons.h"

/* DEFINITIONS */ 
 
//Player starting coordinates
#define startingPosX 10
#define startingPosY 11

//Ghosts starting coordinates
#define ghost1StartX 9
#define ghost2StartX 10
#define ghost3StartX 11
#define ghost1StartY 8 
#define ghost2StartY 8
#define ghost3StartY 8

//Game difficulty, determines how many food pieces you need to fetch.
#define difficulty 2

//How much score per food item
#define FOOD_SCORE 100

//Player starting lives
#define startingLives 8

#define TRUE 1
#define FALSE 0

/* GLOBAL VARIABLES */

//Global structs and enums
enum Direction {Left, Right, Up, Down, NoMove};
typedef enum Direction Direction;

struct Position{
	int x;
	int y;
};
typedef struct Position Position;

//Other Global variables
char foodChar = '*';
int timeStep;

//Game status information
int remainingFood;
int score;
int remainingLives;

//Blocks used in rendering and game logic
Block player1Block = Pacman;
Block neutralGroundBlock = Ground;
Block obstacleBlock = Rock;
Block ghost1Block = Ghost1;
Block ghost2Block = Ghost2;
Block ghost3Block = Ghost3;
Block foodBlock = Food;

//Keeps track of position
Position player1Pos;
Position ghost1Pos;
Position ghost2Pos;
Position ghost3Pos;

//Starting position constants
const Position startingPosition = {.x=startingPosX, .y=startingPosY};
const Position ghost1StartPosition = {.x=ghost1StartX, .y=ghost1StartY};
const Position ghost2StartPosition = {.x=ghost2StartX, .y=ghost2StartY};
const Position ghost3StartPosition = {.x=ghost3StartX, .y=ghost3StartY};

//Keeps track of various information on the 2D game board
Block gameBoard[W_BLOCKS][H_BLOCKS];

//Keeps track of which blocks has a food in it.
char foodLocation[W_BLOCKS][H_BLOCKS];

//Used with optimized render
char changedFlag[W_BLOCKS][H_BLOCKS];

//Used by the ghost AI
unsigned char ghost1WalkCount[W_BLOCKS][H_BLOCKS];
unsigned char ghost2WalkCount[W_BLOCKS][H_BLOCKS];
unsigned char ghost3WalkCount[W_BLOCKS][H_BLOCKS];

/* METHODS */

//Initialization methods
void fillBoard();
void drawBoard();

//Main Loop
void mainLoop();

//Movement methods
void ghostsMoveTurn();
Direction determineGhostMove(Position ghostPosition, Block ghost);
void performMove(Direction d, Position currentPos, Block b);
void moveGhost(Direction d, Position p, Block b);
char possibleMoves(int x, int y);
short walkable(int x, int y);

//Render methods
void renderBoard(int optimize);

//Hit detection methods
int walkIntoGhost(int x, int y);
void hitByGhost();
void foodObtained();

//Setter/getter methods
void setLifeBar(int lives);
void setFlagForRender(int x, int y);
void setBoardBlock(unsigned int x, unsigned y, Block b)
unsigned char * getWalkCount(int x, int y, Block b)
Position getMonsterPosition(Block b);

//Helper methods
int naive_wait(int wait);
int distanceToPlayer(Position pos);
void interpretButtonInput(char driverInput);

//Game end methods
void displayWin()
void displayLose()
void levelCleared();



#endif

