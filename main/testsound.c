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
	while(1){
		/*for (int i = 0; i < 100; i++){
			setFrequency(120*(i%20));
			for (int x = 0; x < 300000; x++){
				int c = x*x;
			}
		}*/
		playSoundFile("./resources/sounds/bumpisong.dat");
	}
	closeSound();

}