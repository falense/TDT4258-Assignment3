
#include "game.h"
#include <stdio.h>
#include <stdlib.h> 
#include <math.h>

/* 
 This file will include the game's logic. 

 It will also instruct the screen framework to put display what it want.
 
 There should be a game loop that continously calls the render() function of
 screen.c, while checking other types of game logic.
 
 Button interrupts or polling?
 
 Either way, button presses should in some way manipulate the world.
 
 */

void testGame() {
    
}



void performMove(Direction d) {
    
    int x = player1Pos.x;
    int y = player1Pos.y;
    
    switch(d){
		case Left:
            // player1Pos.y - 1
            if (player1Pos.y > 0 && gameBoard[x][y - 1] != obstacleBlock) {
                
                //Check for food
                if (gameBoard[x][y-1] == foodBlock) {
                    remainingFood--;
                }
                
                //Check for Death
                if (gameBoard[x][y-1] == fireBlock) {
                    printf("Game Over! \n");
                    fillBoard();
                }
                
                setBoardBlock(x, y - 1 , player1Block);
                setBoardBlock(x, y, neutralGroundBlock);
                player1Pos.y--;
            }
            
			break;
		case Right:
            // player1Pos.y + 1
            if ((player1Pos.y < 9 && gameBoard[x][y + 1] != obstacleBlock) && (gameBoard[x][y + 1] != player2Block) ) {
                
                //Check for food
                if (gameBoard[x][y+1] == foodBlock) {
                    score+=FOOD_SCORE;
                    remainingFood--;
                }
                
                //Check for Death
                if (gameBoard[x][y+1] == fireBlock) {
                    printf("Game Over! \n");
                    fillBoard();
                }
                
                setBoardBlock(x, y + 1 , player1Block);
                setBoardBlock(x, y, neutralGroundBlock);
                player1Pos.y++;
            }
            
			break;
		case Up:
            // player1Pos.x - 1
            if ((player1Pos.x > 0 && gameBoard[x - 1][y] != obstacleBlock) && (gameBoard[x - 1][y] != player2Block)) {
                
                //Check for food
                if (gameBoard[x-1][y] == foodBlock) {
                    score+=FOOD_SCORE;
                    remainingFood--;
                }
                
                //Check for Death
                if (gameBoard[x-1][y] == fireBlock) {
                    printf("Game Over! \n");
                    fillBoard();
                }
                
                setBoardBlock(x - 1, y , player1Block);
                setBoardBlock(x, y, neutralGroundBlock);
                player1Pos.x--;
            }
            
			break;
		case Down:
            // Player1Pos.x + 1
            if ((player1Pos.x < 9 && gameBoard[x+1][y] != obstacleBlock) && (gameBoard[x+1][y] != player2Block)) {
                
                //Check for food
                if (gameBoard[x+1][y] == foodBlock) {
                    score+=FOOD_SCORE;
                    remainingFood--;
                }
                
                //Check for Death
                if (gameBoard[x+1][y] == fireBlock) {
                    printf("Game Over! \n");
                    fillBoard();
                }
                
                setBoardBlock(x + 1, y , player1Block);
                setBoardBlock(x, y, neutralGroundBlock);
                player1Pos.x++;
            }
			break;
            
    }
    
    printBoard();
    printf("Player position, X: %d Y: %d\n", player1Pos.x, player1Pos.y);
    printf("Remaining Food: %d\n", remainingFood);
    if (remainingFood == 0) {
        printf("You are winner! Score: %d", score);
    }
    printf("\n");
    
}

//Measure the charge of the tank shot
//The leds pn the microcontroller should display the charge level, so write to the driver
void tankCharge() {
    
    charge += 10;
}

//Distance in pixel the bullet should travel
int getDistanceToTravel() {
    
    return (int) (MAX_BULLET_DISTANCE * (charge/100));
    
}

void moveBullet(double dx, double dy, double remainingDistance) {
    
    bulletPos.x -= dx;
    bulletPos.y -= dy;
    
    //printf("sqrt %p\n", sqrt);
    //remainingDistance -= sqrt(dx*dx + dy*dy);
    
    if (remainingDistance <= 0) {
        //Bomb explodes, shit happens
    }
    
}

void naive_wait(int wait){ // wait in ms
	wait = wait;
	while(wait > 0){
		int a = wait*wait;
		wait--;
	}
}
    
void checkHit() {
        
}


