#include "Includes.h"


unsigned char chr;

void interrupt ISR(void)
{
	if(RCIF)  // If UART Rx Interrupt
	{
		if(OERR) // If over run error, then reset the receiver
		{
			CREN = 0;
			CREN = 1;
		}

chr = ReceiveByteSerially();

		SendByteSerially(chr);	// Echo back received char

	}
}