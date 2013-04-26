
#include "game.h"
#include <stdio.h>
#include <stdlib.h> 
#include <math.h>

/* MAIN FUNCTION */
 
int main() {
    
    //Component Initialization
    initScreen();
    initSound();
    initLedButtons();
    
    //Perform initial setup of board
    fillBoard();
    
    //The main loop
    mainLoop();
    
    //Component finalizing
    closeScreen();
    closeSound();
    closeLedButtons();
    
    return 0;
}

/* MAIN LOOP */

void mainLoop() {
    
    while (1) {
        
        //Check for input
        char driverInput = readButtons();
        
        //Determine what buttons have been pressed, and execute the action
        interpretButtonInput(driverInput);
        
        //Feed the music buffer to keep the music going
        feedBuffer();
        
        //Move the ghosts
        if (timeStep > 50){
            ghostsMoveTurn();
        }
        
        timeStep += 1;
        
        //Render the board, but only update what needs to be updated
        renderBoard(TRUE);
    }
    
    
}

/* GAME END METHODS */

//Check if the level is cleared
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


//Display a static win screen for about 2 seconds when you lose
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

//Display a static win screen for about 2 seconds when you win
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

/* HIT DETECTION METHODS */
//Checks if the player/ghosts has hit another player, a ghost or food (player only) 

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

//Check if the player has walked into a ghost
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

//Check if the player has walked onto a food block and obtained food
void foodObtained(int x, int y) {
    score+=FOOD_SCORE;
    remainingFood--;
    foodLocation[x][y] = '0';
}

/* RENDER METHODS */

//performs a call to the screen framework, to change the screen.
//It can either be done optimized or unoptimized.
//Optimized: Only changes blocks that have been changed based on the changedFlag array
//Unoptimized: Draw every block
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

//These functions set some global variable
/* SETTER/GETTER FUNCTIONS */

void setBoardBlock(unsigned int x, unsigned y, Block b) {
    
    if (x > W_BLOCKS || y > H_BLOCKS) return;
    
    gameBoard[x][y] = b;
    
    setFlagForRender(x,y);
}

void setLifeBar(int lives) {
    char r = 0;
    for (int i = 0; i < lives;i++){
        
        r = r >> 1;
        r = r | 0x80;
        
    }
    setLeds(r);
}

void setFlagForRender(int x, int y) {
    changedFlag[x][y] = '1';
}

unsigned char * getWalkCount(int x, int y, Block b) {
    
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

Position getMonsterPosition(Block b) {
    
    switch(b){
            
        case Ghost1:
            return ghost1Pos;
        case Ghost2:
            return ghost2Pos;
        case Ghost3:
            return ghost3Pos;
    }
}

/* HELPER METHODS */

int naive_wait(int wait) { // wait in ms
	wait = wait;
    int r = 0;
	while(wait > 0){
		int a = wait*wait;
		wait--;
        r += a;
	}
    return r;
}

//Used by the AI
int distanceToPlayer(Position pos) {
    
    int diffX = pos.x - player1Pos.x;
    int diffY = pos.y - player1Pos.y;
    return diffY*diffY+diffX*diffX;
}


/* MOVEMENT METHODS */

//A high-level method called by the main loop to make the ghosts move
void ghostsMoveTurn() {
    
    Direction ghost1Move = determineGhostMove(ghost1Pos, ghost1Block);
    moveGhost(ghost1Move, ghost1Pos, ghost1Block);
    
    Direction ghost2Move = determineGhostMove(ghost2Pos, ghost2Block);
    moveGhost(ghost2Move, ghost2Pos, ghost2Block);
    
    Direction ghost3Move = determineGhostMove(ghost3Pos, ghost3Block);
    moveGhost(ghost3Move, ghost3Pos, ghost3Block);
}

//Makes a single ghost perform a move
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

//Determines which direction the ghost should move.
//It will first find any directions it can move in, before tries to find a best move
//The best move i calculated by combining the distance to player and
//by checking the ghostXWalkCount array to see if ghost has been in the location before.
//this is to prevent the ghost from getting stuck in one location.
Direction determineGhostMove(Position ghostPosition, Block ghost) {
    
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
    
    return bestMove;
    
}

//Helper function used byt the determineGhostMove function.
//It checks if the x,y block is walkable for a ghost
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

//determines what moves the ghost can make, based on input from walkable
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
    
    return r;
    
}

//Find a direction to move based on the player input
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

//Used to perform the actual move, after determining the direction for
//either the ghosts or the player
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

//These functions perform initialization of various game logic
/* GAME INITIALIZATION FUNCTIONS*/

//Initial board settings
void fillBoard() {
    
    //Choose sound to play
    backgroundSoundFile("./resources/sounds/IAmNobody.dat");
    
    //Clear the board and clear ghost walk count used by the AI
    for (int i = 0; i < W_BLOCKS; i++)
    {
        for (int j = 0; j < H_BLOCKS; j++)
        {
            gameBoard[i][j] = neutralGroundBlock;
            ghost1WalkCount[i][j] = 0;
            ghost2WalkCount[i][j] = 0;
            ghost3WalkCount[i][j] = 0;
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
    
    //Set the monsters position
    ghost1Pos = ghost1StartPosition;
    ghost2Pos = ghost2StartPosition;
    ghost3Pos = ghost3StartPosition;
    
    //Set the ghost sprites on the board
    gameBoard[ghost1Pos.x][ghost2Pos.y] = ghost1Block;
    gameBoard[ghost2Pos.x][ghost2Pos.y] = ghost2Block;
    gameBoard[ghost3Pos.x][ghost3Pos.y] = ghost3Block;
    
    //Variable used to give the player a head start
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
        }
    }
    
    
    //The game requires only, remainingFood amounts of food, depending on the
    //difficulty variable
    remainingFood = remainingFood/difficulty;
    
    //Render the board once, without optimization.
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
