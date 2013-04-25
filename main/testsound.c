//http://servv89pn0aj.sn.sourcedns.com/~gbpprorg/guerrilla.net/reference/dsp/prog_dsp.htm

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <linux/soundcard.h>


#include "sound.h"


int main(){
	initSound();
	printf("test\n");
	playSoundFile("./resources/sounds/bumpisong.dat");
	printf("test\n");
	
	for (int i = 0; i < 10; i++){
		feedBuffer();
	}
	printf("test\n");
	playSoundFile("./resources/sounds/bumpisong.dat");
	printf("test\n");
	for (int i = 0; i < 1000; i++){
		feedBuffer();
	}
	printf("test\n");
	closeSound();

}
