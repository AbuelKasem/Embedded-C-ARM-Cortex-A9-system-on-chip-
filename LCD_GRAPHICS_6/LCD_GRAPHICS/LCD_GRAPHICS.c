/*
 * LCD_GRAPHICS.c



 *
 *  Created on: Mar 17, 2019
 *      Author: Kasem
 */
#include <stdbool.h>
#include <stdlib.h>
#include "LCD_GRAPHICS.h"
#include <math.h>
#include "../DE1SoC_LT24/DE1SoC_LT24.h"
#include "../HPS_Watchdog/HPS_Watchdog.h"
#include "../HPS_usleep/HPS_usleep.h"


#define  T   50    // animatie time




signed int Graphics_initialise( unsigned int lcd_pio_base, unsigned int lcd_hw_base ){
	signed int init_status_code=0;
	if(!(LT24_isInitialised())) {
		init_status_code=-1;
		init_status_code=LT24_initialise(lcd_pio_base,lcd_hw_base);

	}

	return init_status_code;


}

signed int Graphics_drawLine(unsigned int x1,unsigned int y1,unsigned int x2,unsigned int y2,unsigned short colour)
{
		signed int graphics_status=0;
	    int dy=0;  //difference in y axis
		int dx=0;   //difference in x axis
		float s=0; //slope of the line
	    float err=0;
		int x_step=0,y_step=0;   // the increment/decrement step
		int i=0,j=0,x=0,y=0,n=0,m=0,step1=0,step2=0;               // iterators i for x ,j for y

		if(x1 > LT24_WIDTH_limit || x2 > LT24_WIDTH_limit || y1 > LT24_HEIGHT_limit || y2 > LT24_HEIGHT_limit )
				{ graphics_status=Graphics_INVALIDSIZE; }   // if any of the points is beyond the limit of the lcd , return error of invalid size

				if (graphics_status != Graphics_SUCCESS ) return graphics_status;
		dy=y2-y1;      // delta y
		dx=x2-x1;      // delta x
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
                                         //y=s*x+c   the straight line equation                                   //y1=s*x1+c  , c=y1-s*x1  , calculating the intercept
		if(x1!=x2) s=(float)dy/(float)dx;
		if(s<0) s=s*(-1);
		if(s>1) s=1/s;
		err=s-1;
		if(dx==-dy || dy==-dx) dx=dy;//
		 if(dx <0 )  dx=dx*-1;
		 if(dy<0)     dy=dy*-1;


        if(dx>=dy || dy==0) {
			n=x1;
			m=x2;
			step1=x_step;
			step2=y_step;
			j=y1;
		}
		else if(dx==0 || dx < dy  ) {
			n=y1;
			m=y2;
			step1=y_step;
			step2=x_step;
			j=x1;

		}


		for(i=n;(i!=m);i=i+step1){   //i >>>x  ,j>>> y

			if(y1==y2) {
				y=y2;
				x=i;
			}

			else if(x1==x2) {
				x=x2;
				y=i;
			           }
			else if(dx>=dy){
				x=i;
				y=j;
			}
			else if(dx < dy){   //slope greater than 1 , swap x and y , make y driving axis ,and x driven
							y=i;
							x=j;
						}

			usleep(T);

			graphics_status= LT24_drawPixel(colour,x,y);
			if (graphics_status != Graphics_SUCCESS ) return graphics_status;
		 usleep(T);

			 if(err>=0) {
				 j=j+step2;

			    err=err-1;
			            }
			 err=err+s;


		}
		return Graphics_SUCCESS;
	}


signed int Graphics_drawTriangle(unsigned int x1,unsigned int y1,unsigned int x2,unsigned int y2,unsigned int x3,unsigned int y3,unsigned short colour,bool noFill,unsigned short fillColour)
{
	  signed int graphics_status=0;
	  int n,m,xmax,xmin,ymax,ymin;


	graphics_status=Graphics_drawLine(x1,y1,x2,y2, colour);
	if (graphics_status != Graphics_SUCCESS ) return graphics_status;
	graphics_status=Graphics_drawLine(x2,y2,x3,y3, colour);
    if (graphics_status != Graphics_SUCCESS ) return graphics_status;
    graphics_status=Graphics_drawLine(x3,y3,x1,y1, colour);
	if (graphics_status != Graphics_SUCCESS ) return graphics_status;

	if(noFill ) return Graphics_SUCCESS;


	if(!noFill ) {

   xmax = (x1 > x2) ? (x1 > x3 ? x1 : x3) : (x2 > x3 ? x2 : x3);
   ymax = (y1 > y2) ? (y1 > y3 ? y1 : y3) : (y2 > y3 ? y2 : y3);
   xmin= (x1 < x2) ? (x1 < x3 ? x1 : x3) : (x2 < x3 ? x2 : x3);
   ymin = (y1 <y2) ? (y1 < y3 ? y1 : y3) : (y2 < y3 ? y2 : y3);

		for(n=xmin;n<=xmax;n++){
		         for(m=ymin;m<=ymax;m++){

		         	if(isInside(x1,y1,x2,y2,x3,y3,n,m)) {
		         		LT24_drawPixel(fillColour,n,m);
		         	    }
		}

	}


}
	return Graphics_SUCCESS;
}




