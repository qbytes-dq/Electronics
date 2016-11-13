/*

http://web.stanford.edu/class/ee281/handouts/lcd_tutorial.pdf

*/

// Shows the band number as:  >#<
//#define SHOWTIMERS

#ifdef SHOWTIMERS	
	extern char *   itoa(int val , char * buf); // signed int
	char buffer2[10];
#endif

/** I N C L U D E S **********************************************************/
//#include <p18cxxx.h>
#include "C:\MCC18\v3.47\h\p18f2550.h"
#include "GenericTypeDefs.h"
#include "delays.h"
#include "timers.h"

#include "c:/MCC18/v3.47/h/xlcd.h"

/** V A R I A B L E S ********************************************************/
#pragma udata


//==============================================
//==============================================
//==============================================
/** D E C L A R A T I O N S **************************************************/
#pragma code
	
void
timer0Init()
{
	// ================================================	
//Timer0
//Prescaler 1:2; TMR0 Preload = 5536; Actual Interrupt Time : 10 ms
//  TMR0H	 = 0x15;
//  TMR0L	 = 0xA0;
  
  T0CON	 = 0x80;
//	T0CON	 = 0x00;
    TMR0H	 = 0x16;
  // 20 = 3.999.100
  // 1F = 3.999.270
  
  // 1C = 3.999.770
  // 1B = 3.999.961 
  // 1A = 4.000.115
  
  //*15 = 4.001.xxx
  //TMR0L	 = 0x00;   /// MEDIUM Tune
	    //TMR0L	 = 0x21;	  
	TMR0L	 = 0x18;
	    // TMR0L	 = 0x23;	  
	// 1B 60 = 3.999.993
	// 1B 58 = 4.000.008  * higher speeds good/low bad
	// 1B 40 = 4.000.016
	// 1B 30 =            
	// 1B 28 =            
	// 1B 24 = 4.000.025  ** 32,768 , 1M good here.
	// 1B 20 = 4.000.029 
	// 1B 00 = 4.000.070
	// 1A F0 = 4.000.060
	// 1A E0 = 4.000.070
	// 1A D0 = 4.000.081
	// 1A C0 = 4.000.100
	//*1A A0 = 4.000.115 
	// 1A 90 = 4.000.155
	
		    			  
//bit 7 TMR0ON: Timer0 On/Off Control bit
//1 = Enables Timer0
//0 = Stops Timer0
T0CONbits.TMR0ON=0;

//bit 6 T08BIT: Timer0 8-Bit/16-Bit Control bit
//1 = Timer0 is configured as an 8-bit timer/counter
//0 = Timer0 is configured as a 16-bit timer/counter
T0CONbits.T08BIT = 0;

//bit 5 T0CS: Timer0 Clock Source Select bit
//1 = Transition on T0CKI pin
//0 = Internal instruction cycle clock (CLKO)
T0CONbits.T0CS = 0;

//bit 4 T0SE: Timer0 Source Edge Select bit
//1 = Increment on high-to-low transition on T0CKI pin
//0 = Increment on low-to-high transition on T0CKI pin
T0CONbits.T0SE = 0;

//bit 3 PSA: Timer0 Prescaler Assignment bit
//1 = TImer0 prescaler is NOT assigned. Timer0 clock input bypasses prescaler.
//0 = Timer0 prescaler is assigned. Timer0 clock input comes from prescaler output.
T0CONbits.PSA = 0;

//bit 2-0 T0PS2:T0PS0: Timer0 Prescaler Select bits
//111 = 1:256 Prescale value
//110 = 1:128 Prescale value
//101 = 1:64 Prescale value
//100 = 1:32 Prescale value
//011 = 1:16 Prescale value
//010 = 1:8 Prescale value
//001 = 1:4 Prescale value
//000 = 1:2 Prescale value
T0CONbits.T0PS=0x000;
//T0CONbits.T0PS0=0;
//T0CONbits.T0PS1=0;
//T0CONbits.T0PS2=0;


   RCONbits.IPEN = 1;            // Enable interrupt priority 
   INTCONbits.PEIE = 1;          // interrupts allowed
   INTCONbits.GIE = 1;             
   INTCONbits.GIEH = 1;
   INTCONbits.GIEL = 1;

   INTCON2bits.TMR0IP = 1;       // interrupt priority 0
   INTCONbits.TMR0IE = 1;        // timer0 interrupt enabled
}
			
