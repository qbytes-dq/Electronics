#include "Includes.h"


unsigned char chr;

void interrupt ISR(void)
{
	if(RCIF)  // If UART Rx Interrupt
	{
			RA0=1;
		if(OERR) // If over run error, then reset the receiver
		{
			CREN = 0;
			CREN = 1;
		}
			RA0=0;
			RB7=1;
			chr=RCREG;
//chr++;
		SendByteSerially(chr);	// Echo back received char
			RB7=0;
	}
}