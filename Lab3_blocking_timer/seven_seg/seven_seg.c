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




void seg_dec(int n,int pair,int *ptr) {
	int shft=0;
	int dig1=0,dig2=0,dig3=0,temp=0;
	if (pair==1) shft=0;
	else if(pair==2) shft=16;
	else if(pair==3) {shft=0;
	ptr= (int *)0xFF200030;
	}


	if (n<=9) {dig1=n;
	}

	else if ((n>9) && (n<=99)){ dig1=n%10;
	dig2=n/10;}
	else if (n>99) {
	dig3=n/100;
	temp=n%100;
	dig1=temp%10;
		dig2=temp/10;
	}
	switch(dig1) {
					 case 0:   *ptr=*ptr| 0x3F;  //0
			         break;
			         case 1:   *ptr=*ptr| 0x06;  //1
			         break;
			         case 2:   *ptr=*ptr| 0x5B;//2
			         break;
			         case 3:  *ptr=*ptr|0x4F;//3
			         break;
			         case 4:   *ptr=*ptr| 0x66;//4
			         break;
			         case 5:   *ptr=*ptr| 0x6D;//5
			         break;
			         case 6:   *ptr=*ptr| 0x5F;//6
			         break;
			         case 7:   *ptr=*ptr|0x07;//7
			         break;
			         case 8:   *ptr=*ptr|0x7F;//8
			         break;
			         case 9:   *ptr=*ptr| 0x6F;//9
			         break;
			         }
	switch(dig2) {
					 case 0:     *ptr=*ptr| 0x3F00;  //0
			         break;
			         case 1:   *ptr=*ptr| 0x0600;  //1
			         break;
			         case 2:    *ptr=*ptr| 0x5B00;//2
			         break;
			         case 3:    *ptr=*ptr| 0x4F00;//3
			         break;
			         case 4:    *ptr=*ptr| 0x6600;//4
			         break;
			         case 5:    *ptr=*ptr|0x6D00;//5
			         break;
			         case 6:    *ptr=*ptr| 0x5F00;//6
			         break;
			         case 7:    *ptr=*ptr| 0x0700;//7
			         break;
			         case 8:    *ptr=*ptr| 0x7F00;//8
			         break;
			         case 9:    *ptr=*ptr| 0x6F00;//9
			         break;

		         }

	*ptr=*ptr<<shft;

	/*switch(dig3) {
					 case 0:    *ptr=*ptr| (0x3F<<shft);  //0
			         break;
			         case 1:   *ptr=*ptr| (0x06<<shft);  //1
			         break;
			         case 2:   *ptr=*ptr| (0x5B<<shft);//2
			         break;
			         case 3:  *ptr=*ptr| (0x4F<<shft);//3
			         break;
			         case 4:   *ptr=*ptr| (0x66<<shft);//4
			         break;
			         case 5:   *ptr=*ptr| (0x6D<<shft);//5
			         break;
			         case 6:   *ptr=*ptr|(0x5F<<shft);//6
			         break;
			         case 7:   *ptr=*ptr|(0x07<<shft);//7
			         break;
			         case 8:   *ptr=*ptr| (0x7F<<shft);//8
			         break;
			         case 9:   *ptr=*ptr| (0x6F<<shft);//9
			         break;
			         } */
}

void seg_hex(int x,int seg,int *ptr){
int shft;
    switch (seg){
    case 0: shft=0;
    break;
    case 1: shft=8;
    break;
    case 2: shft=16;
    break;
    case 3: shft=24;
    break;

    }
	if ((x<=15) && (x>=0)){


	switch(x) {
		         case 0:    *ptr=*ptr| (0x3F<<shft);  //0
		         break;
		         case 1:   *ptr=*ptr| (0x06<<shft);  //1
		         break;
		         case 2:   *ptr=*ptr| (0x5B<<shft);//2
		         break;
		         case 3:  *ptr=*ptr| (0x4F<<shft);//3
		         break;
		         case 4:   *ptr=*ptr| (0x66<<shft);//4
		         break;
		         case 5:   *ptr=*ptr| (0x6D<<shft);//5
		         break;
		         case 6:   *ptr=*ptr|(0x5F<<shft);//6
		         break;
		         case 7:   *ptr=*ptr|(0x07<<shft);//7
		         break;
		         case 8:   *ptr=*ptr| (0x7F<<shft);//8
		         break;
		         case 9:   *ptr=*ptr| (0x6F<<shft);//9
		         break;
		         case 10:   *ptr=*ptr| (0x77<<shft);//A
		         break;
		         case 11:   *ptr=*ptr| (0x7F<<shft);//B
		         break;
		         case 12:   *ptr=*ptr| (0x39<<shft);//C
		         break;
		         case 13:   *ptr=*ptr|(0x3F<<shft);//D
		         break;
		         case 14:  *ptr=*ptr| (0x79<<shft);//E
		         break;
		         case 15:   *ptr=*ptr| (0x71<<shft);//F
		         }
	}
	else *ptr=*ptr| 0x40; // display a - as an error

}
