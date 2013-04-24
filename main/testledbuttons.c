

#include "ledbuttons.h"


int main(){
	initLedButtons();
	char buttonState;
	while(1){
		char t = readButtons();
		if (t != buttonState){
			buttonState =t;
			setLeds(buttonState);
		}
	}
	closeLedButtons();
}
