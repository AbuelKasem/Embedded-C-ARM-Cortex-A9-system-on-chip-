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
unsigned int recursiveSum(unsigned int N);
unsigned int summ_er(unsigned int n);
unsigned int sum_n(unsigned int n);
int main(void) {
    /*
     *  Declare pointers to I/O registers (volatile keyword means memory not cached)
     */

    // Red LEDs base address
    volatile int *LEDR_ptr = (int *) 0xFF200000;
    volatile int *seg1_ptr = (int *) 0xFF200020;
    volatile int *seg2_ptr = (int *) 0xFF200030;

  //  volatile int *slider_ptr = (int *)0xFF200040;
    // KEY buttons base address
   volatile int *KEY_ptr  = (int *) 0xFF200050;
   unsigned int n,l=0,dis1=0,dis2=0,dis3=0;


    /*
     *  Primary Run Loop.
     *  Bare-Metal Applications use an infinite loop to keep executing (no OS).
     */
     while(1) {
    	 n=*KEY_ptr & 0x0F;
    	 dis1=summ_er(n);
    	 dis2= sum_n(n);
    	 dis3=recursiveSum(99);


        seg_dec(dis1,1,seg1_ptr);
        seg_dec(dis2,2,seg1_ptr);
        seg_dec(dis3,3,seg2_ptr);
    	 *LEDR_ptr = summ_er(n);
    	 HPS_ResetWatchdog();

}
}

unsigned int summ_er(unsigned int n){
	unsigned int summ=0;
	while(n!=0) {
	    		 summ=summ+n;
	    		 n--;
	    	 }
	return summ;
}


// Recursively sum numbers 0 to N
unsigned int recursiveSum(unsigned int N) {
	if (N == 0) {
        //If N is 0, we have reached deepest level
		return 0; //The sum of 0 + 0 is 0.
	} else {
        //Otherwise we need to perform another level
		return N + recursiveSum(N-1); //Return N + sum(0 to N-1)
	}
}

unsigned int sum_n(unsigned int n){
	return (n*(n+1)/2);


}
