
#ifndef EEPROM_H

#define EEPROM_H

	//#include <p18f4550.h>
	//#include <pic.h>
	
	#include <p18cxxx.h>
	#include <delays.h>
	#include <portb.h>//functions to control pull-up resistors and interrupts
	
	#include <pconfig.h>
	#include <delays.h>
	
	void          EEPROM_putc(unsigned char address, unsigned char data);
	unsigned char EEPROM_getc(unsigned char address);
	
	unsigned char EEPROM_getPlayer(void);
	void 		  EEPROM_setPlayer(unsigned char);

#endif	// 