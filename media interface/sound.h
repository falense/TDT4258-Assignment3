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


extern int soundDeviceID;

void initSound();
void closeSound();

void writeSoundValue(char *buffer, unsigned int length);


#define DSP_SAMPLERATE 16000

#define SOUNDBURSTWRITE DSP_SAMPLERATE /8

void playSounds();
void setFrequency(double hertz);
#endif