/*********************************************************************
 * FileName:        tlc5940.h
 * Dependencies:    See INCLUDES section below
 * Processor:       PIC18
 * Compiler:        C18 2.30.01+
 *
 *
 ********************************************************************/

#ifndef FREQUENCY_H
#define FREQUENCY_H

/** I N C L U D E S **********************************************************/
//#include "HardwareProfile.h"     

/** D E F I N I T I O N S ****************************************************/

// ***************************
// Limits
// ***************************


// ***************************
// TLC CMD
// ***************************


// ***************************
// TLC Actions
// ***************************


// ***************************
// PIC18 Pin outs
// ***************************

// ***************************
// TLC States
// ***************************
//#define WAIT	0x00


/** E X T E R N     **********************************************************/
/* declare a string that's initialized elsewhere */

//extern const char string[];

//extern	BYTE		RC_Buttons0;

/** P U B L I C  P R O T O T Y P E S *****************************************/
unsigned char
doNumber(unsigned long number , unsigned short TMR1H,  unsigned short TMR1L, int adc);

void
doScale(unsigned long number);

void
doFrequency(unsigned long number);


//void
//doFrequency(unsigned long number);

/** P R I V A T E  P R O T O T Y P E S ***************************************/
#endif	// FREQUENCY_H

/****  E N D E  *********************************************/
