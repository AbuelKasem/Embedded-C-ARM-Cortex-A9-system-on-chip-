/*
 * This program provides a non-blocking example of code for the ARM A9 Private Timer
 */
//Include ResetWDT() macro:
#include "HPS_Watchdog/HPS_Watchdog.h"
//Main Function
int main(void) {
    /* Pointers to peripherals */
    // Red LEDs base address


    volatile unsigned int *LEDR_ptr = (unsigned int *) 0xFF200000;
    // ARM A9 Private Timer Load
    volatile unsigned int *private_timer_load      = (unsigned int *) 0xFFFEC600;
    // ARM A9 Private Timer Value
    volatile unsigned int *private_timer_value     = (unsigned int *) 0xFFFEC604;
    // ARM A9 Private Timer Control
    volatile unsigned int *private_timer_control   = (unsigned int *) 0xFFFEC608;
    // ARM A9 Private Timer Interrupt
    volatile unsigned int *private_timer_interrupt = (unsigned int *) 0xFFFEC60C;
    /* Local Variables */ 
    //unsigned int lastBlinkTimerValue = *private_timer_value;
    //const unsigned int blinkPeriod = 225000000;
    /* Initialisation *
     *
     */
    int i=0,t_count=10;
    unsigned int currentTimerValue=0;
    unsigned int blink_periods[10]={1000000,5000000,10000000,15000000,20000000,25000000,50000000,100000000,150000000.200000000};
    unsigned int lastBlinkTimerValue[10]= {0,0,0,0,0,0,0,0,0,0};
    unsigned int led_value=0;
    // Set initial value of LEDs
    *LEDR_ptr = 0x00;
    // Configure the ARM Private Timer
    // Set the "Load" value of the timer to max value:
    *private_timer_load    = 0xFFFFFFFF;
    // Set the "Prescaler" value to 0, Enable the timer (E = 1), Set Automatic reload
    // on overflow (A = 1), and disable ISR (I = 0)
    *private_timer_control   = (0 << 8) | (0 << 2) | (1 << 1) | (1 << 0);

    /* Main Run Loop */
    while(1) { 
for(i=0;i<t_count;i++) {
        // Read the current time
        currentTimerValue = *private_timer_value;

        // Check if it is time to blink

        if ((lastBlinkTimerValue[i] - currentTimerValue) >= blink_periods[i]) {
            // When the difference between the last time and current time is greater
            // than the required blink period. We use subtraction to prevent glitches
            // when the timer value overflows – e.g. (0x10 – 0xFFFFFFFF)%32 = 0x11.
            // If the time elapsed is enough, perform our actions.
        	led_value=*LEDR_ptr;
        	led_value= led_value ^(1<<i);
           *LEDR_ptr = led_value; // toggle led0
            // To avoid accumulation errors, we make sure to mark the last time
            // the task was run as when we expected to run it. Counter is going
            // down, so subtract the interval from the last time.
           lastBlinkTimerValue[i] = lastBlinkTimerValue[i] - blink_periods[i];
        }

      /*  if ((lastBlinkTimerValue[1] - currentTimerValue) >= blink_periods[1]) {
                	led_value=*LEDR_ptr;
                	led_value= led_value ^(1<<9);
                   *LEDR_ptr =  led_value; // toggle led1
                   lastBlinkTimerValue[1] = lastBlinkTimerValue[1]  - blink_periods[1];
                }
        if ((lastBlinkTimerValue[2] - currentTimerValue) >= blink_periods[2]) {
                       	led_value=*LEDR_ptr;
                       	led_value= led_value ^(1<<7);
                          *LEDR_ptr = led_value; // toggle led2
                          lastBlinkTimerValue[2] = lastBlinkTimerValue[2] - blink_periods[2];
                       }
        if ((lastBlinkTimerValue[0] - currentTimerValue) >= blink_periods[0]) {
                               	led_value=*LEDR_ptr;
                               	led_value= led_value ^(1<<6);
                                  *LEDR_ptr = led_value; // toggle led3
                                  lastBlinkTimerValue[0] = lastBlinkTimerValue[0] - blink_periods[0];
                               } */

        // Next, make sure we clear the private timer interrupt flag if it is set
        if (*private_timer_interrupt & 0x1) {
            // If the timer interrupt flag is set, clear the flag
            *private_timer_interrupt = 0x1;
        }
    }
        // Finally, reset the watchdog timer. We can use the ResetWDT() macro.
        ResetWDT(); // This basically writes 0x76 to the watchdog reset register.
    }
}


