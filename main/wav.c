

#include "wav.h"


void wavread(char *filename,Sound * s)
{
	printf("Reading: ");
	printf(filename);
	printf("\n");
	int fd;
	WavHeader *header;
	if (!filename) 
		errx(1, "Filename not specified");
	if ((fd = open(filename, O_RDONLY)) < 1) 
		errx(1, "Error opening file");
	lseek(fd,0,SEEK_SET);
	if (!header) 
		header = (WavHeader*)malloc(sizeof(WavHeader));	
	if (read(fd, header, sizeof(WavHeader)) < sizeof(WavHeader)) 
		errx(1, "File broken: header");
	for (int i = 0; i < 42; i++)
		printf("%c ",((char*)header)[i]);
	printf("\n");
	if (strncmp(header->chunk_id, "RIFF", 4) || strncmp(header->format, "WAVE", 4)) 
		errx(1, "Not a wav file");
	printf("Audio format: %d\n",header->audio_format);
	if (header->audio_format != 1) 
		errx(1, "Only PCM encoding supported");

	s->samples = (int16_t*)malloc(sizeof(int16_t)*header->datachunk_size);
	s->length = header->datachunk_size;
	if (!s->samples) 
		errx(1, "Error allocating memory");

	if (read(fd, s->samples, header->datachunk_size) < header->datachunk_size) 
		errx(1, "File broken: samples");
	if (strncmp(header->datachunk_id, "data", 4)) errx(1, "Cannot read this type of wav file");
/*
	for (int i = 0; i < 4; i++)
		printf("%c\t",header->datachunk_id[i]);
	printf("\n");

	printf("No. of channels: %d\n",     header->num_channels);
	printf("Sample rate:     %d\n",     header->sample_rate);
	printf("Bit rate:        %dkbps\n", header->byte_rate*8 / 1000);
	printf("Bits per sample: %d\n",     header->bps);
	printf("Sample count:    %d\n", header->datachunk_size);

	uint32_t i;
	for (i = 0; i < header->datachunk_size; i++){
	printf("Sample %d:        %d\n", i,s->samples[i]);
	}
*/
	free(header);
	close(fd);
}


Sound* loadSound(char * filename){
	Sound *t = (Sound*)malloc(sizeof(Sound));
	wavread(filename,t);
	return t;
}

void finalizeSound(Sound * s){

	free(s->samples);
	free(s);
}
