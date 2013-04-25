
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
    foodLocation[x][y] = '0';
}

void flagForRender(int x, int y) {

    changedFlag[x][y] = '1';
}
void displayLose(){
    printf("Displaying lose screen\n");
    Bitmap * b = loadBitmap("./resources/images/lose.bmp");
    int x,y;
    for (x = 0; x < b->width; x++){
        for(y = 0; y < b->height; y++){
            Color c = getPixel(x,y,b);
            setPixel(x,y,c);
        }
    }
    refreshScreen(currentFrameBuffer);
    finalizeBitmap(b);
}
void displayWin(){

    Bitmap * b = loadBitmap("./resources/images/victory.bmp");
    int x,y;
    for (x = 0; x < b->width; x++){
        for(y = 0; y < b->height; y++){
            Color c = getPixel(x,y,b);
            setPixel(x,y,c);
        }
    }
    refreshScreen(currentFrameBuffer);
    finalizeBitmap(b);
}

void hitByGhost() {

    remainingLives--;

    if (remainingLives == 0) { //Player Game Over, print score and reset board
        printf("Game Over! Total Score: %d\n", score);
        score = 0;
        displayLose();
        naive_wait(50000000);
        fillBoard();
    } else {

        //Adjust lifebar
        setLifeBar(remainingLives);

        //Set starting location
        //setBoardBlock(player1Pos.x, player1Pos.y, neutralGroundBlock);
        setBoardBlock(startingPosition.x, startingPosition.y, player1Block);

        //Return to start
        player1Pos = startingPosition;

    }

    
}

int distanceToPlayer(Position pos) {

    int diffX = pos.x - player1Pos.x;
    int diffY = pos.y - player1Pos.y;
    return diffY*diffY+diffX*diffX;
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

        displayWin();
        naive_wait(50000000);
        fillBoard();
    }
}

