//#include <p18f4550.h>
//#include <pic.h>
#include <p18cxxx.h>
#include <delays.h>
#include <portb.h>//functions to control pull-up resistors and interrupts

#include <pconfig.h>
#include <delays.h>

unsigned char player_addr = 0x00;

void EEPROM_putc(unsigned char address, unsigned char data)
{
	unsigned char INTCON_SAVE;

	EEADR  = address;
	EEDATA = data;

	EECON1bits.EEPGD= 0; // 0 = Access data EEPROM memory
	EECON1bits.CFGS = 0; // 0 = Access Flash program or DATA EEPROM memory
	EECON1bits.WREN = 1; // enable writes to internal EEPROM

	INTCON_SAVE=INTCON; // Save INTCON register contants
	INTCON=0; 			// Disable interrupts, Next two lines SHOULD run without interrupts
	
	EECON2=0x55;		// Required sequence for write to internal EEPROM
	EECON2=0xaa;		// Required sequence for write to internal EEPROM

	EECON1bits.WR=1;    // begin write to internal EEPROM
	INTCON=INTCON_SAVE; //Now we can safely enable interrupts if previously used
	
	Nop();

	while (PIR2bits.EEIF==0)//Wait till write operation complete
	{
		Nop();
	}

	EECON1bits.WREN=0; // Disable writes to EEPROM on write complete (EEIF flag on set PIR2 )
	PIR2bits.EEIF=0; //Clear EEPROM write complete flag. (must be cleared in software. So we do it here)

}

// This function reads data from address given in internal EEPROM of PIC 
unsigned char EEPROM_getc(unsigned char address)
{
	EEADR=address;
	EECON1bits.EEPGD= 0; // 0 = Access data EEPROM memory
	EECON1bits.CFGS = 0; // 0 = Access Flash program or DATA EEPROM memory
    EECON1bits.RD   = 1; // EEPROM Read
   	return EEDATA;       // return data
}

unsigned char EEPROM_getPlayer()
{	
	return EEPROM_getc(player_addr);			
}

void EEPROM_setPlayer(unsigned char player)
{
	// Changing PLAYER ID
	if (player >= 0 && player <= 9)
	{		
		EEPROM_putc(player_addr,player); //Write 0x?? to EEPROM address 0x00
		Nop();
	}		
}