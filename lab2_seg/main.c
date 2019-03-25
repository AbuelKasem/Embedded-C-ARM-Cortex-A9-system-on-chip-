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


volatile int *seg1_ptr = (int *) 0xFF200020;
volatile int *seg2_ptr = (int *) 0xFF200030;

int main(void) {
    /*
     *  Declare pointers to I/O registers (volatile keyword means memory not cached)
     */
// the error was not clear because watchdog timer wasn't reset auto as i thought
// using or in the segment registers ,maintained the previous value
// the solution was clearing the register b4 loading the new value


    // Red LEDs base address
    volatile int *LEDR_ptr = (int *) 0xFF200000;

    volatile int *slider_ptr = (int *)0xFF200040;
    // KEY buttons base address
   volatile int *KEY_ptr  = (int *) 0xFF200050;
    int i,cnt=2000000;
    int cntr=0;

    /*
     *  Primary Run Loop.
     *  Bare-Metal Applications use an infinite loop to keep executing (no OS).
     */
     while(1) {
        // Read WDT counter value, and display it on the red LEDs (scaled to fit)
       // *LEDR_ptr = *wdt_ccvr >> 16;
    	 *LEDR_ptr =0x00;
    	 cntr=0;
    	 while(cntr<=9) {
    	 //if (*KEY_ptr & 0x1) cntr++;
    		if (*slider_ptr & 0x01) {cntr=1;
    		if (*slider_ptr & 0x200) cntr=11;
    		}
    		else if (*slider_ptr & 0x02) {
    			cntr=2;
    			if (*slider_ptr & 0x200) cntr=12;
    		}
    		else if (*slider_ptr & 0x04) {cntr=3;
    		if (*slider_ptr & 0x200) cntr=13;
    		}
    		else if (*slider_ptr & 0x08) { cntr=4;
    		if (*slider_ptr & 0x200) cntr=14;
    		}
    		else if (*slider_ptr & 0x10) {cntr=5;
    		if (*slider_ptr & 0x200) cntr=15;
    		}
    		else if (*slider_ptr & 0x20) {cntr=6;}
    		else if (*slider_ptr & 0x40) cntr=7;
    		else if (*slider_ptr & 0x80) cntr=8;
    		else if (*slider_ptr & 0x100) cntr=9;
    		else if (*slider_ptr & 0x200) cntr=10;
    		else cntr=0;
    	//seg_dis(cntr);

    		seg_hex(cntr,1,seg2_ptr);
    		// HPS_ResetWatchdog();
    		seg_dec((cntr+10),2,seg1_ptr);
    		 HPS_ResetWatchdog();


         }




    }
}


