//http://en.wikipedia.org/wiki/WAV
//http://www.daniweb.com/software-development/c/threads/340334/reading-audio-file-in-c
//https://ccrma.stanford.edu/courses/422/projects/WaveFormat/

#ifndef WAV_HEADER
#define WAV_HEADER

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <err.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/ioctl.h>



typedef struct{
	uint32_t length;
	char *samples;
} Sound;

void wavread(char *file_name,Sound * s);


Sound* loadSound(char * filename);
void finalizeSound(Sound* s);

#endif