float area(int x1, int y1, int x2, int y2, int x3, int y3)
{
   return abs((x1*(y2-y3) + x2*(y3-y1)+ x3*(y1-y2))/2.0);
}
bool isInside(int x1, int y1, int x2, int y2, int x3, int y3, int x, int y)
{
   /* Calculate area of triangle ABC */
   float A = area (x1, y1, x2, y2, x3, y3);

   /* Calculate area of triangle PBC */
   float A1 = area (x, y, x2, y2, x3, y3);

   /* Calculate area of triangle PAC */
   float A2 = area (x1, y1, x, y, x3, y3);

   /* Calculate area of triangle PAB */
   float A3 = area (x1, y1, x2, y2, x, y);

   /* Check if sum of A1, A2 and A3 is same as A */
   return (A == A1 + A2 + A3);
}


signed int Graphics_drawBox(unsigned int x1,unsigned int y1,unsigned int x2,unsigned int y2,unsigned short colour,bool noFill,unsigned short fillColour)

{
	signed int graphics_status=0;
	// x1,y1  top left corner
	//x2,y2 bottom right corner
	unsigned int x3,y3,x4, y4;
	  x3=x1;
	  y3=y2;
	  x4=x2;
	  y4=y1;

	   graphics_status=Graphics_drawLine(x1,y1,x3,y3, colour);
	   if (graphics_status != Graphics_SUCCESS ) return graphics_status;

	   graphics_status= Graphics_drawLine(x3,y3,x2,y2, colour);
	   if (graphics_status != Graphics_SUCCESS ) return graphics_status;

	   graphics_status=Graphics_drawLine(x2,y2,x4,y4, colour);
	   if (graphics_status != Graphics_SUCCESS ) return graphics_status;

	   graphics_status=Graphics_drawLine(x4,y4,x1,y1, colour);
	   if (graphics_status != Graphics_SUCCESS ) return graphics_status;

	   if(noFill ) return Graphics_SUCCESS;

	   if(!noFill)  do {

		                                     //while(x1!=x2 && y1 != y2
		 x1++;
		 y1++;
		 x2--;
		 y2--;

		 Graphics_drawBox(x1,y1,x2,y2,fillColour,1,fillColour);
		 if(x1==x2 || y1==y2) break;
	 } while(x1!=x2);



x1=0,x2=0,y1=0,y2=0;
 return Graphics_SUCCESS;

}

signed int Graphics_drawCircle(unsigned int xc,unsigned int yc,unsigned int r,unsigned short colour,bool noFill,unsigned short fillColour){

	signed int graphics_status=0;





	 int p,q;
	 int x,y,d;
	 if(xc > LT24_WIDTH_limit || (xc+r) > LT24_WIDTH_limit || yc > LT24_HEIGHT_limit || (yc+r) > LT24_HEIGHT_limit )
	 		 // if any of centre coordinates is beyond the limit of the lcd  or the centre plus radius is greater than limits
	 		//, return error of invalid size to prevent the program from iterating through non existent pixels
	 			{ graphics_status=Graphics_INVALIDSIZE; }

	 			if (graphics_status != Graphics_SUCCESS ) return graphics_status;
	 p=0;
	 q=r;
	x=xc;
	y=yc;
	d=3-(2*r);
	graphics_status=eight_octant_draw(colour,x,y,p,q);
	if (graphics_status != Graphics_SUCCESS ) return graphics_status;
	while(p<=q) {
		p++;
		if(d<0) {d=d+4*p+6;

		}
		else {
			q=q-1;
			d=d+4*(p-q)+10;
		}
		graphics_status=eight_octant_draw(colour,x,y,p,q);
		if (graphics_status != Graphics_SUCCESS ) return graphics_status;
	}
    r=r-1;
if(noFill ) return Graphics_SUCCESS;

if(!noFill) while(r>=1) {
	r--;
	graphics_status=Graphics_drawCircle(xc,yc,r,fillColour,1,fillColour);
	if (graphics_status != Graphics_SUCCESS ) return graphics_status;

}
return Graphics_SUCCESS;

}


signed int eight_octant_draw(unsigned short colour,int x ,int y,int p,int q){


	signed int graphics_status=0;


	graphics_status= LT24_drawPixel(colour,x+p,y+q);  //1st octant
	if (graphics_status != Graphics_SUCCESS ) return graphics_status;


	graphics_status= LT24_drawPixel(colour,x-p,y+q);
	if (graphics_status != Graphics_SUCCESS ) return graphics_status;


	graphics_status= LT24_drawPixel(colour,x+p,y-q);
	if (graphics_status != Graphics_SUCCESS ) return graphics_status;


	graphics_status= LT24_drawPixel(colour,x-p,y-q);
	if (graphics_status != Graphics_SUCCESS ) return graphics_status;


	graphics_status= LT24_drawPixel(colour,x+q,y+p);
	if (graphics_status != Graphics_SUCCESS ) return graphics_status;


	graphics_status= LT24_drawPixel(colour,x-q,y+p);
	if (graphics_status != Graphics_SUCCESS ) return graphics_status;


	graphics_status= LT24_drawPixel(colour,x+q,y-p);
	if (graphics_status != Graphics_SUCCESS ) return graphics_status;


	graphics_status= LT24_drawPixel(colour,x-q,y-p);
	if (graphics_status != Graphics_SUCCESS ) return graphics_status;


	return Graphics_SUCCESS;


}

