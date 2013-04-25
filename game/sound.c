int soundDeviceID = -1;
#include "sound.h"
SoundPlaying *channels;
void initSound(){
	soundDeviceID = open("/dev/dsp",O_WRONLY );

	if(soundDeviceID < 0)
	{
		printf("Didnt manage to open sound device.");
		exit(0);
	}

	channels = (SoundPlaying*)malloc(sizeof(SoundPlaying)*MAXSOUNDCOUNT);
	for(int i = 0; i < MAXSOUNDCOUNT;i++){
		channels[i].ss = NULL;
		channels[i].current = 0;
	}
}
void closeSound(){
	close(soundDeviceID);
}
void writeSoundValue(char *buffer, unsigned int length){
	ssize_t written = write(soundDeviceID, buffer,length);
	if(written > 0);
	else if(errno == EWOULDBLOCK)
		printf("Error writing");
	else printf("Error writing");
}
int soundState = 0;
int samplesPerPeriod = 150;


/* Wave sample generating functions 
Each of these functions can be used with the sounds created. 
In our humble opinion square waves sound best while pyramidWave and sinWave each have their respective quirks*/

/*Simples square wave function, either its on or its off. 
This is defined via what tone is currently playing on the channel we are generating for and what state we currently are at.
State is a constantly incrementing value for each interrupt. This makes the function below able to determine where it should be in its waveform */
short squareWave(){
	if (soundState%samplesPerPeriod < samplesPerPeriod/2)
		return 100;
	else return -100;
}

/*Pyramid wave function.  This is defined via what tone is currently playing on the channel we are generating for and what state we currently are at. 
State is a constantly incrementing value for each interrupt. This makes the function below able to determine where it should be in its waveform */
short pyramidWave(){
	int period = soundState%samplesPerPeriod;
	if (period < samplesPerPeriod/4){
		return (period*100/(samplesPerPeriod/4));
	}
	else if(period < samplesPerPeriod/2){
		return (100-(period-samplesPerPeriod/4)*200/(samplesPerPeriod/2));
	}
	else {
		return -100+((period-((samplesPerPeriod*3)/4))*100/(samplesPerPeriod/4));
	}
}
/*
short sinTable[] = {0, 6, 12, 18, 24, 30, 36, 42, 48, 53, 58, 63, 68, 72, 77, 80, 84, 87, 90, 92, 95, 96, 98, 99, 99, 99, 99, 99, 98, 96, 95, 93, 90, 87, 84, 80, 77, 72, 68, 63, 58, 53, 48, 42, 36, 31, 25, 18, 12, 6, 0, -6, -12, -18, -24, -30, -36, -42, -48, -53, -58, -63, -68, -72, -76, -80, -84, -87, -90, -92, -95, -96, -98, -99, -99, -99, -99, -99, -98, -96, -95, -93, -90, -87, -84, -81, -77, -73, -68, -63, -59, -53, -48, -42, -37, -31, -25, -19, -12, -6};

Simple sinus aproximation with a lookup table.  
This is defined via what tone is currently playing on the channel we are generating for and what state we currently are at. 
State is a constantly incrementing value for each interrupt. This makes the function below able to determine where it should be in its waveform 
short sinWave(){
	int period = soundState%samplesPerPeriod;
	short index = (period*100)/samplesPerPeriod;
	return sinTable[index%100];

}
*/
short waveFunction(){
	soundState++;
	return (unsigned int)squareWave();
}


//Sets the frequency the abdac should play
void setFrequency(double hertz){
	//If the hertz given is over 1 we assume we want to play an actual sound
	if (hertz > 1.0){
		samplesPerPeriod = DSP_SAMPLERATE /hertz;
	}
}


void playSounds(){

	char data[SOUNDBURSTWRITE+1];
	for (int i = 0; i < SOUNDBURSTWRITE; i++)
		data[i] = waveFunction();	
	writeSoundValue((char*)&data,SOUNDBURSTWRITE);
}

short getActiveChannels(){

	short activeChannels = 0;
	for (int i = 0; i < MAXSOUNDCOUNT; i++){
		if(channels[i].ss != NULL){
			activeChannels++;
		}
	}
	return  activeChannels;
}
void backgroundSoundFile(char* filename){
	if (getActiveChannels() == 0){
		Sound *t = loadSound(filename);
		
		for (int i = 0; i < MAXSOUNDCOUNT; i++){
			if(channels[i].ss == NULL){
				channels[i].ss = t;
				channels[i].current = 0;
				break;
			}
		}
	}

}
void playSoundFile(char*filename){

	Sound *t = loadSound(filename);
	
	for (int i = 0; i < MAXSOUNDCOUNT; i++){
		if(channels[i].ss == NULL){
			channels[i].ss = t;
			channels[i].current = 0;
			printf("Sound started:");
			printf(filename);
			printf("\n");
			break;
		}
	}
}
void feedBuffer(){
	char * buffer = (char*)malloc(sizeof(char)*SOUNDBURSTWRITE);
	if(!buffer){
		printf("Error: feedBuffer didnt manage to allocate memmory (%d).\n",
			sizeof(char)*SOUNDBURSTWRITE);
		return;
	}
	for (int j = 0; j < SOUNDBURSTWRITE; j++){
		int v = 0;
		short activeChannels = 0;
		for (int i = 0; i < MAXSOUNDCOUNT; i++){
			if(channels[i].ss != NULL){
	
				v += channels[i].ss->samples[channels[i].current];
				channels[i].current++;
				if (channels[i].current == channels[i].ss->length){
					channels[i].current = 0;
					finalizeSound(channels[i].ss);
					channels[i].ss = NULL;
				}
				activeChannels++;
			}
		}
		buffer[j] = v/activeChannels;
		//printf("Active channels: %d\n",activeChannels);
	}
	writeSoundValue(buffer,SOUNDBURSTWRITE);
	free(buffer);
}
