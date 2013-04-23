#include <stdio.h>


int main(int argc, char *argv[]){
	//char *path = argv[0];
	FILE * led_buttons_driver = fopen("driver", "r");

	/* to turn on a LED */
	  //for (int i = 0; i < )
	  if(!led_buttons_driver){
	    printf("Could not open file!\n");     
	    return 0;

	  }


	char oldbyte = 0;
	while(1){

    	char byte = 0;

  	if (fread(&byte,1,1,led_buttons_driver) <=0){

		printf("Failed reading from driver\n");
		}	
	  	if (byte != oldbyte){
			oldbyte = byte;
			printf("New value detected from buttons: %d\n",byte);
		}
	  }

  	fclose(led_buttons_driver);

	return 0;
}


