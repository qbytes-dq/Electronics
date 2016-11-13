/*

http://web.stanford.edu/class/ee281/handouts/lcd_tutorial.pdf

*/

/** I N C L U D E S **********************************************************/
#include <p18cxxx.h>
#include "HardwareProfile.h"
#include "GenericTypeDefs.h"
#include "delays.h"
#include "frequency.h"

#include "c:/MCC18/v3.47/h/xlcd.h"

const unsigned char FREQ = 100;
const unsigned char SCALE = 10;

unsigned char findScale;// = (unsigned char)SCALE; // first thing we do is find the scale.


/** V A R I A B L E S ********************************************************/
#pragma udata

#define GIG 1000000000
#define TEN         10

const char HZU[] = "    KKKMMMG";
const char HZ[]  = "Hz ";

const char noinput[] = "--->No input<---";

int loop=0;

unsigned char sig;
unsigned char digit;

unsigned long divBy = 0;

unsigned long longFrequency = 0;


char buffer9[10];
//// ==========================================================
//#pragma udata gpr1=0x100
//	BYTE large_action[4];
//	unsigned short large_value[4];
//#pragma udata  // return to default section
//
//#pragma udata usb6=0x0600
//	BYTE  large_stepSize[4];
//	BYTE  large_stepDec[4];			
//#pragma udata  // return to default section

//==============================================
#define POSTSCALE    256
#define MAXSCALE       7  // This will be 10 with the MB506 connected

unsigned char  preScaleSelect = MAXSCALE;  // interger for the below array

unsigned short long preScaleValue  = 1;  // The shifted value
unsigned short long calcScaleValue  = 1;  // The shifted value

//                                   MAX MHz  ????  5    10    20    40       16    32     64  128   256   512  1024
//                            preScaleSelect        0     1     2     3        4     5      6    7     8     9    10
//                    PIC internal divide by        1     2     4     8       32    64    128  256     8     8     8
//                  MB506 external divide by        0     0     0     0        0     0     0     0    64   128   256
//                                              ===== ===== ===== =====    ===== ===== ===== ===== ===== ===== =====
//                           total divide by        1     2     4     8       32    64    128  256   512  1024  2048
//                                              ===== ===== ===== =====    ===== ===== ===== ===== ===== ===== =====
const unsigned char  prescaleInternalBits[11] ={0b000,0b001,0b010,0b011,   0b100,0b101,0b110,0b111,0b010,0b010,0b010}; 
const unsigned char  prescaleInternalShift[11]={    1,    2,    3,    4,       5,    6,    7,    8,    3,    3,    3};
const unsigned char  prescaleExternalBits[11] ={ 0b00, 0b00, 0b00, 0b00,    0b00, 0b00, 0b00, 0b00, 0b01, 0b10, 0b11};
const unsigned char  prescaleExternalShift[11]={    0,    0,    0,    0,       0,    0,    0,    0,    6,    7,    8};

//http://fresh2refresh.com/c/c-type-casting/c-itoa-function/
//extern char *   itol(char * buf, int val, int base); // signed int
extern char *   ultoa(unsigned long val, char * buf); // signed int
extern char *   itoa(int val,char * buf); // signed int
extern char *   utoa(int val,char * buf); // signed int
//extern char *   utoa(char * buf, unsigned val, int base); // unsigned int



#define SHOWFREQ 
//==============================================
//==============================================
//==============================================
/** D E C L A R A T I O N S **************************************************/
#pragma code
	
