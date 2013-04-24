
#include "game.h"
#include <stdio.h>
#include <stdlib.h> 
#include <math.h>

/* 
 This file will include the game's logic. 

 It will also instruct the screen framework to put display what it want.
 
 */

//Move the unit standing on the currentPos in the direction d

void foodObtained(int x, int y) {

    score+=FOOD_SCORE;
    remainingFood--;
    foodLocation[x][y] == '0';
}

void hitByGhost() {

    remainingLives--;

    if (remainingLives == 0) { //Player Game Over, print score and reset board
        printf("Game Over! Total Score: %d", score);
        fillBoard();
    } else {

        //Adjust lifebar
        setLifeBar(remainingLives);

        //Return to start
        player1Pos = startingPosition;
    }

    
}

double distanceToPlayer(Position pos) {

    double powX = pow(pos.x - player1Pos.x, 2);
    double powY = pow(pos.y - player1Pos.y, 2);

    return sqrt(powX + powY);
}

void levelCleared() {

    //Check if level is cleared
    if (remainingFood == 0) {
        printf("Level Completed. Cumulative Score Between Rounds: %d\n", score);

         //Give an extra life, up to max 3
        if (remainingLives > 0 && remainingLives != 3) {
            printf("You regain a lost life!\n");
            remainingLives++;
        } 

        fillBoard();
    }
}

void walkIntoGhost(int x, int y) {

    if (gameBoard[x][y] == ghost1Block) {
        hitByGhost();
    } else if (gameBoard[x][y] == ghost2Block) {
        hitByGhost();
    } else if (gameBoard[x][y] == ghost3Block) {
        hitByGhost();
    }
}