int walkIntoGhost(int x, int y) {

    if (gameBoard[x][y] == ghost1Block) {
        hitByGhost();
        return 1;
    } else if (gameBoard[x][y] == ghost2Block) {
        hitByGhost();
        return 1;
    } else if (gameBoard[x][y] == ghost3Block) {
        hitByGhost();
        return 1;
    }

    return 0;
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
                    if (walkIntoGhost(x-1,y)) return;
                }
                
                //Actions to consider if its a ghost
                if (b != player1Block) {

                    //Check if he killed a player
                    if (gameBoard[x-1][y] == player1Block) {
                        hitByGhost();
                    } else { //Just walk to the new position
                        setBoardBlock(x-1, y, b);
                    }

                    //Check if he was standing on food
                    if (foodLocation[x][y] == foodChar) {
                        setBoardBlock(x,y, foodBlock);
                    } else {
                        setBoardBlock(x, y, neutralGroundBlock);
                    }
                } else { //Not a ghost, therefore a player. Move normally
                    setBoardBlock(x-1, y, b);
                    setBoardBlock(x, y, neutralGroundBlock);
                }
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
                    if (walkIntoGhost(x+1,y)) return;
                }

                //Actions to consider if its a ghost
                if (b != player1Block) {

                    //Check if he killed a player
                    if (gameBoard[x+1][y] == player1Block) {
                        hitByGhost();
                    } else { //Just walk to the new position
                        setBoardBlock(x+1, y, b);
                    }

                    //Check if he was standing on food
                    if (foodLocation[x][y] == foodChar) {
                        setBoardBlock(x,y, foodBlock);
                    } else {
                        setBoardBlock(x, y, neutralGroundBlock);
                    } 
                } else { //Not a ghost, therefore a player. Move normally
                    setBoardBlock(x+1, y, b);
                    setBoardBlock(x, y, neutralGroundBlock);
                }

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
                    if (walkIntoGhost(x,y-1)) return;
                }

                //Actions to consider if its a ghost
                if (b != player1Block) {

                    //Check if he killed a player
                    if (gameBoard[x][y-1] == player1Block) {
                        hitByGhost();
                    } else { //Just walk to the new position
                        setBoardBlock(x, y-1, b);
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
                    if (walkIntoGhost(x,y+1)) return;
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

short walkable(int x, int y) {
    if(x < 0 || x > W_BLOCKS-1 || y < 0 || y > H_BLOCKS-1) return 0;

    Block b = gameBoard[x][y];

    switch(b) {
        case Ground:
            return 1;
        case Food:
            return 1;
        case Pacman:
            return 1;
        case Rock:
            return 0;
        case Ghost1:
            return 0;
        case Ghost2:
            return 0;
        case Ghost3:
            return 0;
        default:
            return 0;
    }
}

char possibleMoves(int x, int y) {

    char r = (char) 0;

    if (walkable(x-1, y)) { //Walk left
        r = r | 0x01;
    }
    if (walkable(x+1, y)) { //Walk right
        r = r | 0x02;
    }
    if (walkable(x, y-1)) { //Walk Up
        r = r | 0x04;
    }
    if (walkable(x, y+1)) { //Walk Down
        r = r | 0x08;
    } 

    //printf("%x\n", r);

    return r;

}

unsigned char * getWalkCount(int x, int y, Block b){

    switch(b){

        case Ghost1:
            return &ghost1WalkCount[x][y];
        case Ghost2:
            return &ghost2WalkCount[x][y];
        case Ghost3:
            return &ghost3WalkCount[x][y];

    }
    return NULL;
}
Position getMonsterPosition(Block b){

    switch(b){

    case Ghost1:
        return ghost1Pos;
    case Ghost2:
        return ghost2Pos;
    case Ghost3:
        return ghost3Pos;
    }
}
//AI for the ghosts
Direction determineGhostMove(Position ghostPosition, Block ghost) {
/*
    switch(ghost){
        case Ghost1:
            printf("Ghost1 AI:\n");
            break;
        case Ghost2:
            printf("Ghost2 AI:\n");
            break;
        case Ghost3:
            printf("Ghost3 AI:\n");
            break;
    }
*/
    int x = ghostPosition.x;
    int y = ghostPosition.y;

    char r = possibleMoves(x,y);
    int bestMoveDistance = 0;
    int bestMoveBeenHere = 0;
    Direction bestMove = NoMove;
    if ((r & 0x01) > 0) {
        Position p = {.x = x-1, .y = y};
        int distance = distanceToPlayer(p);
        int beenHere = *getWalkCount(x-1, y, ghost);

        if (bestMove == NoMove || bestMoveBeenHere > beenHere || ( bestMoveBeenHere == beenHere && distance < bestMoveDistance)){
            bestMove = Left;
            bestMoveDistance = distance;
            bestMoveBeenHere = beenHere;
        }

    }

    if ((r & 0x02) > 0) {
        Position p = {.x = x+1, .y = y};
        int distance = distanceToPlayer(p);
        int beenHere = *getWalkCount(x+1, y, ghost);
        if (bestMove == NoMove || bestMoveBeenHere > beenHere || ( bestMoveBeenHere == beenHere && distance < bestMoveDistance)){
            bestMove = Right;
            bestMoveDistance = distance;
            bestMoveBeenHere = beenHere;
        }

    }

    if ((r & 0x04) > 0) {
        Position p = {.x = x, .y = y-1};
        int distance = distanceToPlayer(p);
        int beenHere = *getWalkCount(x, y-1, ghost);
        if (bestMove == NoMove || bestMoveBeenHere > beenHere || ( bestMoveBeenHere == beenHere && distance < bestMoveDistance)){
            bestMove = Up;
            bestMoveDistance = distance;
            bestMoveBeenHere = beenHere;
        }

    }

    if ((r & 0x08) > 0) {
        Position p = {.x = x, .y = y+1};
        int distance = distanceToPlayer(p);
        int beenHere = *getWalkCount(x, y+1, ghost);
        if (bestMove == NoMove || bestMoveBeenHere > beenHere || ( bestMoveBeenHere == beenHere && distance < bestMoveDistance)){
            bestMove = Down;
            bestMoveDistance = distance;
            bestMoveBeenHere = beenHere;
        }

    }
    /*
    printf("\t Possible moves: %x\n",r);
    if ((r & 0x01) > 0) printf("\t Can go left\n");
    if ((r & 0x02) > 0) printf("\t Can go right\n");
    if ((r & 0x04) > 0) printf("\t Can go up\n");
    if ((r & 0x08) > 0) printf("\t Can go down\n");
    printf("\t BestMove: %x\n", bestMove);

    if (bestMove == Left) printf("\t Going left\n");
    if (bestMove == Right) printf("\t Going right\n");
    if (bestMove == Up) printf("\t Going up\n");
    if (bestMove == Down) printf("\t Going down\n");
    printf("\t BestDistance: %d\n", bestMoveDistance);
    printf("\t BestMoveBeenHere: %d\n", bestMoveBeenHere);*/
    return bestMove;


}

int naive_wait(int wait){ // wait in ms
	wait = wait;
    int r = 0;
	while(wait > 0){
		int a = wait*wait;
		wait--;
        r += a;
	}
    return r;
}

int main(){

    //printf("START\n");

    initScreen();
    initSound();
    initLedButtons();
    mainLoop();
    closeScreen();
    closeSound();
    closeLedButtons();

    return 0;
}
void moveGhost(Direction d, Position p, Block b) {

    if (d == NoMove) {
        unsigned char * count = getWalkCount(p.x,p.y,b);
        (*count)++;
    }   
    else{
        performMove(d, p, b);
        Position t = getMonsterPosition(b);
        unsigned char * count = getWalkCount(t.x,t.y,b);
        (*count)++;

    }

 }

//A possible version of the main function/loop
void mainLoop() {

    fillBoard();
    
       

    //Periodically check for input and other stuff
    while (1) {
                
        //Check for input
        char driverInput = readButtons();
        
        //Determine what buttons have been pressed, and execute the action
        interpretButtonInput(driverInput);
        feedBuffer();
        //Move ghosts

        if (timeStep > 50){
            Direction ghost1Move = determineGhostMove(ghost1Pos, ghost1Block);
            moveGhost(ghost1Move, ghost1Pos, ghost1Block);

            Direction ghost2Move = determineGhostMove(ghost2Pos, ghost2Block);
            moveGhost(ghost2Move, ghost2Pos, ghost2Block);

            Direction ghost3Move = determineGhostMove(ghost3Pos, ghost3Block);
            moveGhost(ghost3Move, ghost3Pos, ghost3Block);
        }
        timeStep += 1;

        //Move the ghosts

        renderBoard(TRUE);     
        //naive_wait(4009000);
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
    char r = 0;
    for (int i = 0; i < lives;i++){

        r = r >> 1;
        r = r | 0x80;

    }
    setLeds(r);
    return;
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

    flagForRender(x,y);
}

//Initial board settings
void fillBoard() {

    backgroundSoundFile("./resources/sounds/IAmNobody.dat");
    
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
    remainingLives = startingLives;
    setLifeBar(remainingLives);

    //Monsters
    ghost1Pos = ghost1StartPosition;
    ghost2Pos = ghost2StartPosition;
    ghost3Pos = ghost3StartPosition;

    gameBoard[ghost1Pos.x][ghost2Pos.y] = ghost1Block;
    gameBoard[ghost2Pos.x][ghost2Pos.y] = ghost2Block;
    gameBoard[ghost3Pos.x][ghost3Pos.y] = ghost3Block;

    timeStep = 0;

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
            ghost1WalkCount[i][j] = 0;
            ghost2WalkCount[i][j] = 0;
            ghost3WalkCount[i][j] = 0;
        }
    }
    remainingFood = remainingFood/2;

    
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
