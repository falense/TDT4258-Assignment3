

#include "wav.h"


Sound* loadSound(char * filename){
	printf("Filename:");
	printf(filename);
	Sound *s = (Sound*)malloc(sizeof(Sound));

	int fd = open(filename,O_RDONLY);
	printf("\nSample count: %u\n",s->length);
	read(fd,s,4);
	printf("\nSample count: %d\n",(int)s->length);
	
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
