/*

http://web.stanford.edu/class/ee281/handouts/lcd_tutorial.pdf

*/

#define SHOW_DBM
//#define SHOW_VOLTS


#include <stdio.h>
#include <stdlib.h>


	
extern char *   itoa(int val , char * buf); // signed int
char buffer2[10];

int i;
//int i1;
//int i25 = 25;
//int i3;
double num1;
double num2;
double num3;

double num1000 = 1000;



/** I N C L U D E S **********************************************************/
#include <p18cxxx.h>
#include "GenericTypeDefs.h"
#include "delays.h"
#include "db.h"

#include "c:/MCC18/v3.47/h/xlcd.h"

/** V A R I A B L E S ********************************************************/
#pragma udata


//const char db[]   = "mW/dB ";
//const char db[]   = "-09dB ";
const char db[]   = "dBm ";
//http://www.rapidtables.com/convert/power/mW_to_dBm.htm


//float fval; 

  
#define MAX 10000
//#define DIGS         4
int DIGS   =      4;
#define TEN         10
int loop1=0;

unsigned char pos1;
unsigned char digit1;
unsigned long divBy1 = 0;

//==============================================
//==============================================
//==============================================
/** D E C L A R A T I O N S **************************************************/
#pragma code
	

// Assumes value is in millavolts   (2048 is  2.048V)
// Assumes max value in millavolts (99999 is 99.999V)

void
doVolt(long number)
{
	char displayHZ[] = {'.', '\0'};

	if (number < 0)
	{
		WriteDataXLCD('-');
		number *= -1;
	}
	else
	{
		WriteDataXLCD(' ');
	}		

	divBy1 = MAX;

	{
		// Loop 0 to 5 (total of 6 digits)
		for (loop1=0; loop1 < DIGS; loop1++)
		{
			digit1  = number / divBy1;
			number = number % divBy1;

		// We have a number to display
			while(BusyXLCD());
			WriteDataXLCD(0x30 + digit1);

			if (loop1 == 1) // put in period
			{
				while(BusyXLCD());
				putsXLCD(displayHZ);
			}
		
		divBy1 = divBy1 / TEN;				
		}			
	}
}


   long round(double x) {
//      assert(x >= LONG_MIN-0.5);
//      assert(x <= LONG_MAX+0.5);
      if (x >= 0)
         return (long) (x+0.5);
      return (long) (x-0.5);
   }
   

void
lcd_showdb(int adc)
{
//------------------------
// DBm to Vrms	
//	sqrt((50 * 0.001) * (10 ^ (-16 * 0.1))) = 0.03543928915419706969524388216846
//  sqrt((50 * 0.001) * (10 ^ ( 16 * 0.1))) = 1.4108635131604638154766402585965
//--------------------------	
// Vrms to DBm
// 10 * log((0.0350 * 0.0350) / (50 * 0.001)) = -16.108339156354675337893063775392
// 10 * log((0.0009 * 0.0009) / (50 * 0.001)) = -47.90484985457369055606149492255
// 10 * log((0.3330 * 0.3330) / (50 * 0.001)) =   3.4591846267662093801075188682321
// 10 * log((0.7100 * 0.7100) / (50 * 0.001)) =  10.035466931021317673993977647954
//--------------------------
#ifdef SHOW_DBM	

	//num1 = (double)(round((adc*2.048)/10));
//	num1 = (double)(round((adc*2.180)/10));
//	num1 = (double)(round((adc*2.048)));
//	num1 = (double)(round((adc*5.105)));

DIGS = 4;
	num1 = (double)(round((adc*4.975)));
	num2 = (double)num1/num1000;
	//num3 = (num2 / 0.025) - 74;
	
	
	//=(1.975-1.94)/0.02
	num3 = (double)((num2 - 1.94) / 0.020) + 0.005;//0.005 for rounding
	
	doVolt((int)(num3*1000));
	
//	WriteDataXLCD('D');

			// "dBm" 
			while(BusyXLCD());
			putsXLCD(&db);
			
//#endif

//--------------------------	
//#ifdef SHOW_VOLTS	
WriteCmdXLCD(0xC0);             // Line 2
Delay10KTCYx(0x10);	
//	i = ((long)(adc) * 2048)/1000;
//	i = ((long)(adc) * 2180)/1000;
//	doVolt(i);

DIGS = 6;
	doVolt(num2*1000);
	WriteDataXLCD('V');
#endif


}