void performMove(Direction d, Position currentPos, Block b) {
    
    int x = currentPos.x;
    int y = currentPos.y;
    
    switch(d){
		case Left:
            // currentPos.x - 1
            if (x > 0 && gameBoard[x - 1][y] != obstacleBlock) {
                
                //Actions to consider if its a player
                if (gameBoard[x-1][y] == foodBlock && b == player1Block) {
                    foodObtained(x-1,y);
                } else if (b == player1Block) { //Did the player run into a ghost?
                    walkIntoGhost(x-1,y);
                }
                
                //Actions to consider if its a ghost
                if (b != player1Block) {

                    //Check if he killed a player
                    if (gameBoard[x-1][y] == player1Block) {
                        hitByGhost();
                    } else { //Just walk to the new position
                        setBoardBlock(x-1, y, b);
                    }

                    //Actions to consider if its a ghost
                    if (foodLocation[x][y] == foodChar) {
                        setBoardBlock(x,y, foodBlock);
                    } else {
                        setBoardBlock(x, y, neutralGroundBlock);
                    }
                } else { //Not a ghost, therefore a player. Move normally
                    setBoardBlock(x-1, y, b);
                    setBoardBlock(x, y, neutralGroundBlock);
                }
                changedFlag[x-1][y] = '1';
                changedFlag[x][y] = '1';
                currentPos.x--;
            }
            
			break;
		case Right:
            // currentPos.x + 1
            if (x < W_BLOCKS-1 && gameBoard[x+1][y] != obstacleBlock) {
                
                //Actions to consider if its a player 
                if (gameBoard[x+1][y] == foodBlock && b == player1Block) { //Check for food
                    foodObtained(x+1,y);
                } else if (b == player1Block) { //Did the player run into a ghost?
                    walkIntoGhost(x+1,y);
                }

                //Actions to consider if its a ghost
                if (b != player1Block) {

                    //Check if he killed a player
                    if (gameBoard[x+1][y] == player1Block) {
                        hitByGhost();
                    } else { //Just walk to the new position
                        setBoardBlock(x+1, y, b);
                    }

                    if (foodLocation[x][y] == foodChar) {
                        setBoardBlock(x,y, foodBlock);
                    } else {
                        setBoardBlock(x, y, neutralGroundBlock);
                    } 
                } else { //Not a ghost, therefore a player. Move normally
                    setBoardBlock(x+1, y, b);
                    setBoardBlock(x, y, neutralGroundBlock);
                }
                changedFlag[x+1][y] = '1';
                changedFlag[x][y] = '1';            
                currentPos.x++;

            }
            
			break;
		case Up:
            // currentPos.y - 1
            if (y > 0 && gameBoard[x][y-1] != obstacleBlock) {
                
                //Actions to consider if its a player 
                if (gameBoard[x][y-1] == foodBlock && b == player1Block) { //Check for food
                    foodObtained(x,y-1);
                } else if (b == player1Block) { //Did the player run into a ghost?
                    walkIntoGhost(x,y-1);
                }

                //Actions to consider if its a ghost
                if (b != player1Block) {

                    //Check if he killed a player
                    if (gameBoard[x][y-1] == player1Block) {
                        hitByGhost();
                    } else { //Just walk to the new position
                        setBoardBlock(x+1, y, b);
                    }

                    if (foodLocation[x][y] == foodChar) {
                        setBoardBlock(x,y, foodBlock);
                    } else {
                        setBoardBlock(x, y, neutralGroundBlock);
                    }
                } else { //Not a ghost, therefore a player. Move normally
                    setBoardBlock(x, y-1 , b);
                    setBoardBlock(x, y, neutralGroundBlock);
                }
                changedFlag[x][y-1] = '1';
                changedFlag[x][y] = '1';
                currentPos.y--;
            }
            
			break;
		case Down:
            // Player1Pos.y + 1
            if (y < H_BLOCKS-1 && gameBoard[x][y+1] != obstacleBlock) {
                
                //Actions to consider if its a player 
                if (gameBoard[x][y+1] == foodBlock && b == player1Block) { //Check for food
                    foodObtained(x,y+1);
                } else if (b == player1Block) { //Did the player run into a ghost?
                    walkIntoGhost(x,y+1);
                }

                //Actions to consider if its a ghost
                if (b != player1Block) {

                    //Check if he killed a player
                    if (gameBoard[x][y+1] == player1Block) {
                        hitByGhost();
                    } else { //Just walk to the new position
                        setBoardBlock(x, y+1 , b);
                    }

                    if (foodLocation[x][y] == foodChar) {
                        setBoardBlock(x,y, foodBlock);
                    } else {
                        setBoardBlock(x, y, neutralGroundBlock);
                    }
                } else { //Not a ghost, therefore a player. Move normally
                    setBoardBlock(x, y+1 , b);
                    setBoardBlock(x, y, neutralGroundBlock);
                }
                changedFlag[x][y+1] = '1';
                changedFlag[x][y] = '1';           
                currentPos.y++;
            }
			break;      
    }

    //Update position
    if (b == player1Block) {
        player1Pos = currentPos;  
    } else if (b == ghost1Block) {
        ghost1Pos = currentPos;
    } else if (b == ghost2Block) {
        ghost2Pos = currentPos;
    } else if (b == ghost3Block) {
        ghost3Pos = currentPos;
    }

    //Check if level is cleared
    levelCleared();
    
}

//AI for the ghosts
Direction determineGhostMove(Position ghostPosition) {

    int x = ghostPosition.x;
    int y = ghostPosition.y;



}

void naive_wait(int wait){ // wait in ms
	wait = wait;
	while(wait > 0){
		int a = wait*wait;
		wait--;
	}
}

int main(){

    initScreen();
    initLedButtons();
    mainLoop();
    closeScreen();
    closeLedButtons();

    return 0;
}

//A possible version of the main function/loop
void mainLoop() {

    printf("Hello test start\n");

    fillBoard();

    //Periodically check for input and other stuff
    while (1) {
                
        //Check for input
        char driverInput = readButtons();
        
        //Determine what buttons have been pressed, and execute the action
        interpretButtonInput(driverInput);

        //Move ghosts

        //Move the ghosts
        renderBoard(TRUE);
    }
    
    
}

void interpretButtonInput(char driverInput) {


    if (driverInput == 0) return; 
    
    if((driverInput & 0x80) != 0) { //SW7 pressed
        performMove(Up, player1Pos, player1Block);
    }

    if((driverInput & 0x20) != 0) { //SW5 pressed
        performMove(Down, player1Pos, player1Block);
    }

    if((driverInput & 0x04) != 0) { //SW2 pressed
        performMove(Left, player1Pos, player1Block);
    }

    if((driverInput & 0x01) != 0) { //SW0 pressed
        performMove(Right, player1Pos, player1Block);
    }
    
}

