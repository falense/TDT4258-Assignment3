


struct Color{
	char red;
	char green;
	char blue;

};
typedef struct Color Color ;


enum Block {White, Black, Blue, Red, Green};
typedef enum Block Block;

int screenDeviceID = -1;

#define SCREENHEIGHT 240
#define SCREENWIDTH 320

#define H_BLOCKS 10
#define W_BLOCKS 10

const unsigned int BLOCK_WIDTH = SCREENWIDTH/H_BLOCKS;
const unsigned int BLOCK_HEIGHT = SCREENHEIGHT/W_BLOCKS;


#define DEBUG 1


void initScreen();
void closeScreen();
void writeScreen(char* data, unsigned int start, unsigned int size);
void setPixel(unsigned int x, unsigned int y, Color c);
void setBlock(unsigned int bx,unsigned int by, Block b);


void clearScreen(Color c);
void clearScreen();

char* blockToData(Block b);