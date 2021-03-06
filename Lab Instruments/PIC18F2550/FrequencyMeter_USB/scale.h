/*********************************************************************
 * FileName:        tlc5940.h
 * Dependencies:    See INCLUDES section below
 * Processor:       PIC18
 * Compiler:        C18 2.30.01+
 *
 *
 ********************************************************************/

#ifndef SCALE_H
#define SCALE_H

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
void
lcd_showscale(unsigned long number);

/** P R I V A T E  P R O T O T Y P E S ***************************************/
#endif	// BAND_H

/****  E N D E  *********************************************/
