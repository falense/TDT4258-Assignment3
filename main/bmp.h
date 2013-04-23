
#ifndef BMP_HEADER
#define BMP_HEADER

//http://en.wikipedia.org/wiki/BMP_file_format

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

#include "./libs/qdbmp.h"

typedef struct {
	unsigned char red;
	unsigned char green;
	unsigned char blue;

}Color;

typedef struct {
	int width;
	int height;
	BMP* bmp;
}Bitmap;

Bitmap* loadBitmap(char * filename);
void finalizeBitmap(Bitmap * image);
Color* getPixel(int x, int y, Bitmap * image);

#endif
