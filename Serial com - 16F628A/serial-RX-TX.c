#include "htc.h"

#include "pic.h"
#include "lcd.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define _XTAL_FREQ 20000000

__CONFIG(FOSC_HS  & MCLRE_ON & BOREN_OFF & PWRTE_ON & WDTE_OFF & LVP_OFF & CP_OFF & CPD_OFF );


//__CONFIG(    FOSC_ECIO & MCLRE_ON & BOREN_OFF & PWRTE_OFF & WDTE_OFF & LVP_OFF);// Diable CLKOUT


void init(void){

}


unsigned char inc ;
		
void interrupt ISR(void)
{	
	if ( RCIF ) {  // se dado chegou na USART
		TXREG = RCREG;  // pega dado recebido em RCREG e transfere 
		                // para TXREG para ser transmitido via USART
		TXEN = 1;  // habilita envio na USART
		lcd_puts(RCREG);
		
		  while(TXSTAbits.TRMT==0) // wait here till transmit complete
  			{
    			NOP();
  			}
  		inc++;
  		lcd_puts(inc);
	}	
}	


// ===============================================================
// ===============================================================
// ===============================================================
void main(void){
	    

	init();				// Initialize me.
	lcd_init();			// Initialize LCD
	
	lcd_puts("Serial");
	
	lcd_goto(0x40);	// Select second line
	lcd_puts("RX/TX");
	
	__delay_ms(2000);	
	
	lcd_clear();	// Clear screen	
//-------------------------------------------------------------
	TRISB1 = 1;
	TRISB2 = 0;
	
	RB2 = 1;
	
	// configura baud rate
//    cUART_data_flg=0;   // init data receive flag to zero (no data)
//    TRISCbits.TRISC7=1; //Make UART RX pin input
//    TRISCbits.TRISC6=0; //Make UART TX pin output
    SPBRGH  = 0x02;     //9600bps 20MHz Osc
    SPBRG   = 0x08;        

    CREN=1;   //1 = Enables receiver
    SPEN=1;   //1 = Serial port enabled (configures RX/DT and TX/CK pins as serial port pins)
    BRG16=1;//1 = 16-bit Baud Rate Generator – SPBRGH and SPBRG

    SYNC=0;  //0 = Asynchronous mode
    BRGH=1;  //1 = High speed 
    TXEN=1;  //1 = Transmit enabled

    IPEN = 1;  //enable Interrupt priority levels
    RCIP=0;     // EUSART Receive Interrupt Priority 0 = Low priority
    RCIE=1;     // 1 = Enables the EUSART receive interrupt
    GIEL = 1;//enable interrupts
    GIEH = 1;      
//-------------------------------------------------------------


     // ok, now some dummy code... (loop forever and ever and ever and ...)
     // just send some information every second
     do
     {

     } while(1);	
}	

