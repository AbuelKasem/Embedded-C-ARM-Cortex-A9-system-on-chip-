/*
 * Mp_core_timer.c
 *
 *  Created on: Mar 3, 2019
 *      Author: Kasem
 */
#include "Mp_core_timer.h"

volatile unsigned int *private_timer_load      = (unsigned int *) Timer_Load_Address;
    // ARM A9 Private Timer Value
volatile unsigned int *private_timer_value     = (unsigned int *)  Timer_Value_Address;
   // ARM A9 Private Timer Control
volatile unsigned int *private_timer_control   = (unsigned int *) Timer_Control_Address;
    // ARM A9 Private Timer Interrupt
volatile unsigned int *private_timer_interrupt = (unsigned int *) Timer_Interrupt_Address;

void Mp_core_timer_Init(unsigned int load) {


	*private_timer_load      = load;
}


void Mp_core_timer_start(unsigned int prescaler,char mode){
	// Set the "Prescaler" value to 0 (0<< 8), Enable the timer (E = 1)((1 << 1),
	    //Set Automatic reload (1 << 0)
	    // on overflow (A = 1), and disable ISR (I = 0) (0 << 2)
	       *private_timer_control   = (prescaler<< 8) | (0 << 2) | (1 << 1) | (mode << 0);
}

char Mp_core_timer_finished(){
	char flag=0;
	if (*private_timer_interrupt & 0x1) flag=1;
	        // Clear the timer interrupt flag. (We do this by writing 1 to the I bit)
	 *private_timer_interrupt = 0x1;
	 return flag;
}

unsigned int Mp_core_timer_read(){
	return *private_timer_value;
}