void renderBoard(int optimize){
	
     
	for (int i = 0; i < W_BLOCKS; i++){
		for(int j = 0; j < H_BLOCKS; j++){
            if (optimize == TRUE) {
                if (changedFlag[i][j] == '1') {
                    setBlock(i,j,gameBoard[i][j]);
                }
            } else {
                setBlock(i,j,gameBoard[i][j]);
            }
		}
	}
    refreshScreen(currentFrameBuffer);
    

     
}

void setLifeBar(int lives) {

    if (lives == 1) {
        setLeds(0x80);
    } else if (lives == 2) {
        setLeds(0xC0);
    } else if (lives == 3) {
        setLeds(0xE0);
    }
}

void setBoardBlock(unsigned int x, unsigned y, Block b) {

    if (x > W_BLOCKS || y > H_BLOCKS) return;
    
    gameBoard[x][y] = b;
}

//Initial board settings
void fillBoard() {

    //Clear the board
    for (int i = 0; i < W_BLOCKS; i++)
    {
        for (int j = 0; j < H_BLOCKS; j++)
        {
            gameBoard[i][j] = neutralGroundBlock;
        }   
    }

    //Fill out obstacles
    drawBoard();
    
    //Set initial player coordinates    
    player1Pos = startingPosition;
    
    //Set player 1 position
    gameBoard[player1Pos.x][player1Pos.y] = player1Block;

    //Set player lives, if its a new game (or game over from an old game)
    if (remainingLives == 0) {
        remainingLives = startingLives;
    }
    setLifeBar(remainingLives);

    //Monsters

    //Fill food ground
    remainingFood = 0;
    int i,j;
    for (i = 0; i < W_BLOCKS; i++){
        for(j = 0; j < H_BLOCKS; j++){
            if (gameBoard[i][j] == neutralGroundBlock){
                gameBoard[i][j] = foodBlock;
                foodLocation[i][j] = foodChar;
                remainingFood++;
            }
        }
    }

    renderBoard(FALSE);
    
}

