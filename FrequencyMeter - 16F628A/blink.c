#include "htc.h"

#include "lcd.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//#define _XTAL_FREQ    4000000
#define _XTAL_FREQ 20000000

// http://picguides.com/beginner/config.php


#define  testbit(var, bit)  ((var) & (1 <<(bit)))
#define  setbit(var, bit)   ((var) |= (1 << (bit)))
#define  clrbit(var, bit)   ((var) &= ~(1 << (bit)))

#define GATE RA0

int TMR1cnt = 0;

unsigned long TMR0cnt = 0;	//unsigned long       32 bits  0 to 4,294,967,295
unsigned long number =    0;	//unsigned long       32 bits  0 to 4,294,967,295

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

unsigned char band = 0;


const char qbytes[]  = "Q-Bytes World.";
const char version[] = "Hz Counter v1.1h";
const char noinput[] = "--->No input<---";

#define POSTSCALE    256
#define MAXSCALE       7  // This will be 10 with the MB506 connected

char buffer[10];

unsigned char  preScaleSelect = MAXSCALE;  // interger for the below array

unsigned short long preScaleValue  = 0;  // The shifted value
unsigned short long calcScaleValue  = 0;  // The shifted value

//                                  MAX MHz  ????  1     2     4     8    16    32     64  128   256   512  1024
//                           preScaleSelect        0     1     2     3     4     5      6    7     8     9    10
//                   PIC internal divide by        2     4     8    16    32    64    128  256     8     8     8
//                 MB506 external divide by        0     0     0     0     0     0     0     0    64   128   256
//                                             ===== ===== ===== ===== ===== ===== ===== ===== ===== ===== =====
//                          total divide by        2     4     8    16    32    64    128  256   512  1024  2048
//                                             ===== ===== ===== ===== ===== ===== ===== ===== ===== ===== =====
const unsigned char  prescaleInternalBits[11] =0b000,0b001,0b010,0b011,0b100,0b101,0b110,0b111,0b010,0b010,0b010; 
const unsigned char  prescaleInternalShift[11]=    1,    2,    3,    4,    5,    6,    7,    8,    3,    3,    3;
const unsigned char  prescaleExternalBits[11] = 0b00, 0b00, 0b00, 0b00, 0b00, 0b00, 0b00, 0b00, 0b01, 0b10, 0b11;
const unsigned char  prescaleExternalShift[11]=    0,    0,    0,    0,    0,    0,    0,    0,    6,    7,    8;

const char * const bands[8][2]  = {"EL", "VL", " L", " M", " H", "VH", "UH", "SH", "??"};


//http://fresh2refresh.com/c/c-type-casting/c-itoa-function/
extern char *   itol(char * buf, int val, int base); // signed int
extern char *   ultoa(char * buf, unsigned long val, int base); // signed int
extern char *   itoa(char * buf, int val, int base); // signed int
extern char *   utoa(char * buf, unsigned val, int base); // unsigned int

//__CONFIG(FOSC_INTOSCIO & MCLRE_OFF & BOREN_OFF & PWRTE_ON & WDTE_OFF & LVP_OFF);
//__CONFIG(FOSC_INTOSCIO & MCLRE_ON & BOREN_OFF & PWRTE_ON & WDTE_OFF & LVP_OFF & CP_OFF & CPD_OFF );
//__CONFIG(FOSC_EXTRCCLK & MCLRE_ON & BOREN_OFF & PWRTE_ON & WDTE_OFF & LVP_OFF & CP_OFF & CPD_OFF );
__CONFIG(FOSC_HS  & MCLRE_ON & BOREN_OFF & PWRTE_ON & WDTE_OFF & LVP_OFF & CP_OFF & CPD_OFF );


//__CONFIG(    FOSC_ECIO & MCLRE_ON & BOREN_OFF & PWRTE_OFF & WDTE_OFF & LVP_OFF);// Diable CLKOUT

// RB4 = input for pin press (toggle RB5) 
// RB5 = toggle based on input from RB4

// RA0 = interupt timer1


//const unsigned char FREQ = 10;
//const unsigned char SCALE = 1;
const unsigned char FREQ = 80;
const unsigned char SCALE = 10;
unsigned char findScale = 1; // first thing we do is find the scale.

