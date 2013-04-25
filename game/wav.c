

#include "wav.h"


Sound* loadSound(char * filename){
	printf("Filename:");
	printf(filename);
	Sound *s = (Sound*)malloc(sizeof(Sound));

	int fd = open(filename,O_RDONLY);
	if(fd < 0){
		printf("Didnt manage to load sound file:");
		printf(filename);
		printf("\n");
		return NULL;

	}

	read(fd,&s->length,4);
	
	//if (s->length > 240000) s->length = 240000;

	printf("\nSample count: %u\n",s->length);
	s->samples = (char*)malloc(sizeof(char)*s->length);
	read(fd,s->samples,sizeof(char)*s->length);
	close(fd);

	return s;
}

void finalizeSound(Sound * s){

	free(s->samples);
	free(s);
}
