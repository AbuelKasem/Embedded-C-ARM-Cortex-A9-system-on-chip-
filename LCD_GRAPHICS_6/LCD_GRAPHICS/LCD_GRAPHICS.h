/*
 * LCD_GRAPHICS.h
 *
 *  Created on: Mar 17, 2019
 *      Author: Kasem
 */

#ifndef LCD_GRAPHICS_H_
#define LCD_GRAPHICS_H_

#include <stdbool.h>

//Error Codes
#define Graphics_SUCCESS       0
#define Graphics_ERRORNOINIT  -1
#define Graphics_INVALIDSIZE  -4


//Size of the LCD
#define LT24_WIDTH_limit  240
#define LT24_HEIGHT_limit 320

signed int Graphics_initialise( unsigned int lcd_pio_base, unsigned int lcd_hw_base );

signed int Graphics_drawLine(unsigned int x1,unsigned int y1,unsigned int x2,unsigned int y2,unsigned short colour);


signed int Graphics_drawTriangle(unsigned int x1,unsigned int y1,unsigned int x2,unsigned int y2,unsigned int x3,unsigned int y3,unsigned short colour,bool noFill,unsigned short fillColour);

signed int Graphics_drawBox(unsigned int x1,unsigned int y1,unsigned int x2,unsigned int y2,unsigned short colour,bool noFill,unsigned short fillColour);

bool point_Triangle(int x1, int y1, int x2, int y2, int x3, int y3, int xp, int yp);

signed int Graphics_drawCircle(unsigned int xc,unsigned int yc,unsigned int r,unsigned short colour,bool noFill,unsigned short fillColour);

signed int eight_octant_draw(unsigned short colour,int x ,int y,int p,int q);

bool isInside(int x1, int y1, int x2, int y2, int x3, int y3, int x, int y);

float area(int x1, int y1, int x2, int y2, int x3, int y3);
#endif /* LCD_GRAPHICS_H_ */
