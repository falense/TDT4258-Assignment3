#include "stdio.h"


int main(int argc, char *argv[]){
	//char *path = argv[0];
	FILE * led_buttons_driver = fopen("driver", "w");

	/* to turn on a LED */
	unsigned char byte = 0xff;
    printf("Byte value is 0x%x\n",byte);
    if(led_buttons_driver){
    	fwrite(&byte,1,1,led_buttons_driver);	
    	fclose(led_buttons_driver);
    }
    else{
    	printf("Could not open file!\n");    	
    }


    /*
	size_t count = 1;
	size_t size = 1;
	char *buffer = malloc(sizeof(char));
	size_t r = fread ( buffer,  size, count, led_buttons_driver );
	*/
	return 0;
}


/*

#include <stdio.h>
#include <unistd.h></p>

int main() { 
  unsigned char byte,dummy;
  FILE * PARLELPORT;

  PARLELPORT=fopen("/dev/parlelport","w");
  // We remove the buffer from the file i/o 
  setvbuf(PARLELPORT,&dummy,_IONBF,1);

  byte=1;

  while (1) { 
    printf("Byte value is %d\n",byte);
    fwrite(&byte,1,1,PARLELPORT);
    sleep(1);

    byte<<=1;
    if (byte == 0) byte = 1;
  }

  fclose(PARLELPORT);

}

*/