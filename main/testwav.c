#include "wav.h"

int main()
{
	printf("Reading a correctly formatted wav\n");
	Sound *s = loadSound("./resources/sounds/success.wav");
	for (int i = 0; i < 10; i++){
		printf("%d\n",s->samples[i]);
	}
	printf("Trying to read a incorrectly formatted wav\n");
	loadSound("./resources/sounds/fail.wav");
	return 0;
	
}
