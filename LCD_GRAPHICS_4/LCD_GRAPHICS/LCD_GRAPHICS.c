/*
 * LCD_GRAPHICS.c



 *
 *  Created on: Mar 17, 2019
 *      Author: Kasem
 */
#include <stdbool.h>
#include "LCD_GRAPHICS.h"
#include <math.h>
#include "../DE1SoC_LT24/DE1SoC_LT24.h"
#include "../HPS_Watchdog/HPS_Watchdog.h"
#include "../HPS_usleep/HPS_usleep.h"


#define  T   150    // animatie time




unsigned int  Graphics_initialise( unsigned int pio_base_address, unsigned int pio_hw_base_address ){

	if(!(LT24_isInitialised())) LT24_initialise(pio_base_address,pio_hw_base_address);
	else return 0;


}

void Graphics_drawLine(unsigned int x1,unsigned int y1,unsigned int x2,unsigned int y2,unsigned short colour)
{

	    int dy=0;  //difference in y axis
		int dx=0;   //difference in x axis
		float s=0; //slope of the line
	    float err=0;
		int x_step=0,y_step=0;   // the increment/decrement step
		int i=0,j=0,x=0,y=0,n=0,m=0,step1=0,step2=0;               // iterators i for x ,j for y
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
			else if(dx < dy){
							y=i;
							x=j;
						}

			usleep(T);

			 LT24_drawPixel(colour,x,y);
		 usleep(T);

			 if(err>=0) {
				 j=j+step2;

			    err=err-1;
			            }
			 err=err+s;


		}
	}


void Graphics_drawTriangle(unsigned int x1,unsigned int y1,unsigned int x2,unsigned int y2,unsigned int x3,unsigned int y3,unsigned short colour,bool noFill,unsigned short fillColour)
{
	float invs1 ;
	  float invs2;
	  int x1f=(int)x1,x2f=(int)x2,x3f=(int)x3,y1f=(int)y1,y2f=(int)y2,y3f=(int)y3 ;
	  float curx1 ;
	  float curx2 ;
	  int scanlineY;
	int dx1,dy1,dx2,dy2;


	Graphics_drawLine(x1,y1,x2,y2, colour);

    Graphics_drawLine(x2,y2,x3,y3, colour);

	Graphics_drawLine(x3,y3,x1,y1, colour);





	if(!noFill ) {

		if(y2>y1) {
			if (y2==y3){
				dx1=x2f -x1f;
				dy1=y2f - y1f;
				dx2=x3f - x1f;
				dy2=y3f - y1f;
		       invs1 =  ( float)dx1 / (float)dy1;

			   invs2 = (float)dx2 / ( float)dy2;
			   curx1 = x1;
			  curx2 = x1;}

			for ( scanlineY = y1; scanlineY <y3; scanlineY++) {
				Graphics_drawLine((int)curx1, scanlineY, (int)curx2, scanlineY,fillColour);
			    curx1 += invs1;
			    curx2 += invs2;
			  }
			}
		else if(y1>y2) {
			if (y2==y3){
							dx1=x1f -x2f;
							dy1=y1f - y2f;
							dx2=x1f - x3f;
							dy2=y1f - y3f;
					       invs1 =  ( float)dx1 / (float)dy1;

						   invs2 = (float)dx2 / ( float)dy2;
						   curx1 = x1;
						  curx2 = x1+1;}
						for ( scanlineY = y1; scanlineY >y2; scanlineY--) {
							Graphics_drawLine((int)curx1, scanlineY, (int)curx2, scanlineY,fillColour);
						    curx1 -= invs1;
						    curx2 -= invs2;
						  }

		}




	}
		/*

		if (y2-y1 > 0) dx1=(x2-x1)/(y2-y1);
		else dx1=0;

	    if (y3-y1> 0) dx2=(x3-x1)/(y3-y1);
	    	else dx2=0;
		if (y3-y2 > 0) dx3=(x3-x2)/(y3-y2);
			else dx3=0;

			//S=E=A;
			sx=x1;
			sy=y1;
			ex=sx;
			ey=sy;

			if(dx1 > dx2) {
				for(;  sy<=y2;  sy++,ey++, sx=sx+dx2,ex=ex+dx1){

					Graphics_drawLine(sx,sy,ex,ey,fillColour);}
				//E=B;
				ex=x2;
				ey=y2;
				for(;sy<=y3; sy++,ey++, sx=sx+dx2,ex=ex+dx3)
					Graphics_drawLine(sx,sy,ex,ey,fillColour);
			} else {
				for(;sy<=y2; sy++,ey++, sx=sx+dx1,ex=ex+dx2)
					Graphics_drawLine(sx,sy,ex,ey,fillColour);
				//S=B;
				sx=x2;
				sy=y2;
				for(;sy<=y3; sy++,ey++, sx=sx+dx3,ex=ex+dx2)
					Graphics_drawLine(sx,sy,ex,ey,fillColour);
			}
		}

       if(y2==y3 && y2>y1){
		        y2--;
		        y3--;
		        y1++;
        	}
        if(x2<x1 && x3>x1){
        	x2++;
        	x3--;
        				}


  if(!noFill) while(x1!=x2 && y2!=y1){
	  x1++;
	  y1++;
	  y2--;
	  x3--;
	 if(y2!=y3) y3++;
	 else y3--;
	  Graphics_drawTriangle(x1,y1,x2,y2,x3,y3,fillColour,1,fillColour);
  }  */

}


void Graphics_drawBox(unsigned int x1,unsigned int y1,unsigned int x2,unsigned int y2,unsigned short colour,bool noFill,unsigned short fillColour)

{

	// x1,y1  top left corner
	//x2,y2 bottom right corner
	unsigned int x3,y3,x4, y4;
	  x3=x1;
	  y3=y2;
	  x4=x2;
	  y4=y1;

	       Graphics_drawLine(x1,y1,x3,y3, colour);

	       Graphics_drawLine(x3,y3,x2,y2, colour);

	  	   Graphics_drawLine(x2,y2,x4,y4, colour);

	    	Graphics_drawLine(x4,y4,x1,y1, colour);


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

}

void Graphics_drawCircle(unsigned int xc,unsigned int yc,unsigned int r,unsigned short colour,bool nofill,unsigned short fillColour){

	 int p,q;
	 int x,y,d;
	 p=0;
	 q=r;
	x=xc;
	y=yc;
	d=3-(2*r);
	eight_octant_draw(colour,x,y,p,q);
	while(p<=q) {
		p++;
		if(d<0) {d=d+4*p+6;

		}
		else {
			q=q-1;
			d=d+4*(p-q)+10;
		}
		eight_octant_draw(colour,x,y,p,q);
	}
r=r-1;
if(!nofill) while(r>=2) {
	r--;
	Graphics_drawCircle(xc,yc,r,fillColour,1,fillColour);

}


}


void eight_octant_draw(unsigned short colour,int x ,int y,int p,int q){

	LT24_drawPixel(colour,x+p,y+q);  //1st octant

		LT24_drawPixel(colour,x-p,y+q);

		LT24_drawPixel(colour,x+p,y-q);

		LT24_drawPixel(colour,x-p,y-q);

		LT24_drawPixel(colour,x+q,y+p);

		LT24_drawPixel(colour,x-q,y+p);

		LT24_drawPixel(colour,x+q,y-p);

		LT24_drawPixel(colour,x-q,y-p);




}

