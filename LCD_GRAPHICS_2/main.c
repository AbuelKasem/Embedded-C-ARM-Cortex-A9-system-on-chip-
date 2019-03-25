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
#include "Test.h"

//Debugging Function (same as last lab)
#include <stdlib.h>
#include <math.h>


Graphics_drawLine(unsigned int x1,unsigned int y1,unsigned int x2,unsigned int y2,unsigned short colour);
void exitOnFail(signed int status, signed int successStatus){
    if (status != successStatus) {
        exit((int)status); //Add breakpoint here to catch failure
    }
}

//
// Main Function
// =============
int main(void) {
	//int i=0;
    //Initialise the LCD Display.
	 unsigned short colours[6] = {LT24_RED,LT24_YELLOW,LT24_GREEN,LT24_CYAN,LT24_BLUE,LT24_MAGENTA};
	 unsigned int colourIdx = 0;
	 unsigned int x1=50,y1=50,x2=75,y2=150,x3=100,y3=50;
    exitOnFail(
            LT24_initialise(0xFF200060,0xFF200080), //Initialise LCD
            LT24_SUCCESS);                          //Exit if not successful
    HPS_ResetWatchdog();
    //Display the image. Setting the co-ordinates and size of the image.

   // LT24_setWindow( xleft,  ytop,  width,  height);
    //LT24_window_background(xleft,  ytop,  width,  height);
    LT24_clearDisplay(LT24_YELLOW);
    //LT24_window_background(LT24_BLUE,xleft,  ytop,  width,  height);




    while (1) {





    			//Graphics_drawLine(x1,y1,x2,y2, LT24_RED);

    	    	//Graphics_drawLine(x2,y2,x3,y3, LT24_BLUE);

    	    	//Graphics_drawLine(x3,y3,x1,y1, LT24_GREEN);

    	    	//Graphics_drawLine(70,25,70,100, LT24_BLUE);

    	    	//Graphics_drawLine(40,160,150,60, LT24_RED);


    	//Graphics_drawLine(120,160,20,160, LT24_RED);

    	//Graphics_drawLine(191,89,120,160, LT24_BLUE);

    	//Graphics_drawLine(50,25,200,100, LT24_GREEN);

    	//Graphics_drawLine(70,25,70,100, LT24_BLUE);

    	Graphics_drawLine(40,160,150,60, LT24_RED);

        HPS_ResetWatchdog(); //Just reset the watchdog.
    }
}

Graphics_drawLine(unsigned int x1,unsigned int y1,unsigned int x2,unsigned int y2,unsigned short colour){
	int dy=0;  //difference in y axis
	int dx=0;   //difference in x axis
	int f=0; //flag for when x1=x2 ,used to control the drawing loop
	float s=0; //slope of the line
	double  k;   //intercept
    double eqn;
    float c;

	int x_step=0,y_step=0;   // the increment/decrement step
	int i=0,j=0;               // iterators i for x ,j for y
	dy=y2-y1;
	dx=x2-x1;

	if(y2>y1){    // to decide the direction of movement
	y_step=1;  // if end larger than start , step is positive ,to increment by a single pixel


	}
	else if(y2<y1){
		y_step=-1;  // if end less than start , step is negative ,to decrement by a single pixel
	}


	if(x2>x1) {  // same as y ,to determine the step

		x_step=1;
	}
	else if(x2<x1){

			x_step=-1;
	}


    //y=s*x+c   the straight line equation ,
	//y1=s*x1+c  , c=y1-s*x1  , calculating the intercept
	if(x1!=x2) s=(float)dy/(float)dx;  // if only there is difference in x axis ,calculate slope
	                                   // else slope =0 , to prevent division by zero

	c=y1-(s*x1);


	//c=round(c1);     // calculating the intercept
	j=y1;          // init. the y iterator to first point's y coordinate ,y1
	if(x1==x2) f=1;  //when the line to be drawn is vertical , set a flag to 1
	else f=0;        // else if the line is not vertical , clear the flag


	// the for loop ,init. the i iterator for x to x1 , then check if the condition if the iterator reached
	// the end point in x ,or the flag is set (to enter the loop in case of vertical line (x1=x2)
	// as long as either conditions is true , execute the loop , when both conditions are false
	// terminate
	for(i=x1;(i!=x2|| f);i=i+x_step){   //i >>>x  ,j>>> y

		if(x1==x2) {
			i=x2;            // if the line is vertical , no change in x axis
			j=j+y_step;     // if the line is vertical , then we only need to fix x and
		                   // either decrement or increment y by the step
			}
		else if((x1!=x2) && (s<=1)){                    // only if the line is not vertical , caluclate y's new position
	    	                      // from the line's equation
	    		 if(j!=y2){
	    	eqn=s*i+c;
	    	//k=round(eqn);//as long as the y iterator is didn't reach the destination
	    	  j=(int)eqn;}
		}            // the line's equation
		else
		if(y1==y2) j=y2;           // if the line is horizontal ,no change in y axis

		 if(j==y2) f=0;            // once the y iterator reaches the end point , clear the flag
                                       // to exit the loop



	      usleep(1000);  // the delay is only to animate the line drawing
	      LT24_drawPixel(colour,i,j);  // call the pixel draw function with the desired color and
	                                   // the updated x & y coordinates of the pixels along the line
	     usleep(1000);

	}
	/*
	for(i=x1;(i!=x2 || j!=y2);i=i+x_step){
			if(x1==x2) i=x2;
			if(y1==y2) j=y2;

		      if(j!=y2){
		    	  j=slope*i;}
		    	  //j=j+y_step;}

		      usleep(50000);
		      LT24_drawPixel(colour,i,j);
		      usleep(50000);
		}
       */


}

