//http://servv89pn0aj.sn.sourcedns.com/~gbpprorg/guerrilla.net/reference/dsp/prog_dsp.htm

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>


#include "ledbuttons.h"


int main(){
	initLedButtons();
	while(1){
		for (int i = 0; i < 100; i++){
			setLeds((char)i);
			if (readButtons() & 0x01 > 0) break;
		}
	}
	closeLedButtons();
}
