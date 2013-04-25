//http://servv89pn0aj.sn.sourcedns.com/~gbpprorg/guerrilla.net/reference/dsp/prog_dsp.htm

#ifndef SOUND_HEADER
#define SOUND_HEADER


#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <linux/soundcard.h>
#include <sys/ioctl.h>

#include "wav.h"

extern int soundDeviceID;

typedef struct {
	Sound * ss;
	uint32_t current;
} SoundPlaying;

#define MAXSOUNDCOUNT 1
extern SoundPlaying *channels;


void initSound();
void closeSound();

void writeSoundValue(char *buffer, unsigned int length);


#define DSP_SAMPLERATE 8000

#define SOUNDBURSTWRITE 1000
//(DSP_SAMPLERATE /8)

void playSounds();
void playSoundFile(char*filename);
void backgroundSoundFile(char*filename);
void setFrequency(double hertz);
void feedBuffer();
#endif

