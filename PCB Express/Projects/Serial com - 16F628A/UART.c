/*  File:     UART.c
    Purpose:  To provide UART functionality for PIC uC
*/

#include "Includes.h"

void InitUART(void)
{
	TRISB2 = 0;   					// TX Pin
	TRISB1 = 1;   					// RX Pin
	
//    use:
//    /16 for BRGH = 1;
//    /64 for BRHG = 0;
	
	SPBRG = ((_XTAL_FREQ/16)/BAUDRATE) - 1;
	BRGH  = 1;                   	// Fast baudrate (div by 16)
	
//	SPBRG = ((_XTAL_FREQ/64)/BAUDRATE) - 1;
//	BRGH  = 0;                   	// Low baudrate	(div by 64)
	
	SYNC  = 0;						// Asynchronous
	SPEN  = 1;						// Enable serial port pins
	CREN  = 1;						// Enable reception
	SREN  = 0;						// No effect
	TXIE  = 0;						// Disable tx interrupts
	RCIE  = 1;						// Enable rx interrupts
	TX9   = 0;						// 8-bit transmission
	RX9   = 0;						// 8-bit reception
	TXEN  = 0;						// Reset transmitter
	TXEN  = 1;						// Enable the transmitter
}


void SendByteSerially(unsigned char Byte)  // Writes a character to the serial port
{	
	RA0=1;
	while(!TXIF);  // wait for previous transmission to finish
	TXREG = Byte;
	RA0=0;
}

unsigned char ReceiveByteSerially(void)   // Reads a character from the serial port
{

	RB4=1;	
	if(OERR) // If over run error, then reset the receiver
	{
		CREN = 0;
		CREN = 1;
	}
	
	while(!RCIF);  // Wait for transmission to receive
	
	RB4=0;
	return RCREG;
}

void SendStringSerially(const unsigned char* st)
{
	while(*st)
		SendByteSerially(*st++);
}