/*

http://web.stanford.edu/class/ee281/handouts/lcd_tutorial.pdf

*/
	
extern char *   itoa(int val , char * buf); // signed int
char buffer3[4];


/** I N C L U D E S **********************************************************/
#include <p18cxxx.h>
#include "GenericTypeDefs.h"
#include "delays.h"
#include "scale.h"

#include "c:/MCC18/v3.47/h/xlcd.h"

/** V A R I A B L E S ********************************************************/
#pragma udata

unsigned char len;
//==============================================
//==============================================
//==============================================
/** D E C L A R A T I O N S **************************************************/
#pragma code
	
void
lcd_showscale(unsigned long number)
{
	char displayB[] = {'1', '/', '\0'};
		


	while(BusyXLCD());
	putsXLCD(&displayB[0]);
		
	//--------------------------	
	// Display scale		
			
	itoa(number,buffer3);
	putsXLCD(buffer3);

	for( len=0 ; len < sizeof(buffer3); len++)
	   if(buffer3[len] == '\0') 
	   		break;
	   		
	len = sizeof(buffer3) - len;
	
	for(  ; len>0; len--)
		putcXLCD(' ');
		
	//#ifdef SHOWSCALE	
	//	putcXLCD('>');
	//len = sizeof(buffer3);
	//	itoa(len,buffer3);
	//	putsXLCD(buffer3);
	//	
	//	putcXLCD('<');			
	//#endif
}