void init(void){

//  PCONbits.OSCF = 0; // set internal oscillator to 0 = 48kHz
//    PCONbits.OSCF = 1; // set internal oscillator to 1 =  4mHz

    // by default all ports are set to inputs and analog functions are enabled

   CMCON = 0b00000111; // Turn the comparator off to enable digital IO

	// 1 = input
	// 0 = output
	
	TRISA = 0x10;  //	TRISA0 = 0; RISA1 = 0; TRISA2 = 0; TRISA3 = 0; TRISA4 = 1; TRISA5 = 0; TRISA6 = 0; TRISA7 = 0;
	TRISB = 0x00;

//  TRISA0 = 0; // set RA0 (pin 17) as output
//  TRISB0 = 0; // set RB5 (pin 17) as output
//  RB5 = 0; // we start with the LED off
}

// Frequency to measure
void initTimer0(void)
{
	INTCON	   = 0xA0;
	      	
// bits            7        - 0 = PORTB pull-ups enable
// bits             6       - 0 = RB0 falling edge
// bits              5      - 0 = internal clock, 1 = external RA4
// bits               4     - 0 = low to high edge
// bits                3    - 0 = prescale on timer 0  (1:x - x is the shift)
// bits                 210 - PRESCALE
//                      000 -   = Prescale  = 1:2
//                      001 -   = Prescale  = 1:4
//                      010 -   = Prescale  = 1:8
//                      011 -   = Prescale  = 1:16
//                      100 -   = Prescale  = 1:32
//                      101 -   = Prescale  = 1:64
//                      110 -   = Prescale  = 1:128
//                      111 -   = Prescale  = 1:256
//	OPTION_REG = 0b10100110;

	OPTION_REG = 0b10100000;
	OPTION_REG |= prescaleInternalBits[preScaleSelect];

//RB4 = !(!testbit(prescaleExternalBits[preScaleSelect],0));
//RB5 = !(!testbit(prescaleExternalBits[preScaleSelect],1));
//RB6 = !(!testbit(prescaleInternalBits[preScaleSelect],2));

	preScaleValue = (1 << prescaleInternalShift[preScaleSelect] << prescaleExternalShift[preScaleSelect]);

	TMR0	  = 0;
	TMR0cnt   = 0; // Clear the overflow
	number    = 0;

	// Timer0 is an 8 bit timer, select T0CS to be zero
	//OPTION_REG &= 0xc0;	// Make prescalar 1:2
	//T0IE = 1;	// Enable Timer0 interrupt
	GIE = 1;	// Enable global interrupts
}


	
void initTimer1(void)
{
//// 32.768K Crystal 	
//	TMR1H = 0xF0;  // Cleat timer1 register
//	TMR1L = 0x0A;  // Before enablining timer1  -- overflow @ 4096 cycles
////	TMR1L = 0x0B;  // Before enablining timer1  -- overflow @ 4096 cycles
//	//TMR1L = 0x06;  // Before enablining timer1  -- overflow @ 4096 cycles
//			
////              >>     T1CKPS - PreScale 
////                               00=1:1
////                               01=1:2
////                               10=1:4
////                               11=1:8
////                >    T1OSCEN - 0 = OSC off, 1 = Osc on
////                 >   T1Sync - 0 = Sync, 1= do not
////                  >  TMR1CS - 0=internal, 1=external 
////                   > TMR1ON - 0=off, 1=on 	
//	T1CON = 0b00001111;
//	TMR1IF = 0;		// Clear interrupt bit
////	TMR1IE = 1; 	// Enable Timer1 interrupt
//	PEIE = 1; 		// Enable peripheral interrupts
//	GIE = 1;		// Enable global interrupts	
//===================================================================

  T1CON	 = 0x31;
  TMR1IF = 0;
  
  // HS 20MHz with Capacitor
  TMR1H	 = 0x09;
  TMR1L	 = 0xAC;
  
  INTCON = 0xC0;  
}

void initTimer2(void)
{
//Timer2
//Prescaler 1:16; Postscaler 1:13; TMR2 Preload = 240; Actual Interrupt Time : 9.9866 ms	
  //T2CON	 = 0x66;
  T2CON	 = 0b01111111;
  
  PR2		 = 199;// Time period //PR2		 = 244;
  TMR2IE	 = 1;
//  INTCON	 = 0xC0;
}	
  		
