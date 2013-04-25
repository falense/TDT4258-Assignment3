
#include "bmp.h"

Bitmap* loadBitmap(char * filename){

	Bitmap * r = (Bitmap*)malloc(sizeof(Bitmap));
	r->bmp  = BMP_ReadFile( filename );
	BMP_CHECK_ERROR( stdout, -1 );

	r->width = BMP_GetWidth(r->bmp);
	r->height = BMP_GetHeight(r->bmp);
	return r;
}


void finalizeBitmap(Bitmap * image){
	BMP_Free( image->bmp );
	free(image);
}

Color getPixel(unsigned int x,unsigned int y, Bitmap * image){
	Color  c = {.red = 0, .green = 0, .blue = 0};

	if (x >= image->width || y >= image->height) return c;

	BMP_GetPixelRGB( image->bmp, x, y, &c.red, &c.green, &c.blue );
	//printf("%d,%d \n",x,y);
	//printf("%d,%d,%d \n",c.red,c.green,c.blue);
	return c;
}
