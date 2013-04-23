

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
