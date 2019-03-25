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
volatile int *seg_ptr = (int *) 0xFF200020;
//volatile int *seg1_ptr = (int *) 0xFF200022;
void seg_dis(int n);
void seg_hex(int x);
int main(void) {
    /*
     *  Declare pointers to I/O registers (volatile keyword means memory not cached)
     */



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
    		if (*slider_ptr & 0x01) cntr=1;
    		else if (*slider_ptr & 0x02) cntr=2;
    		else if (*slider_ptr & 0x04) cntr=3;
    		else if (*slider_ptr & 0x08) cntr=4;
    		else if (*slider_ptr & 0x10) cntr=5;
    		else if (*slider_ptr & 0x20) cntr=6;
    		else if (*slider_ptr & 0x40) cntr=7;
    		else if (*slider_ptr & 0x80) cntr=8;
    		else if (*slider_ptr & 0x100) cntr=9;
    		else if (*slider_ptr & 0x200) cntr=10;
    		else if ((*slider_ptr & 0x100)&&(*slider_ptr & 0x01)) cntr=11;
    		else if ((*slider_ptr & 0x100)&&(*slider_ptr & 0x02)) cntr=12;
    		else if ((*slider_ptr & 0x100)&&(*slider_ptr & 0x04)) cntr=13;
    		else if ((*slider_ptr & 0x100)&&(*slider_ptr & 0x08)) cntr=14;
    		else if ((*slider_ptr & 0x100)&&(*slider_ptr & 0x10)) cntr=15;
    		else cntr=0;
    	//seg_dis(cntr);
    		seg_hex(cntr);



         }




    }
}

void seg_dis(int n) {
	int dig1,dig2=0,dig3=0,temp=0;
	if (n<=9) {dig1=n;
	}

	else if (n>9 && n<=99){ dig1=n%10;
	dig2=n/10;}
	else if (n>99) {
	dig3=n/100;
	temp=n%100;
	dig1=temp%10;
		dig2=temp/10;
	}
	switch(dig1) {
	         case 0:    *seg_ptr=*seg_ptr| 0x3F;  //0
	         break;
	         case 1:   *seg_ptr=*seg_ptr| 0x06;  //1
	         break;
	         case 2:   *seg_ptr=*seg_ptr| 0x5B;//2
	         break;
	         case 3:   *seg_ptr=*seg_ptr| 0x4F;//3
	         break;
	         case 4:   *seg_ptr=*seg_ptr| 0x66;//4
	         break;
	         case 5:   *seg_ptr=*seg_ptr| 0x6D;//5
	         break;
	         case 6:   *seg_ptr=*seg_ptr| 0x5F;//6
	         break;
	         case 7:   *seg_ptr=*seg_ptr| 0x07;//7
	         break;
	         case 8:   *seg_ptr=*seg_ptr| 0x7F;//8
	         break;
	         case 9:   *seg_ptr=*seg_ptr| 0x6F;//9
	         break;

	         }
	switch(dig2) {
		         case 0:    *seg_ptr=*seg_ptr| 0x3F00;  //0
		         break;
		         case 1:   *seg_ptr=*seg_ptr| 0x0600;  //1
		         break;
		         case 2:   *seg_ptr=*seg_ptr| 0x5B00;//2
		         break;
		         case 3:   *seg_ptr=*seg_ptr| 0x4F00;//3
		         break;
		         case 4:   *seg_ptr=*seg_ptr| 0x6600;//4
		         break;
		         case 5:   *seg_ptr=*seg_ptr|0x6D00;//5
		         break;
		         case 6:   *seg_ptr=*seg_ptr| 0x5F00;//6
		         break;
		         case 7:   *seg_ptr=*seg_ptr| 0x0700;//7
		         break;
		         case 8:   *seg_ptr=*seg_ptr| 0x7F00;//8
		         break;
		         case 9:   *seg_ptr=*seg_ptr| 0x6F00;//9
		         break;

		         }

	switch(dig3) {
			         case 0:    *seg_ptr=*seg_ptr| 0x3F0000;  //0
			         break;
			         case 1:   *seg_ptr=*seg_ptr| 0x060000;  //1
			         break;
			         case 2:   *seg_ptr=*seg_ptr| 0x5B0000;//2
			         break;
			         case 3:   *seg_ptr=*seg_ptr| 0x4F0000;//3
			         break;
			         case 4:   *seg_ptr=*seg_ptr| 0x660000;//4
			         break;
			         case 5:   *seg_ptr=*seg_ptr|0x6D0000;//5
			         break;
			         case 6:   *seg_ptr=*seg_ptr| 0x5F0000;//6
			         break;
			         case 7:   *seg_ptr=*seg_ptr| 0x070000;//7
			         break;
			         case 8:   *seg_ptr=*seg_ptr| 0x7F0000;//8
			         break;
			         case 9:   *seg_ptr=*seg_ptr| 0x6F0000;//9
			         break;

			         }
}

void seg_hex(int x){


	if ((x<=15) && (x>=0)){


	switch(x) {
		         case 0:    *seg_ptr=*seg_ptr| 0x3F;  //0
		         break;
		         case 1:   *seg_ptr=*seg_ptr| 0x06;  //1
		         break;
		         case 2:   *seg_ptr=*seg_ptr| 0x5B;//2
		         break;
		         case 3:   *seg_ptr=*seg_ptr| 0x4F;//3
		         break;
		         case 4:   *seg_ptr=*seg_ptr| 0x66;//4
		         break;
		         case 5:   *seg_ptr=*seg_ptr| 0x6D;//5
		         break;
		         case 6:   *seg_ptr=*seg_ptr| 0x5F;//6
		         break;
		         case 7:   *seg_ptr=*seg_ptr| 0x07;//7
		         break;
		         case 8:   *seg_ptr=*seg_ptr| 0x7F;//8
		         break;
		         case 9:   *seg_ptr=*seg_ptr| 0x6F;//9
		         break;
		         case 10:   *seg_ptr=*seg_ptr| 0x77;//A
		         break;
		         case 11:   *seg_ptr=*seg_ptr| 0x7F;//B
		         break;
		         case 12:   *seg_ptr=*seg_ptr| 0x39;//C
		         break;
		         case 13:   *seg_ptr=*seg_ptr| 0x3F;//D
		         break;
		         case 14:   *seg_ptr=*seg_ptr| 0x79;//E
		         break;
		         case 15:   *seg_ptr=*seg_ptr| 0x71;//F
		         }
	}
	else *seg_ptr=*seg_ptr| 0x40; // display a - as an error

}