unsigned char
doNumber(unsigned long number, unsigned short T1H, unsigned short T1L, int adc)
{		
		if (findScale == FREQ)
		{		
			longFrequency = (unsigned long)(((number * 256UL * 256UL) + (T1H * 256UL) + T1L)) * (unsigned long)preScaleValue;

			#if defined(SHOWFREQ)  // Regular view
				// Show Band
				WriteCmdXLCD(0x80);             // Line 1, pos 0
				Delay10KTCYx(0x10);		
				lcd_showband(longFrequency);
				
				// Show Scale
				WriteCmdXLCD(0x84);             // Line 1, pos 4
				Delay10KTCYx(0x10);
				lcd_showscale((unsigned long)preScaleValue);
				
				// Show DB
				WriteCmdXLCD(0x88);             // Line 1, pos 9
				Delay10KTCYx(0x10);
				lcd_showdb(adc);
				
//				// Show Frequency
//				WriteCmdXLCD(0xC0);             // Line 2
//				Delay10KTCYx(0x10);	
//				doFrequency(longFrequency);
			#else				// special view
				clearXLCD();					// Line 1
				WriteCmdXLCD(0x80);             // Line 1, pos 0
				Delay10KTCYx(0x10);				
			
				WriteDataXLCD('N');			
				WriteDataXLCD(':');			
				ultoa(number,buffer9);
				putsXLCD(buffer9);
				
				WriteDataXLCD(' ');			
				WriteDataXLCD('H');			
				WriteDataXLCD(':');			
				ultoa((unsigned long)T1H,buffer9);
				putsXLCD(buffer9);
			
				WriteDataXLCD(' ');			
				WriteDataXLCD('L');			
				WriteDataXLCD(':');			
				ultoa((unsigned long)T1L,buffer9);
				putsXLCD(buffer9);
				
				
				WriteCmdXLCD(0xC0);             // Line 2
				Delay10KTCYx(0x10);			
				WriteDataXLCD('C');			
				WriteDataXLCD(':');			
				ultoa((unsigned long)calcScaleValue,buffer9);
				putsXLCD(buffer9);
				
				WriteDataXLCD('S');			
				WriteDataXLCD(':');			
				ultoa((unsigned long)preScaleValue,buffer9);
				putsXLCD(buffer9);		
			#endif			
		
		mSW1_lo();
		mSW2_lo();
		mSW3_lo();
					
		if (m50MHz_get() == 0x00)
		{
			findScale = FREQ; //100
			preScaleValue = 1;
		}
		else
		{
			findScale = SCALE; //10
		}
	}
	else
	{
		// Show Frequency
//		WriteCmdXLCD(0x80);             // Line 1
//		Delay10KTCYx(0x10);	
//		doFrequency(longFrequency);

		Delay10KTCYx(0x10);	// Allow LED to be seen for second blick.
		
		longFrequency = (unsigned long)(((number * 256UL * 256UL) + (unsigned long)(T1H * 256UL) + T1L));// * 1ul;
		
		doScale(longFrequency);
		findScale = FREQ; //100
	}
			
	return findScale;
}


unsigned long TMR0cnt = 0;	//unsigned long       32 bits  0 to 4,294,967,295
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// The 32.768 time is divide by 4096.  
// 32768/4096 = 8 (0.125 seconds)
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
void doScale(unsigned long number){

			//calcScaleValue = number >> (18);
			calcScaleValue = number >> (19);

			// default to divide by           10
			// Anything above   536,870,912 is divided by 20
			// Anything above 1,072,741,824 is divided by 40
			// Anything above 2,147,483,648 is divided by 80
			

// divide by 10 not working, comment out and make it 20
//			if (calcScaleValue <= 1)
//			{	
//				preScaleValue = 10;
//				mSW1_hi();
//				mSW2_hi();
//				mSW3_hi();
//			}	
//			else
			if (calcScaleValue <= 2)  
			{	
				preScaleValue = 20;
				mSW1_lo();
				mSW2_hi();
				mSW3_hi();				
			}	
			else
			if (calcScaleValue <= 4)
			{	
				preScaleValue = 40;
				mSW1_lo();
				mSW2_lo();
				mSW3_hi();				
			}	
			else
			{
				preScaleValue = 80;
				mSW1_lo();
				mSW2_lo();
				mSW3_lo();				
			}	
}


