/*
 * DE1-SoC Audio Example
 *
 * Generates a sinusoidal tone waveform
 * Writes stereo audio to the CODEC (LINE OUT)
 *
 *  Created on: 03 Feb 2018
 */

#include "DE1SoC_WM8731/DE1SoC_WM8731.h"
#include "HPS_Watchdog/HPS_Watchdog.h"

//Include Floating Point Math Libraries
#include <math.h>
 volatile unsigned int *private_timer_load      = (unsigned int *) 0xFFFEC600;
    // ARM A9 Private Timer Value
    volatile unsigned int *private_timer_value     = (unsigned int *) 0xFFFEC604;
    // ARM A9 Private Timer Control
    volatile unsigned int *private_timer_control   = (unsigned int *) 0xFFFEC608;
    // ARM A9 Private Timer Interrupt
    volatile unsigned int *private_timer_interrupt = (unsigned int *) 0xFFFEC60C;

//Debugging Function (same as last lab)
#include <stdlib.h>
void exitOnFail(signed int status, signed int successStatus){
    if (status != successStatus) {
        exit((int)status); //Add breakpoint here to catch failure
    }
}

//Define some useful constants
#define F_SAMPLE 48000.0        //Sampling rate of WM8731 Codec (Do not change)
#define PI2      6.28318530718  //2 x Pi      (Apple or Peach?)

//
// Main Function
// =============
int main(void) {
    //Pointers
    volatile unsigned int*  LEDR_ptr  = (unsigned int *) 0xFF200000; // Red LEDs base address
    volatile unsigned char* fifospace_ptr;
    volatile unsigned int*  audio_left_ptr;
    volatile unsigned int*  audio_right_ptr;
    volatile unsigned int t_init;
    volatile unsigned int t_final;
    volatile unsigned int t_diff;
    //timer

    //Variables
    //Phase Accumulator
    double phase = 0.0;  // Phase accumulator
    double inc   = 0.0;  // Phase increment
    double ampl  = 0.0;  // Tone amplitude (i.e. volume)
    signed int audio_sample = 0;
    *private_timer_load      = 225000000;
    t_init=0;
    t_final=0;
    //Initialise the Audio Codec.
    exitOnFail(
            WM8731_initialise(0xFF203040),  //Initialise Audio Codec
            WM8731_SUCCESS);                //Exit if not successful
    //Clear both FIFOs
    WM8731_clearFIFO(true,true);
    //Grab the FIFO Space and Audio Channel Pointers
    fifospace_ptr = WM8731_getFIFOSpacePtr();
    audio_left_ptr = WM8731_getLeftFIFOPtr();
    audio_right_ptr = WM8731_getRightFIFOPtr();
    //Initialise Phase Accumulator
    inc   = 440.0 * PI2 / F_SAMPLE;  // Calculate the phase increment based on desired frequency - e.g. 440Hz
    ampl  = (3*8388608.0);               // Pick desired amplitude (e.g. 2^23). WARNING: If too high = deafening!
    phase = 0.0;
    // Primary function while loop
    *private_timer_control   = (0<< 8) | (0 << 2) | (1 << 1) | (1 << 0); //dis. auto ,start
    while (1) {
        //Always check the FIFO Space before writing or reading left/right channel pointers
        if ((fifospace_ptr[2] > 0) && (fifospace_ptr[3] > 0)) {
            //If there is space in the write FIFO for both channels:
            //Increment the phase

        	t_init=*private_timer_value;
            phase = phase + inc;
            //Ensure phase is wrapped to range 0 to 2Pi (range of sin function)
            while (phase >= PI2) {
                phase = phase - PI2;
            }
            // Calculate next sample of the output tone.
            audio_sample = (signed int)( ampl * sin( phase ) );
            // Output tone to left and right channels.
            *audio_left_ptr = audio_sample;
            *audio_right_ptr = audio_sample;
            t_final=*private_timer_value;
            t_diff=t_init-t_final;
           // t_final=*private_timer_value;
        }
        //Debugging - display FIFO space on red LEDs.
        *LEDR_ptr = fifospace_ptr[2];  // Output 'WSRC' register to the red LEDs.
        //Finally reset the watchdog.
        HPS_ResetWatchdog();
    }
}
