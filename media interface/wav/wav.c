//http://en.wikipedia.org/wiki/WAV
//http://www.daniweb.com/software-development/c/threads/340334/reading-audio-file-in-c
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <err.h>
//#include "wavlib.h"

typedef struct {
    char     chunk_id[4]; //4
    uint32_t chunk_size; //8
    char     format[4]; //12

    char     fmtchunk_id[4]; //16
    uint32_t fmtchunk_size; //20
    uint16_t audio_format; //22
    uint16_t num_channels; //24
    uint32_t sample_rate; //28
    uint32_t byte_rate; //32
    uint16_t block_align; //34
    uint16_t bps;	//36

    char     datachunk_id[4]; //40
    uint32_t datachunk_size; //44
}WavHeader;


typedef struct{
	int length;
	int16_t *samples;
} Sound;

void wavread(char *file_name)
{
    int fd;

WavHeader *header;
    if (!file_name)
        errx(1, "Filename not specified");

    if ((fd = open(file_name, O_RDONLY)) < 1)
        errx(1, "Error opening file");

    if (!header)
        header = (WavHeader*)malloc(sizeof(WavHeader));

    if (read(fd, header, sizeof(WavHeader)) < sizeof(WavHeader))
        errx(1, "File broken: header");
	/*read(fd, header->chunk_id, 4);
	read(fd, &header->chunk_size, 4);
	read(fd, header->fmtchunk_id, 4);
	read(fd, &header->fmtchunk_size, 4);
	read(fd, &header->audio_format, 2);
	read(fd, &header->num_channels, 2);
	read(fd, &header->sample_rate, 4);
	read(fd, &header->byte_rate, 4);
	read(fd, &header->block_align, 2);
	read(fd, &header->bps, 2);
	read(fd, header->datachunk_id, 4);
	read(fd, &header->datachunk_size, 4);*/



    if (strncmp(header->chunk_id, "RIFF", 4) ||
        strncmp(header->format, "WAVE", 4))
        errx(1, "Not a wav file");

    if (header->audio_format != 1)
        errx(1, "Only PCM encoding supported");


    int16_t *samples = (int16_t*)malloc(header->datachunk_size);
 //   if (!samples)
   //     errx(1, "Error allocating memory");
   // if (read(fd, samples, header->datachunk_size) < header->datachunk_size)
   //     errx(1, "File broken: samples");

for (int i = 0; i < 4; i++)
printf("%c\t",header->format[i]);
/*
    printf("No. of channels: %d\n",     header->num_channels);
    printf("Sample rate:     %d\n",     header->sample_rate);
    printf("Bit rate:        %dkbps\n", header->byte_rate*8 / 1000);
    printf("Bits per sample: %d\n\n",     header->bps);*/
/*
    printf("Sample 0:        %d\n", samples[0]);
    printf("Sample 1:        %d\n", samples[1]);
    printf("Sample count:    %d\n", header->datachunk_size);
*/
//uint32_t i;
//	for (i = 0; i < header->datachunk_size; i++){

  //  printf("Sample %d:        %d\n", i,(*samples)[i]);
//	}
   // close(fd);
}


Sound* loadSound(char * filename){
	Sound *t;
	t = (Sound*)malloc(sizeof(Sound));
	int16_t * samples = NULL;
	wavread(filename);
	//t->length = 0;
	return NULL;
}

int main()
{
wavread("./mytest.wav");
	//for (int i = 0; i < s->length; i++){
	//	printf("%d",s->samples[i]);
	//}
return 0;
	
}
