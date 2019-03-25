/*
 * Mp_core_timer.h
 *
 *  Created on: Mar 3, 2019
 *      Author: Kasem
 */

#ifndef MP_CORE_TIMER_MP_CORE_TIMER_H_
#define MP_CORE_TIMER_MP_CORE_TIMER_H_

#define Timer_Load_Address       0xFFFEC600
#define Timer_Value_Address      0xFFFEC604
#define Timer_Control_Address    0xFFFEC608
#define Timer_Interrupt_Address  0xFFFEC60C

void Mp_core_timer_Init(unsigned int load);
void Mp_core_timer_start(unsigned int prescaler,char mode);
char Mp_core_timer_finished();
unsigned int Mp_core_timer_read();




#endif /* MP_CORE_TIMER_MP_CORE_TIMER_H_ */
