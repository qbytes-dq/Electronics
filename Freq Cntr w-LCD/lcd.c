/*
 *	LCD interface example
 *	Uses routines from delay.c
 *	This code will interface to a standard LCD controller
 *	like the Hitachi HD44780. It uses it in 4 bit mode, with
 *	the hardware connected as follows (the standard 14 pin 
 *	LCD connector is used):
 *	
 *	PORTA bit 2 is connected to the LCD RW input
 *	PORTA bit 3 is connected to the LCD RS input (register select)
 *	PORTA bit 4 is connected to the LCD EN bit (enable)
 *	PORTB bits 0-3 are connected to the LCD data bits 4-7 (high nibble)
 *	
 *	To use these routines, set up the port I/O (TRISA, TRISD) then
 *	call lcd_init(), then other routines as required.
 *	
 */


//http://www.newhavendisplay.com/specs/NHD-0216HZ-FL-YBW-C.pdf
//http://www.newhavendisplay.com/app_notes/ST7066U.pdf



#ifndef _XTAL_FREQ
 // Unless specified elsewhere, 4MHz system frequency is assumed
//#define _XTAL_FREQ 4000000
 #define _XTAL_FREQ 20000000
#endif


#include	<htc.h>
#include	"lcd.h"

#define LCD_EN RA1
#define	LCD_RW RA2
#define	LCD_RS RA3
//#define LCD_EN RA4

#define LCD_DATA	PORTB

#define	LCD_STROBE() ((LCD_EN = 1), (LCD_EN=0))

unsigned long divBy =       0;

#define GIG 1000000000
#define TEN         10

const char HZ[] = "    KKKMMMG";


unsigned char sig;
unsigned char digit;
	
/* initialise the LCD - put into 4 bit mode */
void
lcd_init()
{
//	char init_value;

//daq	ADCON1 = 0x06;	// Disable analog pins on PORTA

//	init_value = 0x3;
//	TRISA=0;
//	TRISB=0;
//	LCD_RS = 0;
//	LCD_EN = 0;
//	LCD_RW = 0;

RB7 = 1; // LCB Power 
	
	__delay_ms(150);	// wait 15mSec after power applied,
//	LCD_DATA	 = init_value;
	LCD_DATA	 = 0x3 | (PORTB & 0xF0);
	LCD_STROBE();
	__delay_ms(5);
	LCD_STROBE();
	__delay_us(200);
	LCD_STROBE();
	__delay_us(200);
	LCD_DATA = 2 | (PORTB & 0xF0);;	// Four bit mode
	LCD_STROBE();

	lcd_write(0x28); // Set interface length
	//lcd_write(0xF); // Display On, Cursor On, Cursor Blink
	lcd_write(0b1100); // Display On, Cursor On, Cursor Blink
	lcd_clear();	// Clear screen
	lcd_write(0x6); // Set entry Mode
}


/* write a byte to the LCD in 4 bit mode */
void
lcd_write(unsigned char c)
{
	__delay_us(40);
	LCD_DATA = ( (( c >> 4 ) & 0x0F ) | (PORTB & 0xF0) );
	LCD_STROBE();
	LCD_DATA = ( ( c & 0x0F ) | (PORTB & 0xF0) );
	LCD_STROBE();
}

/*
 * 	Clear and home the LCD
 */
void
lcd_clear(void)
{
	LCD_RS = 0;
	lcd_write(0x1);
	__delay_ms(2);
}

/* write a string of chars to the LCD */
void
lcd_puts(const char * s)
{
	LCD_RS = 1;	// write characters
	while(*s)
		lcd_write(*s++);
}

/* write one character to the LCD */
void
lcd_putch(char c)
{
	LCD_RS = 1;	// write characters
	lcd_write( c );
}


/*
 * Go to the specified position
 */
void
lcd_goto(unsigned char pos)
{
	LCD_RS = 0;
	lcd_write(0x80+pos);
}

/* put a number on the lcd */
// input s/b 0 to 9
void
lcd_putdigit(unsigned char c)
{ 
	LCD_RS = 1;	// write characters
	lcd_write( 0x30 + c );
}
	
void
lcd_putnumber(unsigned long number)
{
	char displayHZ[] = {'.', '\0'};
	
	divBy  = GIG;
	sig = 0;

	// Loop 0 to 9 (total of 10 digits)
	for (int loop=0; loop < TEN; loop++)
	{
		digit  = number / divBy;
		number = number % divBy;
		if (digit > 0 || sig != 0)
		{
			// We have a number to display
			lcd_putdigit(digit);
			sig++;
			if ( ((9 - loop)%3 == 0) && loop != 9)
			{
				lcd_puts(displayHZ);
				displayHZ[0] = ',';
			}	
		}
		else
		{
			// No digits yet,
			// We are filling in the blanks
			if ( ((9 - loop)%3 == 0) && loop != 9)
			{			
				lcd_puts(" ");
			}
			lcd_puts(" ");
		}		
		divBy = divBy / TEN;
	}
	
	displayHZ[0] = HZ[sig];
	lcd_puts(&displayHZ[0]);
	lcd_puts("Hz");
}		