/*  Name     : main.c
 *  Purpose  : Main file for UART code for PIC16F628A.
 *  Author   : M.Saeed Yasin
 *  Date     : 19-09-13
 *  Website  : saeedsolutions.blogspot.com
 *  Revision : None
 */
#include "Includes.h"

// Config word
__CONFIG(FOSC_HS  & MCLRE_ON & BOREN_OFF & PWRTE_ON & WDTE_OFF & LVP_OFF & CP_OFF & CPD_OFF );
//__CONFIG(FOSC_HS & WDTE_OFF & PWRTE_ON & MCLRE_ON & BOREN_ON & LVP_OFF & CPD_OFF & CP_OFF);

// Main function
void main()
{	
	InitUART();							// Initialize UART
    
    SendStringSerially("Hello World!");	// Send string on UART

	GIE  = 1;  							// Enable global interrupts
    PEIE = 1;  							// Enable Peripheral Interrupts
    
TRISA0=0;    
   RA0=1;
TRISB4=0;    
   RB4=1;
	while(1)
	{
		// Do nothing, as Received character is echoed back in the ISR
		// If you decide to disable interrupts, then you can 
		// echo back characters by uncommenting the line below
		//SendByteSerially(ReceiveByteSerially());  //Echo Back
	}
}