int main(){

/*
    int i = 9;
    char *buttons_pressed;
    buttons_pressed = malloc(sizeof(char));
    *buttons_pressed = (char) i;
    printf("char: %s\n", buttons_pressed);
    char c128 = (char) i;
    
    if(*buttons_pressed & c128 == c128){
        sw7_pressed();

    }
    */
    /*
    char byte = 0x0;
    printBoard();
    printf("\n");
    interpretButtonInput(byte);
    */

    mainLoop();

    return 0;
}

//A possible version of the main function/loop
void mainLoop() {
    
    fillBoard();
    
    int fakeTimer = 0;
    
    //Periodically check for input and other stuff
    while (1) {
        
        //Wait
        naive_wait(100000000);
        
        //Check for input
        char driverInput = 0x80;
        
        //Determine what buttons have been pressed, and execute the action
        interpretButtonInput(driverInput);

        //Move Bullet
        
        //Refresh Screen
        renderBoard();
    }
    
    
}

void interpretButtonInput(char driverInput) {

    if (driverInput == 0) return; 
    
  
    if((driverInput & 0x80) != 0) { //SW7 pressed
        performMove(Up);
    }

    if((driverInput & 0x40) != 0) { //SW6 pressed
        performMove(Down);
    }

    if((driverInput & 0x20) != 0) { //SW5 pressed
        performMove(Left);
    }

    if((driverInput & 0x10) != 0) { //SW4 pressed
        performMove(Right);
    }

    if((driverInput & 0x4) != 0) { //SW2 pressed
        tankCharge();
    } else if (charge > 0){
        tankFire();
    }

    if((driverInput & 0x2) != 0) { //SW1 pressed
        adjustReticule(Up);
    }

    if((driverInput & 0x1) != 0) { //SW0 pressed
        adjustReticule(Down);
    }
    
}

void tankFire() {


}


void adjustReticule(Direction d) {
    
    if ((player2Degrees >= 90 && d == Up) || (player2Degrees <= 0 && d == Down)) return;
    
    switch(d){
        case Up:
            player2Degrees += 5;
            break;
        case Down:
            player2Degrees -= 5;
            break;
            
    }
    
}

void renderBoard(){
	
    /*   
	for (int i = 0; i < H_BLOCKS; i++){
		for(int j = 0; j < W_BLOCKS; j++){
            setBlock(i,j,board[i][j]);
		}
	}
    refreshScreen(currentFrameBuffer);
    */

     
}
    
    void printBoard() {
        
        int i, j;
        for (i = 0; i < H_BLOCKS; i++){
            for(j = 0; j < W_BLOCKS; j++){
                
                Block b = gameBoard[i][j];
                
                if (j == 0) {
                    printf("|");
                }
                
                if (b == player1Block) {
                    printf("@");
                } else if (b == player2Block) {
                    printf("&");
                } else if (b == fireBlock) {
                    printf("^");
                } else if (b == neutralGroundBlock) {
                    printf(" ");
                } else if (b == obstacleBlock) {
                    printf("#");
                } else if (b == foodBlock) {
                    printf("·");
                } 
                
                printf("|");
                
            }
            
            printf("\n");
        }
        
    }
    
void setBoardBlock(unsigned int x, unsigned y, Block b) {
    
    if (x > H_BLOCKS || y > W_BLOCKS) return;
    
    gameBoard[x][y] = b;
}


//Initial board settings
void fillBoard() {
    
    //Fill out obstacles
    gameBoard[2][1] = obstacleBlock;
    gameBoard[2][2] = obstacleBlock;
    gameBoard[5][3] = obstacleBlock;
    gameBoard[6][3] = obstacleBlock;
    gameBoard[7][7] = obstacleBlock;
    gameBoard[7][8] = obstacleBlock;
    gameBoard[0][8] = obstacleBlock;
    gameBoard[1][9] = obstacleBlock;
    gameBoard[1][8] = obstacleBlock;
    
    player1Pos.x = 9;
    player1Pos.y = 0;
    
    //Player 1 (Mover)
    gameBoard[player1Pos.x][player1Pos.y] = player1Block;
    
    //Player 2 (Shooter)
    gameBoard[0][9] = player2Block;
    
    //Set Player 2 Reticule degree
    player2Degrees = 45.0;

    remainingFood = 0;
    
    //Fill food ground
    int i,j;
    for (i = 0; i < H_BLOCKS; i++){
        for(j = 0; j < W_BLOCKS; j++){
            if (gameBoard[i][j] != obstacleBlock && gameBoard[i][j] != player1Block && gameBoard[i][j] != player2Block) {
                gameBoard[i][j] = foodBlock;
                remainingFood++;
            }
        }
    }
    
}