void
doFrequency(unsigned long number)
{
	char displayHZ[] = {'.', '\0'};

	divBy  = GIG;
	sig = 0;

	if (number > 0)
		{
			// Loop 0 to 9 (total of 10 digits)
			for (loop=0; loop < TEN; loop++)
			{
				digit  = number / divBy;
				number = number % divBy;
				if (digit > 0 || sig != 0)
				{
					// We have a number to display
						while(BusyXLCD());
						WriteDataXLCD(0x30 + digit);
		
					sig++;
					if ( ((9 - loop)%3 == 0) && loop != 9)
					{
						while(BusyXLCD());
						putsXLCD(displayHZ);
						displayHZ[0] = ',';
					}	
				}
				else
				{
					// No digits yet,
					// We are filling in the blanks
					if ( ((9 - loop)%3 == 0) && loop != 9)
					{	
						while(BusyXLCD());			
						WriteDataXLCD(' ');	//WriteDataXLCD(0x20);
		
					}
					while(BusyXLCD());
					WriteDataXLCD(' ');
				}		
				divBy = divBy / TEN;
			}
			
			// ' KMG'
			if (sig>3)
			{
				displayHZ[0] = HZU[sig];
				while(BusyXLCD());
				putsXLCD(&displayHZ[0]);	
			}	
			
			// "Hz" 
			while(BusyXLCD());
			putsXLCD(&HZ);
		}
	else
		{
		putsXLCD(&noinput);
		}			
}

//// -----------------------------------------------------------------------------
//// -----------------------------------------------------------------------------
//// -----------------------------------------------------------------------------
//// Find the pre scale values
//// -----------------------------------------------------------------------------
//// -----------------------------------------------------------------------------
//// -----------------------------------------------------------------------------
//void doFrequency(){
//TMR1cnt = TMR0cnt;	
//			// LCD Line 1
//			lcd_goto(0);	// select first line
//			
//			if (number != 0)
//			{
//				lcd_putnumber(number);
//			}
//			else
//			{
//				lcd_puts(&noinput);	
//			}	
//						
//			// LCD Line 2
//			lcd_goto(0x40);	// Select second line
//
//			// -----Frequency bands (ranges)-----
//			// Find Band (NO USE OF NUMBER OR TMR0cnt AFTER THIS SECTION						
//			TMR0cnt = 3000;
//			for (band = 0;band <= 7; band ++)
//			{
//				if (number < TMR0cnt)
//				{
//					break;  // Band found
//				}	
//				TMR0cnt *=10;
//			}	
//		
//
////
////			// Show DB vs Volts vs Watts
////			lcd_puts("mW/dB ");// part of UHF, VHF, ..F, ...
//								
////			//Display shift	(multipy using preScaleValue)
//			char** pBands = bands;	
//			pBands += band;			
//			lcd_puts(*pBands);
//			lcd_puts("F");// part of UHF, VHF, ..F, ...
//			
////			//Display scale
//			lcd_puts(" 1/");
//			ultoa(buffer,preScaleValue,10);   // here 10 means decimal
//			lcd_puts(buffer);
//
//			// Max prescale value
//			preScaleSelect = MAXSCALE; // will be 11 with MB506
//			preScaleValue  = (1 << prescaleInternalShift[preScaleSelect] << prescaleExternalShift[preScaleSelect]);
//	
///////////////////////////////////////////////
////TMR0cnt = TMR1cnt;			
////			// Display number of overflows		
////			lcd_puts("o");
////			ultoa(buffer,TMR0cnt,10);   // here 10 means decimal
////			lcd_puts(buffer);
////		
////			//Display timer 0 count		
////			lcd_puts("t");
////			ultoa(buffer,TMR0,10);   // here 10 means decimal
////			lcd_puts(buffer);
//			
///////////////////////////////////////////////
//			// Last line
//			lcd_puts("   ");	
//}	

