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
#include "LCD_GRAPHICS/LCD_GRAPHICS.h"
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>


void exitOnFail(signed int status, signed int successStatus){
    if (status != successStatus) {
        exit((int)status); //Add breakpoint here to catch failure
    }
}





int main(void) {

	//Graphics_initialise(0xFF200060,0xFF200080); ResetWDT();

	 exitOnFail(
			 Graphics_initialise(0xFF200060,0xFF200080), //Initialise LCD
			 Graphics_SUCCESS);
	 //Exit if not successful
	    HPS_ResetWatchdog();
//Initialise the LCD Display.
	    exitOnFail(
	    		LT24_clearDisplay(0),
				Graphics_SUCCESS);
	    ResetWDT();




//Rectangle. Red Border. Grey Fill.
	    exitOnFail(
	    		Graphics_drawBox(10,10,230,310,LT24_RED,false,0x39E7),
				Graphics_SUCCESS);
	    ResetWDT();


//Circle. Blue Border, White Fill. Centre of screen. 100px radius
	    exitOnFail(
	    		Graphics_drawCircle(120,160,100,LT24_BLUE,false,LT24_WHITE),
	    Graphics_SUCCESS);
	    ResetWDT();

//Circle. Yellow Border, No Fill. Centre of screen. 102px radius

	    exitOnFail(
                 Graphics_drawCircle(120,160,102,LT24_YELLOW,true,0),
				 Graphics_SUCCESS);
	    ResetWDT();


//Rectangle. Cyan Border, No Fill.
	    exitOnFail(
	    		Graphics_drawBox(49,89,191,231,LT24_CYAN,true,0),
				Graphics_SUCCESS);
	    ResetWDT();


//Line. Green. 45 degree Radius of circle.
	    exitOnFail(
	    		Graphics_drawLine(191,89,120,160,LT24_GREEN),
				Graphics_SUCCESS);
	    ResetWDT();


//Line. Magenta. 270 degree Radius of circle.
	    exitOnFail(
	    		Graphics_drawLine(120,160,20,160,LT24_MAGENTA),
				Graphics_SUCCESS);
		ResetWDT();


//Triangle. Blue Border, No Fill. Bottom left corner. Right-angle triangle.


		 exitOnFail(
				 Graphics_drawTriangle(18,283,18,302,37,302,LT24_BLUE,true,0),
				 Graphics_SUCCESS);
		 ResetWDT();


//Triangle. Yellow Border, Green Fill. Bottom left corner Equilateral triangle.

		 exitOnFail(
				 Graphics_drawTriangle(213,283,204,302,222,302,LT24_YELLOW,0,LT24_GREEN),
				 Graphics_SUCCESS);

//Done.
while (1) {

	//Graphics_drawTriangle(213,283,204,302,222,302,LT24_YELLOW,0,LT24_GREEN);
	//Graphics_drawLine(50,100,100,150,LT24_RED);
	// Graphics_drawTriangle2(213,283,204,302,222,302,LT24_YELLOW,0,LT24_GREEN);
	// Graphics_drawTriangle2(18,283,18,302,37,302,LT24_BLUE,0,LT24_YELLOW);
	//Graphics_drawTriangle2(150,150,125,100,175,100,LT24_BLUE,0,LT24_RED);

	HPS_ResetWatchdog(); } //Watchdog reset.
}


