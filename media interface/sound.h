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

extern int soundDeviceID;

void initSound();
void closeSound();

void writeSoundValue(char *buffer, unsigned int length);

#endif
