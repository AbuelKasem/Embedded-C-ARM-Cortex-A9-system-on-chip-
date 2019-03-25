/*
 * mai.c
 *
 *  Created on: Feb 23, 2019
 *      Author: Kasem
 */

#include "HPS_Watchdog/HPS_Watchdog.h"
int Disp(int i)
{
  int hex_dis[16] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x5F, 0x07, 0x7F, 0x6F, 0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71};
  return hex_dis[i];
}

int main()
{
  int x=0;
  volatile unsigned int *Seg_0 = (unsigned int *) 0xFF200020;
  while(1)
  {
    *Seg_0 = Disp(x);
	if (x>15) {
	x=0;
	x++; }
	else x++;

	 HPS_ResetWatchdog();
  }
}