void
timer1Init()
{
//////Timer1
//////Prescaler 1:8; Actual Interrupt Time : ??
//Set up timer1 to interrupt every 1s at high priority.

//bit 7 RD16: 16-Bit Read/Write Mode Enable bit
//1 = Enables register read/write of Timer1 in one 16-bit operation
//0 = Enables register read/write of Timer1 in two 8-bit operations
T1CONbits.RD16    = 0;             

//bit 6 T1RUN: Timer1 System Clock Status bit
//1 = Device clock is derived from Timer1 oscillator
//0 = Device clock is derived from another source
T1CONbits.T1RUN = 0; // Device clock is derived from other oscillator

//bit 5-4 T1CKPS1:T1CKPS0: Timer1 Input Clock Prescale Select bits
//11 = 1:8 Prescale value
//10 = 1:4 Prescale value
//01 = 1:2 Prescale value
//00 = 1:1 Prescale value
//T1CONbits.T1CKPS1 = 1;             //prescale = 0 bit 5
//T1CONbits.T1CKPS0 = 1;             //prescale = 0 bit 4
T1CONbits.T1CKPS = 0b00;

//bit 3 T1OSCEN: Timer1 Oscillator Enable bit
//1 = Timer1 oscillator is enabled
//0 = Timer1 oscillator is shut off
//The oscillator inverter and feedback resistor are turned off to eliminate power drain.
T1CONbits.T1OSCEN = 0;             

//bit 2 T1SYNC: Timer1 External Clock Input Synchronization Select bit
//When TMR1CS = 1:
//1 = Do not synchronize external clock input
//0 = Synchronize external clock input
//When TMR1CS = 0:
//This bit is ignored. Timer1 uses the internal clock when TMR1CS = 0.
T1CONbits.T1SYNC  = 1;             

//bit 1 TMR1CS: Timer1 Clock Source Select bit
//1 = External clock from RC0/T1OSO/T13CKI pin (on the rising edge)
//0 = Internal clock (FOSC/4)
T1CONbits.TMR1CS  = 1;             

//bit 0 TMR1ON: Timer1 On bit
//1 = Enables Timer1
//0 = Stops Timer1
T1CONbits.TMR1ON  = 0;             
 									
IPR1bits.TMR1IP   = 0;             //TMR1 Overflow Interrupt Priority bit. Set at high priority if 1
PIE1bits.TMR1IE   = 1;             //TMR1 Overflow Interrupt Enable bit. Set to be enabled.
//WriteTimer1(0x8000);             //This sets bit 7 of the TMR1H register. 
                                   //Hence it takes 32768 cycles for timer1 to overflow the TMR1H register.
                                   //32768 cycles is 1 sec when using a 32.768KHz crystall.
}
		
void 
timersInit()
{
timer0Init();
timer1Init();
}	
	
void 
timersOff()
{
			T0CONbits.TMR0ON = 0;
			T1CONbits.TMR1ON = 0; 
}	

void
timersOn()
{
			timersInit();	
			
			//TMR0L=0;
			//TMR0H=0;
			TMR1L=0;
			TMR1H=0;			
			//TMR1 = 0x0000; // TMR1L = 0xFF - TMR1H = 0xFF						
			//TMR1L=0x0000;

			T0CONbits.TMR0ON = 1;
			T1CONbits.TMR1ON = 1; 			
			
//--------------------------	
#ifdef SHOWTIMERS	
	// Display band number		
	putcXLCD('>');			
	itoa(band,buffer2);
	putsXLCD(buffer2);
	putcXLCD('<');			
#endif
}



