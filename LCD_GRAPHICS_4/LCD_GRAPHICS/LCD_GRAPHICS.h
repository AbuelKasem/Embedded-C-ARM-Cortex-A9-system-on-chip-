/*
 * LCD_GRAPHICS.h
 *
 *  Created on: Mar 17, 2019
 *      Author: Kasem
 */

#ifndef LCD_GRAPHICS_H_
#define LCD_GRAPHICS_H_

#include <stdbool.h>



unsigned int Graphics_initialise( unsigned int pio_base_address, unsigned int pio_hw_base_address );

void Graphics_drawLine(unsigned int x1,unsigned int y1,unsigned int x2,unsigned int y2,unsigned short colour);

void Graphics_drawTriangle(unsigned int x1,unsigned int y1,unsigned int x2,unsigned int y2,unsigned int x3,unsigned int y3,unsigned short colour,bool noFill,unsigned short fillColour);

void Graphics_drawBox(unsigned int x1,unsigned int y1,unsigned int x2,unsigned int y2,unsigned short colour,bool noFill,unsigned short fillColour);

void Graphics_drawCircle(unsigned int xc,unsigned int yc,unsigned int r,unsigned short colour,bool nofill,unsigned short fillColour);

void eight_octant_draw(unsigned short colour,int x ,int y,int p,int q);
#endif /* LCD_GRAPHICS_H_ */
