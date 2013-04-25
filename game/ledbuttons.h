//http://servv89pn0aj.sn.sourcedns.com/~gbpprorg/guerrilla.net/reference/dsp/prog_dsp.htm

#ifndef LEDBUTTONS_HEADER
#define LEDBUTTONS_HEADER


#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>


extern int ledButtonsDeviceID;

void initLedButtons();
void closeLedButtons();
void setLeds(char leds);
char readButtons();
#endif
