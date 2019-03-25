/*
 * DE1-SoC LT24 Example
 *
 * Displays a test pattern on the LT24
 * LCD using the LT24 bare metal driver.
 *
 *  Created on: 09 Feb 2018
 */

#include "DE1SoC_LT24/DE1SoC_LT24.h"
#include "HPS_Watchdog/HPS_Watchdog.h"
#include "HPS_usleep/HPS_usleep.h"

//Include our image
#include "sea.h"
#include "Test.h"
#include "man.h"
#include "joker.h"
#include "flowers.h"


//Debugging Function (same as last lab)
#include <stdlib.h>
void exitOnFail(signed int status, signed int successStatus){
    if (status != successStatus) {
        exit((int)status); //Add breakpoint here to catch failure
    }
}

//
// Main Function
// =============
int main(void) {

	unsigned short arr[76800]={0};
	 int i;

    for(i=0;i<76800;i++) arr[i]=sea[i];

    //Initialise the LCD Display.
    exitOnFail(
            LT24_initialise(0xFF200060,0xFF200080), //Initialise LCD
            LT24_SUCCESS);                          //Exit if not successful
    HPS_ResetWatchdog();
    //Display the image. Setting the co-ordinates and size of the image.
    exitOnFail(
            LT24_copyFrameBuffer(Test,0,0,240,320),
            LT24_SUCCESS); //Exit if not successful
    //Main Run Loop
    while (1) {
    	i=0;
    	for (i=0;i<76800;i++)
    	{arr[i]=arr[i]+1;
    	LT24_copyFrameBuffer(arr,0,0,240,320);
    	}
    	/*LT24_copyFrameBuffer(sea,0,0,240,320);
    	usleep(500000);
    	LT24_copyFrameBuffer(flowers,0,0,240,320);
    	 usleep(500000);
    	 LT24_copyFrameBuffer(joker,0,0,240,320);
    	     	 usleep(500000);
    	     	LT24_copyFrameBuffer(man,0,0,240,320);
    	     	    	 usleep(500000);
    	     	    	LT24_copyFrameBuffer(Test,0,0,240,320);
    	     	    	    	 usleep(500000); */
        HPS_ResetWatchdog(); //Just reset the watchdog.
    }
}
