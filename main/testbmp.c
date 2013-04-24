#include "bmp.h"

int main(){
	Bitmap * image = loadBitmap("./resources/images/test.bmp");

	Color c = getPixel(0,0,image);
	printf("Red: %d\n",(int)c.red);
	printf("Green: %d\n",(int)c.green);
	printf("Blue: %d\n",(int)c.blue);
	finalizeBitmap(image);
	return 0;
	
}
