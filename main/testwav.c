#include "wav.h"
#include <limits.h>

int main()
{
	//printf("Trying to read a incorrectly formatted wav\n");
	//loadSound("./resources/sounds/fail.wav");
	printf("Reading a correctly formatted wav\n");
	Sound *s = loadSound("./resources/sounds/out.dat");
	for (int i = 0; i < 100; i++){
		printf("%d\n",s->samples[i]);
	}
	return 0;
	
}
