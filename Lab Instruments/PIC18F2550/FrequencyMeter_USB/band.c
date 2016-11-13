/*

http://web.stanford.edu/class/ee281/handouts/lcd_tutorial.pdf

*/

/* Frequency bands (ranges)
0 - ELF =      >    3k
1 - VLF =   3K -   30K
2 -  LF =  30K -  300K
3 -  MF = 300K - 3000K
4 -  HF =   3M -   30M
------------------  My gap 66-100 MHz
5 - VHF =  30M -  300M
6 - UHF = 300M - 3000M
7 - SHF     3G < 
*/

// Shows the band number as:  >#<
//#define SHOWBAND

#ifdef SHOWBAND	
	extern char *   itoa(int val , char * buf); // signed int
	char buffer1[10];
#endif

/** I N C L U D E S **********************************************************/
#include <p18cxxx.h>
#include "GenericTypeDefs.h"
#include "delays.h"
#include "band.h"

#include "c:/MCC18/v3.47/h/xlcd.h"

/** V A R I A B L E S ********************************************************/
#pragma udata

unsigned long numberBand;
unsigned char band;

const char bands1[]  = "EV   VUS?";
const char bands2[]  = "LLLMHHHH?";
const char bandF[]   = "F ";

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

//==============================================
//==============================================
//==============================================
/** D E C L A R A T I O N S **************************************************/
#pragma code
	
void
lcd_showband(unsigned long number)
{
	char displayB[] = {'.', '\0'};

	// -----Frequency bands (ranges)-----
	// Find Band			
	numberBand = 3000;
	for (band = 0;band <= 7; band ++)
	{
		if (number < numberBand)
		{
			break;  // Band found
		}	
		numberBand *=10;
	}

	displayB[0]=bands1[band];
	while(BusyXLCD());
	putsXLCD(&displayB[0]);

	displayB[0]=bands2[band];
	while(BusyXLCD());
	putsXLCD(&displayB[0]);			
	
	while(BusyXLCD());				
	putsXLCD(&bandF);
						
//--------------------------	
#ifdef SHOWBAND	
	// Display band number		
	putcXLCD('>');			
	itoa(band,buffer1);
	putsXLCD(buffer1);
	putcXLCD('<');			
#endif
}
