/*
 * This program shows how to create a function pointer
 */
#include "HPS_Watchdog/HPS_Watchdog.h"
#include "seven_seg/seven_seg.h"
 volatile int *seg1_ptr = (int *) 0xFF200020;
   volatile int *seg2_ptr = (int *) 0xFF200030;

//Define a new data type for a function which takes two int parameters
//and returns an int.
typedef int (*TaskFunction)(int, int);

//Create a couple of functions which match our function data type
int aFunction(int a, int b){
    //<-- Set a break point here
    int c = a + b;
    return c;
}
int anotherFunc(int a, int b) {
    //<-- Set a break point here
    int c = a * b;
    return c;
}

//Main Function
int main(void) {
    //Create a pointer to aFunction
    TaskFunction aPointer = &aFunction; //Try changing to &anotherFunc
    TaskFunction aPointer1 = &anotherFunc;
    //Create some inputs
    int a = 4;
    int b = 6;
    int c,d;
    //Try calling the function



    //Do nothing.
    while(1) {
    	d = aPointer1(a, b);
    	 seg_dec(d,1,seg1_ptr);
    	 c = aPointer(a, b);
    	     seg_dec(c,3,seg2_ptr);
        HPS_ResetWatchdog();
    }
}
