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
/*
//
// Main Function
// =============
int main(void) {

    //Initialise the LCD Display.
	// unsigned short colours[6] = {LT24_RED,LT24_YELLOW,LT24_GREEN,LT24_CYAN,LT24_BLUE,LT24_MAGENTA};

	 unsigned int x1=50,y1=5,x2=75,y2=75,x3=100,y3=5;
    exitOnFail(
            LT24_initialise(0xFF200060,0xFF200080), //Initialise LCD
            LT24_SUCCESS);                          //Exit if not successful
    HPS_ResetWatchdog();

   // LT24_setWindow( xleft,  ytop,  width,  height);
    //LT24_window_background(xleft,  ytop,  width,  height);
    LT24_clearDisplay(0);
    //LT24_window_background(LT24_BLUE,xleft,  ytop,  width,  height);

    while (1) {

    	Graphics_drawCircle(100,100,50,LT24_GREEN,0,LT24_RED);
    	Graphics_drawCircle(100,230,30,LT24_GREEN,1,LT24_RED);

    	Graphics_drawLine(x2,y2,x3,y3, LT24_BLUE);   //x2=75,y2=150,x3=100,y3=50;  dx=25 ,dy=-100 ,s=-4

    	Graphics_drawTriangle(x1,y1,x2,y2,x3,y3,LT24_BLUE,1,LT24_GREEN);


    	Graphics_drawBox(50,100,200,150,LT24_RED,1,LT24_BLUE);


 	    Graphics_drawLine(120,160,20,160, LT24_RED);  //dy=0 ,dx- ,s=0  horizontal

    	Graphics_drawLine(191,89,120,160, LT24_BLUE);  //dx- ,dy+  ,dx<dy


    	Graphics_drawLine(0,0,150,70, LT24_GREEN);        //dx>dy ,s+

    	Graphics_drawLine(50,200,200,100, LT24_BLUE);     //dx>dy   ,s-

    	Graphics_drawLine(200,200,50,50, LT24_GREEN);     //dx=dy   ,s+

    	Graphics_drawLine(70,20,70,120, LT24_RED);     //dx=0 ,,dy+ , dx<dy  ,s=0

    	Graphics_drawLine(20,50,170,50, LT24_BLUE);     //dx+ ,,dy=0 , dx>dy  ,s=0


    	Graphics_drawLine(0,0,100,200, LT24_RED);  //dx=100 ,dy=200 ,s=2  ,dx<dy

    	Graphics_drawLine(20,30,50,70, LT24_GREEN);  //dx=30 ,dy=40 ,s1.3  ,dx<dy


        HPS_ResetWatchdog(); //Just reset the watchdog.
    }
}


*/
int main(void) {


	// exitOnFail(
	       //     LT24_initialise(0xFF200060,0xFF200080), //Initialise LCD
	      //      LT24_SUCCESS);

	 exitOnFail(
			 Graphics_initialise(0xFF200060,0xFF200080), //Initialise LCD
	 	            LT24_SUCCESS);
	 //Exit if not successful
	    HPS_ResetWatchdog();
//Initialise the LCD Display.

	    LT24_clearDisplay(0);
//Graphics_initialise(0xFF200060,0xFF200080); ResetWDT();



//Rectangle. Red Border. Grey Fill.
Graphics_drawBox(10,10,230,310,LT24_RED,false,0x39E7); ResetWDT();



//Circle. Blue Border, White Fill. Centre of screen. 100px radius
Graphics_drawCircle(120,160,100,LT24_BLUE,false,LT24_WHITE); ResetWDT();


//Circle. Yellow Border, No Fill. Centre of screen. 102px radius
Graphics_drawCircle(120,160,102,LT24_YELLOW,true,0); ResetWDT();


//Rectangle. Cyan Border, No Fill.
Graphics_drawBox(49,89,191,231,LT24_CYAN,true,0); ResetWDT();


//Line. Green. 45 degree Radius of circle.
Graphics_drawLine(191,89,120,160,LT24_GREEN); ResetWDT();


//Line. Magenta. 270 degree Radius of circle.
Graphics_drawLine(120,160,20,160,LT24_MAGENTA); ResetWDT();


//Triangle. Blue Border, No Fill. Bottom left corner. Right-angle triangle.
Graphics_drawTriangle(18,283,18,302,37,302,LT24_BLUE,true,0); ResetWDT();


//Triangle. Yellow Border, Green Fill. Bottom left corner Equilateral triangle.
Graphics_drawTriangle(213,283,204,302,222,302,LT24_YELLOW,0,LT24_GREEN);

//Done.
while (1) {

	//Graphics_drawTriangle(213,283,204,302,222,302,LT24_YELLOW,0,LT24_GREEN);


	//Graphics_drawTriangle(150,150,125,100,175,100,LT24_BLUE,0,LT24_RED);

	HPS_ResetWatchdog(); } //Watchdog reset.
}