void interrupt ISR(void)
{
	// ==========================================
	// Frequency to measure
	// Timer0 interrupt.
	// http://
	if (TMR0IF)  // If Timer0 interrupt
	{
		TMR0IF = 0;	// Clear the interrupt	

		// XTAL frequency is 20 MHz, so CPU frequency is 5MHz
		// RA1 toggles after every 256 cycles
		// So RA1 completes it cycle 2*256 = 512 cycles
		// A prescalar of 1:2 is applied.
		// A frequency of 5M/(512*2) = 4.9Khz on RA1
//		RA1 = ! RA1;	// Toggle RA1 pin		
//		T0IF = 0;		// Clear the interrupt		
		//Timer0
		//Prescaler 1:256; TMR0 Preload = 61; Actual Interrupt Time : 9.984 ms
    	//TMR0		 = 61;
		TMR0cnt++; 
		
			
		RB4 = !RB4;   		
	}
		
	// ==========================================
	// 32.768K Crystal
	// Timer1 interrupt.
	// http://saeedsolutions.blogspot.com/2014/03/pic16f628a-timer1-code-proteus.html
	if (TMR1IF) // If Timer1 Interrupt
	{
	//		TMR1H = 0xF0;  // Cleat timer1 register
	//		TMR1L = 0x00;  // before enablining timer1  -- overflow @ 4096 cycles
	//	
	//		TMR1IF = 0;	// Clear the interrupt		
	//		
	//		TMR1cnt++;
	//		
	////		RA0 = ~RA0;	
	
		// 4 MHZ 100 ms
	    //TMR1H	 = 0x3C;
	    //TMR1L	 = 0xB0;
	    
	    // 20 MHZ 100 ms    
	    TMR1H	 = 0x0B;
	    TMR1L	 = 0xDC;
	    
	    TMR1IF   = 0;
	    
//	    TMR1cnt++;	
	    RB5 = ~RB5;
	}	
	
  	if (TMR2IF)
	{ 
    	TMR2IF = 0;
    	//Enter your code here
  	    TMR1cnt++;
  	    PR2 = 244;// Time period	
	  	RB6 = !RB6; // Toggle RB6 pin
  	} 	
}	

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// The 32.768 time is divide by 4096.  
// 32768/4096 = 8 (0.125 seconds)
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
void doScale(){
			// We need 12 of the bits (2 to 2048)
			number = number >> (17);
			       
			TMR0cnt = 1;
			for (preScaleSelect =0; preScaleSelect <= MAXSCALE; preScaleSelect++)
			{
				if (TMR0cnt > number)
				{
					break;// found prescale
				}	
				TMR0cnt = TMR0cnt << 1;
			}
			if (preScaleSelect>MAXSCALE)
			{
				preScaleSelect=MAXSCALE;
			}
				
			preScaleValue  = (1 << prescaleInternalShift[preScaleSelect] << prescaleExternalShift[preScaleSelect]);
			calcScaleValue = preScaleSelect;
			
//			// Display preScaleSelect		
//			lcd_puts("p");			
//			ultoa(buffer,preScaleSelect,10);   // here 10 means decimal
//			lcd_puts(buffer);
//			lcd_puts("n");
//
//			ultoa(buffer,number,16);   // here 16 means hex
//			lcd_puts(buffer);
//			lcd_puts("  ");
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// Find the pre scale values
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
void doFrequency(){
TMR1cnt = TMR0cnt;	
			// LCD Line 1
			lcd_goto(0);	// select first line
			
			if (number != 0)
			{
				lcd_putnumber(number);
			}
			else
			{
				lcd_puts(&noinput);	
			}	
						
			// LCD Line 2
			lcd_goto(0x40);	// Select second line

			// -----Frequency bands (ranges)-----
			// Find Band (NO USE OF NUMBER OR TMR0cnt AFTER THIS SECTION						
			TMR0cnt = 3000;
			for (band = 0;band <= 7; band ++)
			{
				if (number < TMR0cnt)
				{
					break;  // Band found
				}	
				TMR0cnt *=10;
			}	
		

//
//			// Show DB vs Volts vs Watts
//			lcd_puts("mW/dB ");// part of UHF, VHF, ..F, ...
								
//			//Display shift	(multipy using preScaleValue)
			char** pBands = bands;	
			pBands += band;			
			lcd_puts(*pBands);
			lcd_puts("F");// part of UHF, VHF, ..F, ...
			
//			//Display scale
			lcd_puts(" 1/");
			ultoa(buffer,preScaleValue,10);   // here 10 means decimal
			lcd_puts(buffer);

			// Max prescale value
			preScaleSelect = MAXSCALE; // will be 11 with MB506
			preScaleValue  = (1 << prescaleInternalShift[preScaleSelect] << prescaleExternalShift[preScaleSelect]);
	
/////////////////////////////////////////////
//TMR0cnt = TMR1cnt;			
//			// Display number of overflows		
//			lcd_puts("o");
//			ultoa(buffer,TMR0cnt,10);   // here 10 means decimal
//			lcd_puts(buffer);
//		
//			//Display timer 0 count		
//			lcd_puts("t");
//			ultoa(buffer,TMR0,10);   // here 10 means decimal
//			lcd_puts(buffer);
			
/////////////////////////////////////////////
			// Last line
			lcd_puts("   ");	
}	

// ===============================================================
void timersON()
{
			GATE = 0; // gate LED OFF 

// This needs to be replaced with an external gate
TRISA = 0x10;  //	TRISA0 = 0; RISA1 = 0; TRISA2 = 0; TRISA3 = 0; TRISA4 = 1; TRISA5 = 0; TRISA6 = 0; TRISA7 = 0;

			initTimer0();	
			initTimer1();
			initTimer2();
			
			TMR1cnt = 0;
			
			TMR2IE = 1; // Esable Timer1 interrupt	
			TMR1IE = 1; 	// Enable Timer1 interrupt	
			T0IE = 1;	// Enable Timer0 interrupt
}		

// ===============================================================
void timersOFF()
{
// This needs to be replaced with an external gate
TRISA = 0x00;  //	TRISA0 = 0; RISA1 = 0; TRISA2 = 0; TRISA3 = 0; TRISA4 = 0; TRISA5 = 0; TRISA6 = 0; TRISA7 = 0;	
			T0IE = 0;	// Disable Timer0 interrupt
			TMR1IE = 0; // Disable Timer1 interrupt	
			TMR2IE = 0; // Disable Timer1 interrupt	
			GATE = 1; // gate LED ON 
			
			number = (preScaleValue * POSTSCALE * TMR0cnt) + (preScaleValue * TMR0);
			__delay_ms(10);
}


// ===============================================================
// ===============================================================
// ===============================================================
void main(void){
	    

	init();				// Initialize me.
	lcd_init();			// Initialize LCD
	
	timersON();

	lcd_puts(&qbytes);
	
	lcd_goto(0x40);	// Select second line
	lcd_puts(&version);
	
	__delay_ms(2000);	
	
	lcd_clear();	// Clear screen	
//-------------------------------------------------------------
	// Never ending loop
	while(1)  // repeat forever	
	{ 
		while (TMR1cnt < findScale) {} // Wait for timer count
		{
			timersOFF();

			if (findScale == SCALE)
			{
				doScale();
				findScale=FREQ;
			}
			else
			{
				doFrequency();
				findScale=SCALE;				
	
//		RB6 = ~RB6; // Toggle RA6 pin	
					
			}
			
			timersON();
		}	
	}	
}	


//			lcd_puts("B");
//			lcd_putdigit(band);	

			
////			// Display number of overflows		
//			lcd_puts("o");
//			ultoa(buffer,TMR0cnt,10);   // here 10 means decimal
//			lcd_puts(buffer);
//				
//			
//			//Display timer 0 count		
//			lcd_puts("t");
//			ultoa(buffer,TMR0,10);   // here 10 means decimal
//			lcd_puts(buffer);



//			// Display OPTION REG
//			lcd_puts("o");
//			ultoa(buffer,OPTION_REG,16);   // here 16 means hexadecimal
//			lcd_puts(buffer);
//			
			
//			lcd_puts(">");			
//			ultoa(buffer,calcScaleValue,16);   // here 10 means decimal
//			lcd_puts(buffer);
//			lcd_puts("<  ");	

			// Prepare for find preScale
//			findScale=1;