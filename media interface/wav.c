//http://en.wikipedia.org/wiki/BMP_file_format

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <linux/soundcard.h>
#include <sndfile.h>


#include "sound.h"
struct Sound{
	int length;
	int *samples;
};
typedef struct Sound Sound;

Sound* loadSound(char * filename){

	soundFileID = open(filename,O_RDONLY);

	if(soundFileID < 0)
	{
		printf("Didnt manage to open screen block device.");
		return NULL;
	}
	Sound * image = (Sound*)malloc(sizeof(Sound));
	
	lseek(bitmapFileID, 10, SEEK_SET);
	ssize_t bytesread = write(soundFileID, (void*)image.pixelArrayOffset,4);
	printf("%d",image.fileSize);
	
	close(soundFileID);
}


int main(){
	Sound t;

    int slen;
    int i;
    int result;
    int NUM_SKIP = 40;
    char *sample;
    char tempfile[175];
    FILE *wav;
    FILE *outwav;
    
    
    snprintf(tempfile, 175, "temp&#37;s", file);
    wav = fopen(tempfile, "rb");
    
    fseek(wav, 0, SEEK_END);
    slen = ftell(wav);
    rewind(wav);
    
    sample = (char*) malloc (sizeof(char)*slen);
    if(sample == NULL)
    {
        fputs("Memory error", stderr);
        exit(1);
    }
    
    result = fread(sample, 1, slen, wav);
    if(result != slen)
    {
        fputs("Read error",stderr);
        exit(2);
    }
    
    fclose(wav);
    char nsample[slen-NUM_SKIP];
    for(i = slen-1; i >NUM_SKIP; i--)
    {
        nsample[i-NUM_SKIP] = sample[i];
        //Some other stuff happens in here too, but it's irrelevant to gettting this all to work.
        printf("nsample: %c", nsample[i]);
        printf(" sample: %c\n", sample[i]);
    }

    
    return 0;
	
}