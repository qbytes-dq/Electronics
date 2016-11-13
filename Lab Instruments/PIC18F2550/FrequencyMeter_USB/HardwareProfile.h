/************************************************************************
	HardwareProfile.h

	WFF USB Generic HID Demonstration 3
    usbGenericHidCommunication reference firmware 3_0_0_0
    Copyright (C) 2011 Simon Inns

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

	Email: simon.inns@gmail.com

************************************************************************/

#ifndef HARDWAREPROFILE_H
#define HARDWAREPROFILE_H

// USB stack hardware selection options ----------------------------------------------------------------

// (This section is the set of definitions required by the MCHPFSUSB framework.)

// Uncomment the following define if you wish to use the self-power sense feature 
// and define the port, pin and tris for the power sense pin below:
// #define USE_SELF_POWER_SENSE_IO
#define tris_self_power     TRISAbits.TRISA2
#if defined(USE_SELF_POWER_SENSE_IO)
	#define self_power      PORTAbits.RA2
#else
	#define self_power          1
#endif

// Uncomment the following define if you wish to use the bus-power sense feature 
// and define the port, pin and tris for the power sense pin below:
//#define USE_USB_BUS_SENSE_IO
#define tris_usb_bus_sense  TRISAbits.TRISA1
#if defined(USE_USB_BUS_SENSE_IO)
	#define USB_BUS_SENSE   PORTAbits.RA1
#else
	#define USB_BUS_SENSE       1
#endif

// Uncomment the following line to make the output HEX of this project work with the MCHPUSB Bootloader    
//#define PROGRAMMABLE_WITH_USB_MCHPUSB_BOOTLOADER

// Uncomment the following line to make the output HEX of this project work with the HID Bootloader
#define PROGRAMMABLE_WITH_USB_HID_BOOTLOADER		

// Application specific hardware definitions ------------------------------------------------------------

// Oscillator frequency (48Mhz with a 20Mhz external oscillator)
#define CLOCK_FREQ 48000000

// Device Vendor Indentifier (VID) (0x04D8 is Microchip's VID)
#define USB_VID	0x04D9

// Device Product Indentifier (PID) (0x0042)
#define USB_PID		0x0999
#define USB_PID_p0	0x0100
#define USB_PID_p1	0x0101
#define USB_PID_p2	0x0102
#define USB_PID_p3	0x0103
#define USB_PID_p4	0x0104
#define USB_PID_p5	0x0105
#define USB_PID_p6	0x0106
#define USB_PID_p7	0x0107
#define USB_PID_p8	0x0108
#define USB_PID_p9	0x0109

// Manufacturer string descriptor
//#define MSDLENGTH	10
#define MSDLENGTH	11
//#define MSD		'S','i','m','o','n',' ','I','n','n','s'
#define MSD		'Q','u','e','s','e','n','b','e','r','r','y'

// Product String descriptor
//#define PSDLENGTH	21
#define PSDLENGTH	14
//#define PSD   'W','F','F',' ','G','e','n','e','r','i','c',' ','H','I','D',' ','d','e','m','o'
//               1   2   3   4   5   6   7   8   9   0   1   2   3   4   5   6   7   8   9   0   1   2   3   4   5   6   7   8   9   0
#define PSD		'Q','-','B','e','r','r','y',' ','H','z',' ',' ',35,'?'
#define PSD_p0	'Q','-','B','e','r','r','y',' ','H','z',' ',' ',35,'0'
#define PSD_p1	'Q','-','B','e','r','r','y',' ','H','z',' ',' ',35,'1'
#define PSD_p2	'Q','-','B','e','r','r','y',' ','H','z',' ',' ',35,'2'
#define PSD_p3	'Q','-','B','e','r','r','y',' ','H','z',' ',' ',35,'3'
#define PSD_p4	'Q','-','B','e','r','r','y',' ','H','z',' ',' ',35,'4'
#define PSD_p5	'Q','-','B','e','r','r','y',' ','H','z',' ',' ',35,'5'
#define PSD_p6	'Q','-','B','e','r','r','y',' ','H','z',' ',' ',35,'6'
#define PSD_p7	'Q','-','B','e','r','r','y',' ','H','z',' ',' ',35,'7'
#define PSD_p8	'Q','-','B','e','r','r','y',' ','H','z',' ',' ',35,'8'
#define PSD_p9	'Q','-','B','e','r','r','y',' ','H','z',' ',' ',35,'9'


// Device serial number string descriptor
#define DSNLENGTH	10

// Version 3.7.0
//#define DSN		'W','F','F','_','3','.','0'
#define DSN		'Q','B','W',' ','v','1','.','0','w',' '

// Common useful definitions
#define INPUT_PIN  1
#define OUTPUT_PIN 0
#define FLAG_FALSE 0
#define FLAG_TRUE  1

// Comment out the following line if you do not want the debug
// feature of the firmware (saves code and RAM space when off)
//
// Note: if you use this feature you must compile with the large
// memory model on (for 24-bit pointers) so that the sprintf()
// function will work correctly.  If you do not require debug it's
// recommended that you compile with the small memory model and 
// remove any references to <strings.h> and sprintf().
#define DEBUGON

/**
Each port has three registers for its operation. These registers are:
-- TRIS register (data direction register)
-- PORT register (reads the levels on the pins of the device)
-- LAT register (output latch)
*/

// PIC to hardware pin mapping and control macros



//LATCbits.LATC2 = PORTAbits.RA6;



// Led control macros                                        76543210
#define mInitStatusLeds()		LATA = 0b00000000; TRISA = 0b00011111;

// RA0 = Analog 0-5 (power meter)

// RA1 = Analog 0-5 (pre 7805 voltage divided by 10)

// RA2 = 0 is < 50MHz, 1 is > 50MHz
//#define m50MHz			LATAbits.LATA2
#define m50MHz			PORTAbits.RA2
#define m50MHz_get()    m50MHz

// RA3 = 2.048V ref

// RA4 = clock x

// RA5 = Gate LED
#define mGate			LATAbits.LATA5
#define mGate_on()		mGate = 1;
#define mGate_off()		mGate = 0;

// RA6 = SW1
//#define mSW1			LATAbits.LATA6
//#define mSW1_toggle()	mSW1 = !mSW1;
//#define mSW1_on()		mSW1 = 1;
//#define mSW1_off()		mSW1 = 0;
#define mSW1_hi() LATAbits.LATA6=1; TRISAbits.TRISA6=0; // Input and hi (+5)
#define mSW1_lo() LATAbits.LATA6=0; TRISAbits.TRISA6=1; // Output and hi z (?)

// RC1 = SW2
//#define mSW2			LATCbits.LATC1
//#define mSW2_toggle()	mSW2 = !mSW2;
//#define mSW2_on()		mSW2 = 1;
//#define mSW2_off()		mSW2 = 0;
#define mSW2_hi() LATCbits.LATC1=1; TRISCbits.TRISC1=0; // Input and hi (+5)
#define mSW2_lo() LATCbits.LATC1=0; TRISCbits.TRISC1=1; // Output and hi z (?)

// RC2 = SW3
//#define mSW3			LATCbits.LATC2
//#define mSW3_toggle()	mSW3 = !mSW3;
//#define mSW3_on()		mSW3 = 1;
//#define mSW3_off()		mSW3 = 0;
#define mSW3_hi() LATCbits.LATC2=1; TRISCbits.TRISC2=0; // Input and hi (+5)
#define mSW3_lo() LATCbits.LATC2=0; TRISCbits.TRISC2=1; // Output and hi z (?)


#endif
