/*
 * DE1-SoC LT24 Example
 *
 * Displays a test pattern on the LT24
 * LCD using the LT24 bare metal driver.
 *
 *  Created on: 09 Feb 2018
 */

#include "DE1SoC_LT24/DE1SoC_LT24.h"
#include "HPS_Watchdog/HPS_Watchdog.h"
#include "HPS_usleep/HPS_usleep.h"
#include "seven_seg/seven_seg.h"
#include <math.h>
volatile int *seg1_ptr = (int *) 0xFF200020;
 volatile unsigned int *private_timer_load      = (unsigned int *) 0xFFFEC600;
    // ARM A9 Private Timer Value
    volatile unsigned int *private_timer_value     = (unsigned int *) 0xFFFEC604;
    // ARM A9 Private Timer Control
    volatile unsigned int *private_timer_control   = (unsigned int *) 0xFFFEC608;
    // ARM A9 Private Timer Interrupt
    volatile unsigned int *private_timer_interrupt = (unsigned int *) 0xFFFEC60C;
//Array Length Helper
#define ARRAY_LEN(arr) (sizeof(arr)/sizeof(arr[0]))

//Debugging Function (same as last lab)
#include <stdlib.h>
void exitOnFail(signed int status, signed int successStatus){
    if (status != successStatus) {
        exit((int)status); //Add breakpoint here to catch failure
    }
}
    // frame rate with bit-bang mode is 6.6 per second
   // with hardware optimisation enabled frame rate is 20 per second !
   // speed increased by 20/6.6 = 303%
// the previous calc. was at optimization level of -O0 and Total RO  Size (Code + RO Data 6.54kB
// at leve -o1  Total RO  Size (Code + RO Data) 5.53kB ,frame rate same as -O0 ,o1 better memory
// at level O2 Total RO  Size (Code + RO Datav 5.24kB) a little better size than o1
// frame-rate variable optimised away
//at o3 level max ,deafult for size the  Total RO  Size (Code + RO Datav 5.23kB) almost same as o2 and the frame rate is a little it better almost 21
// o3 with time ,code size is 620 kb ,and frame rate is 32 /s  ,the fastest ever!

// usind DDR memory ,no change in frame rate from when using fpga memory ,same 20 for o0 level
// Main Function
// =============
int main(void) {
    //Variables
	 unsigned short colours[6] = {LT24_RED,LT24_YELLOW,LT24_GREEN,LT24_CYAN,LT24_BLUE,LT24_MAGENTA};
	 volatile unsigned int  t_init=0;
	 volatile unsigned int t_final=0;
	 volatile unsigned int t_diff=0;
    unsigned int colourIdx = 0;
    //unsigned int f=225;  // timer freq = 225mhz ,225 milion tick in 1 sec
     volatile double tick_period=0.0044;    // period of timer tick in nano sec
     volatile double time_color_s=0;
     volatile double time_color_ns=0;
     unsigned long frame_rate=0;

    *private_timer_load    = 225000000;
	//Initialise the LCD Display.
    exitOnFail(
            LT24_initialise(0xFF200060,0xFF200080), //Initialise LCD
            LT24_SUCCESS);                          //Exit if not successful
    HPS_ResetWatchdog();
    //Display Internal Test Pattern
    exitOnFail(
            LT24_testPattern(), //Generate test pattern
            LT24_SUCCESS);      //Exit if not successful
    HPS_ResetWatchdog();
    //Wait a moment
    usleep(500000);
    HPS_ResetWatchdog();
    *private_timer_control   = (0<< 8) | (0 << 2) | (1 << 1) | (1 << 0); //auto ,start
    //Main Run Loop
    while (1) {
        //Set display to solid colour
    	t_init=*private_timer_value;
        LT24_clearDisplay(colours[colourIdx]);


        //Update Colour Index
        colourIdx++;
        if (colourIdx >= ARRAY_LEN(colours)) {
            colourIdx = 0;
        }
        t_final=*private_timer_value;
        t_diff=t_init-t_final; // number of ticks
        time_color_ns=t_diff * tick_period; // in nano sec
        time_color_s=time_color_ns/1000000; // in sec
        frame_rate=1/time_color_s;
        seg_dec(frame_rate,1,seg1_ptr);
          //Finally reset the watchdog.
        HPS_ResetWatchdog();
    }
}