//Builds the board
void drawBoard() {

    gameBoard[0][5] = obstacleBlock;
    gameBoard[0][6] = obstacleBlock;
    gameBoard[0][7] = obstacleBlock;
    gameBoard[0][8] = obstacleBlock;
    gameBoard[0][9] = obstacleBlock;
    gameBoard[0][12] = obstacleBlock;
    gameBoard[1][1] = obstacleBlock;
    gameBoard[1][3] = obstacleBlock;
    gameBoard[1][5] = obstacleBlock;
    gameBoard[1][9] = obstacleBlock;
    gameBoard[1][12] = obstacleBlock;
    gameBoard[1][14] = obstacleBlock;
    gameBoard[2][1] = obstacleBlock;
    gameBoard[2][3] = obstacleBlock;
    gameBoard[2][5] = obstacleBlock;
    gameBoard[2][6] = obstacleBlock;
    gameBoard[2][8] = obstacleBlock;
    gameBoard[2][9] = obstacleBlock;
    gameBoard[2][14] = obstacleBlock;
    gameBoard[3][3] = obstacleBlock;
    gameBoard[3][11] = obstacleBlock;
    gameBoard[3][14] = obstacleBlock;
    gameBoard[4][1] = obstacleBlock;
    gameBoard[4][3] = obstacleBlock;
    gameBoard[4][7] = obstacleBlock;
    gameBoard[4][8] = obstacleBlock;
    gameBoard[4][9] = obstacleBlock;
    gameBoard[4][11] = obstacleBlock;
    gameBoard[4][12] = obstacleBlock;
    gameBoard[4][14] = obstacleBlock;
    gameBoard[5][1] = obstacleBlock;
    gameBoard[5][3] = obstacleBlock;
    gameBoard[5][8] = obstacleBlock;
    gameBoard[5][11] = obstacleBlock;
    gameBoard[5][12] = obstacleBlock;
    gameBoard[5][14] = obstacleBlock;
    gameBoard[6][5] = obstacleBlock;
    gameBoard[6][7] = obstacleBlock;
    gameBoard[6][8] = obstacleBlock;
    gameBoard[6][9] = obstacleBlock;
    gameBoard[6][11] = obstacleBlock;
    gameBoard[6][14] = obstacleBlock;
    gameBoard[7][3] = obstacleBlock;
    gameBoard[7][5] = obstacleBlock;
    gameBoard[7][14] = obstacleBlock;
    gameBoard[8][0] = obstacleBlock;
    gameBoard[8][1] = obstacleBlock;
    gameBoard[8][3] = obstacleBlock;
    gameBoard[8][5] = obstacleBlock;
    gameBoard[8][7] = obstacleBlock;
    gameBoard[8][8] = obstacleBlock;
    gameBoard[8][9] = obstacleBlock;
    gameBoard[8][12] = obstacleBlock;
    gameBoard[8][14] = obstacleBlock;
    gameBoard[9][3] = obstacleBlock;
    gameBoard[9][4] = obstacleBlock;
    gameBoard[9][5] = obstacleBlock;
    gameBoard[9][7] = obstacleBlock;
    gameBoard[9][9] = obstacleBlock;
    gameBoard[9][10] = obstacleBlock;
    gameBoard[9][12] = obstacleBlock;
    gameBoard[10][1] = obstacleBlock;
    gameBoard[10][2] = obstacleBlock;
    gameBoard[10][3] = obstacleBlock;
    gameBoard[10][4] = obstacleBlock;
    gameBoard[10][9] = obstacleBlock;
    gameBoard[10][10] = obstacleBlock;
    gameBoard[10][12] = obstacleBlock;
    gameBoard[10][13] = obstacleBlock;
    gameBoard[10][14] = obstacleBlock;
    gameBoard[11][1] = obstacleBlock;
    gameBoard[11][4] = obstacleBlock;
    gameBoard[11][7] = obstacleBlock;
    gameBoard[11][9] = obstacleBlock;
    gameBoard[11][10] = obstacleBlock;
    gameBoard[11][12] = obstacleBlock;
    gameBoard[12][7] = obstacleBlock;
    gameBoard[12][8] = obstacleBlock;
    gameBoard[12][9] = obstacleBlock;
    gameBoard[12][12] = obstacleBlock;
    gameBoard[12][14] = obstacleBlock;
    gameBoard[13][1] = obstacleBlock;
    gameBoard[13][3] = obstacleBlock;
    gameBoard[13][4] = obstacleBlock;
    gameBoard[13][5] = obstacleBlock;
    gameBoard[13][14] = obstacleBlock;
    gameBoard[14][0] = obstacleBlock;
    gameBoard[14][1] = obstacleBlock;
    gameBoard[14][5] = obstacleBlock;
    gameBoard[14][14] = obstacleBlock;
    gameBoard[15][1] = obstacleBlock;
    gameBoard[15][3] = obstacleBlock;
    gameBoard[15][5] = obstacleBlock;
    gameBoard[15][7] = obstacleBlock;
    gameBoard[15][8] = obstacleBlock;
    gameBoard[15][9] = obstacleBlock;
    gameBoard[15][10] = obstacleBlock;
    gameBoard[15][11] = obstacleBlock;
    gameBoard[15][12] = obstacleBlock;
    gameBoard[15][14] = obstacleBlock;
    gameBoard[16][3] = obstacleBlock;
    gameBoard[16][5] = obstacleBlock;
    gameBoard[16][14] = obstacleBlock;
    gameBoard[17][1] = obstacleBlock;
    gameBoard[17][3] = obstacleBlock;
    gameBoard[17][5] = obstacleBlock;
    gameBoard[17][10] = obstacleBlock;
    gameBoard[17][11] = obstacleBlock;
    gameBoard[17][12] = obstacleBlock;
    gameBoard[17][14] = obstacleBlock;
    gameBoard[18][1] = obstacleBlock;
    gameBoard[18][2] = obstacleBlock;
    gameBoard[18][3] = obstacleBlock;
    gameBoard[18][8] = obstacleBlock;
    gameBoard[18][10] = obstacleBlock;
    gameBoard[18][14] = obstacleBlock;
    gameBoard[19][1] = obstacleBlock;
    gameBoard[19][3] = obstacleBlock;
    gameBoard[19][5] = obstacleBlock;
    gameBoard[19][6] = obstacleBlock;
    gameBoard[19][8] = obstacleBlock;
    gameBoard[19][10] = obstacleBlock;
    gameBoard[19][12] = obstacleBlock;
    gameBoard[19][14] = obstacleBlock;
    gameBoard[20][5] = obstacleBlock;
    gameBoard[20][8] = obstacleBlock;
    gameBoard[20][12] = obstacleBlock;
}
