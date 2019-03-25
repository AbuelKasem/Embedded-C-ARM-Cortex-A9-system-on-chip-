/*
 * main.c
 *
 * This program is a simple piece of code to test the Watchdog Timer.
 *
 * The watchdog will be reset any time a button is pressed.
 *
 * The value of the watchdog timer is displayed on the red LEDs.
 *
 *  Created on: 13 Jan 2018
 *      Author: Doug from Up.
 *       Notes: Squirrel!
 */
#include "HPS_Watchdog/HPS_Watchdog.h"
#include "seven_seg/seven_seg.h"
#include "Mp_core_timer/Mp_core_timer.h"
volatile int *seg1_ptr = (int *) 0xFF200020;
volatile int *seg2_ptr = (int *) 0xFF200030;

int main(void) {
    /*
     *  Declare pointers to I/O registers (volatile keyword means memory not cached)
     */
// the error was not clear because watchdog timer wasn't reset auto as i thought
// using or in the segment registers ,maintained the previous value
// the solution was clearing the register b4 loading the new value
unsigned int load_value=225000000 ;
volatile unsigned int current_value;
char t_done=0;
int sec=0,mins=38,hours=19;
int f1=0,f2=0,f3=0;

    volatile int *slider_ptr = (int *)0xFF200040;
    // KEY buttons base address
   volatile int *KEY_ptr  = (int *) 0xFF200050;
int n=0;

    /*
     *  Primary Run Loop.
     *  Bare-Metal Applications use an infinite loop to keep executing (no OS).
     */
    Mp_core_timer_Init(load_value);
    Mp_core_timer_start(0,1);
  while(1) {
	  current_value= Mp_core_timer_read();
  if (*slider_ptr & 0x01)  {
	  	  if ((*KEY_ptr & 0x01) ){
	  		//  f1=1;}
    	 // if (f1==1){
    	//  f1=0;
	  	 hours++;
    		 if(hours>=24){
    			 hours=0; }

    		  }

  	 /* if (*KEY_ptr & 0x02 ) f2=1;

  	      if (f2==1){  mins++;

  	  	  	   if(mins>=59){
  	  	  	  	  mins=0;}

  	      }f2=0;



  	if (*KEY_ptr & 0x04 )  f3=1;
  	if (f3==1) {sec++;
  	  	  	  if(sec>=59){
  	  	  	  	 sec=0;}

  	}f3=0;  */
    		 }


    	 t_done=Mp_core_timer_finished();

    	 if (t_done) {
    		 sec++;
    		 if (sec>=59) {
    			 sec=0;
    			 mins++;
    			 if(mins>=59){
    				 mins=0;
    				 hours++;
    			     if(hours>=24){
    			    	 hours=0;
    		 }
    			 }
    		 }
    	 }



    		//seg_hex(cntr,1,seg2_ptr);
    		// HPS_ResetWatchdog();
    		seg_dec(sec,1,seg1_ptr);
    		seg_dec(mins,2,seg1_ptr);
    		seg_dec(hours,3,seg2_ptr);

    		 HPS_ResetWatchdog();


         }




    }



