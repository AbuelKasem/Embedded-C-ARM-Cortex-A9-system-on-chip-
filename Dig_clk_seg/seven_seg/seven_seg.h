/*
 * seven_seg.h
 *
 *  Created on: Feb 5, 2019
 *      Author: Kasem
 */

#ifndef SEVEN_SEG_H_
#define SEVEN_SEG_H_


extern volatile int *seg1_ptr;
extern volatile int *seg2_ptr;
void seg_dec(int n,int pair,volatile int *ptr);
void seg_hex(int x,int seg,int *ptr);

#endif /* SEVEN_SEG_H_ */
