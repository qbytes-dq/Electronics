/************************************************************************

************************************************************************/

const char qbytes[]  = "Q-Bytes World.";
const char version[] = "Hz Counter v1.0w";
// Keep in sync w/HardwareProfile.h line 108


//#define Hz256

#ifndef MAIN_C
	#define MAIN_C
	
	#include <string.h> /* for 'strcpypgm2ram' */
	#include <stdlib.h> /* for 'atoi' */
	#include "pwm.h"
	
	#include "eeprom.h"
	#include "frequency.h"
	#include "db.h"
	#include "scale.h"
	#include "timers.h"
	
#define PID_GET			0xEE
#define PID_SET			0xFF
	
	// Global includes
	// Note: string.h is required for sprintf commands for debug
	#include <string.h>
	
	// Local includes
	#include "HardwareProfile.h"
	#include "debug.h"
	

	// The library location must be set in:
	// Project -> Build Options Project -> Directories -> Include search path
	// in order for the project to compile.
	#include "./USB/usb.h"
	#include "./USB/usb_function_hid.h"
		
	#include "c:/MCC18/v3.47/h/xlcd.h"
		
		
// ADC
#include <adc.h>
#include <delays.h>
 
int result;
// ADC end
		
	// Ensure we have the correct target PIC device family
	#if !defined(__18F4550) && !defined(__18F2550)
		#error "This firmware only supports either the PIC18F4550 or PIC18F2550 microcontrollers."
	#endif

// Define the globals for the USB data in the USB RAM of the PIC18F*550
#pragma udata
#pragma udata USB_VARIABLES=0x500
	unsigned char ReceivedDataBuffer[64];
	unsigned char ToSendDataBuffer[64];
#pragma udata
	
USB_HANDLE USBOutHandle = 0;
USB_HANDLE USBInHandle = 0;


unsigned long overflowTMR0;
unsigned long overflowTMR1;

unsigned char trigger = 10; // first thing we do is find the scale.


//BOOL blinkStatusValid = FLAG_TRUE;
// http://www.xargs.com/pic/c18large.html

// ==========================================================
// ==========================================================
// ==========================================================
// PIC18F4550/PIC18F2550 configuration for the WFF Generic HID test device
//#pragma config PLLDIV=12, CPUDIV=OSC1_PLL2, USBDIV=2, FOSC=HSPLL_HS// FCMEM=OFF
#pragma config PLLDIV   = 12
#pragma config CPUDIV   = OSC1_PLL2   
#pragma config USBDIV   = 2         // Clock source from 96MHz PLL/2
//#pragma config FOSC     = HSPLL_HS
//Oscillator Selection bits:
//#pragma config FOSC = XT_XT         //XT oscillator, XT used by USB
//#pragma config FOSC = XTPLL_XT      //XT oscillator, PLL enabled, XT used by USB
//    #pragma config FOSC = ECIO_EC       //External clock, port function on RA6, EC used by USB
//#pragma config FOSC = EC_EC         //External clock, CLKOUT on RA6, EC used by USB
  #pragma config FOSC = ECPLLIO_EC    //External clock,PLL enabled, port function on RA6,EC used by USB
//#pragma config FOSC = ECPLL_EC      //External clock, PLL enabled, CLKOUT on RA6, EC used by USB
//#pragma config FOSC = INTOSCIO_EC   //Internal oscillator, port function on RA6, EC used by USB
//#pragma config FOSC = INTOSC_EC     //Internal oscillator, CLKOUT on RA6, EC used by USB
//#pragma config FOSC = INTOSC_XT     //Internal oscillator, XT used by USB
//#pragma config FOSC = INTOSC_HS     //Internal oscillator, HS used by USB
//#pragma config FOSC = HS            //HS oscillator, HS used by USB
//#pragma config FOSC = HSPLL_HS      //HS oscillator, PLL enabled, HS used by USB
#pragma config FCMEN    = OFF
#pragma config IESO     = OFF
#pragma config PWRT     = OFF
#pragma config BOR      = ON
#pragma config BORV     = 3
#pragma config VREGEN   = ON
#pragma config WDT      = OFF
#pragma config WDTPS    = 32768
#pragma config MCLRE    = ON
#pragma config LPT1OSC  = OFF
#pragma config PBADEN   = OFF
//#pragma config CCP2MX   = ON
#pragma config CCP2MX   = OFF
#pragma config STVREN   = ON
#pragma config LVP      = OFF
// #pragma config ICPRT    = OFF
#pragma config XINST    = OFF
#pragma config CP0      = OFF
#pragma config CP1      = OFF
// #pragma config CP2      = OFF
// #pragma config CP3      = OFF
#pragma config CPB      = OFF
// #pragma config CPD      = OFF
#pragma config WRT0     = OFF
#pragma config WRT1     = OFF
// #pragma config WRT2     = OFF
// #pragma config WRT3     = OFF
#pragma config WRTB     = OFF
#pragma config WRTC     = OFF
// #pragma config WRTD     = OFF
#pragma config EBTR0    = OFF
#pragma config EBTR1    = OFF
// #pragma config EBTR2    = OFF
// #pragma config EBTR3    = OFF
#pragma config EBTRB    = OFF

//#pragma config CCP2MX = PORTC 
//#pragma config STVREN = OFF
//#pragma config LVP = OFF
//#pragma config XINST = OFF

// Private function prototypes
static void initialisePic(void);
void processUsbCommands(void);
void applicationInit(void);
void USBCBSendResume(void);
void highPriorityISRCode();
void lowPriorityISRCode();


void GSCLK_Event();

// Remap vectors for compatibilty with Microchip USB boot loaders
#if defined(PROGRAMMABLE_WITH_USB_HID_BOOTLOADER)
	#define REMAPPED_RESET_VECTOR_ADDRESS			0x1000
	#define REMAPPED_HIGH_INTERRUPT_VECTOR_ADDRESS	0x1008
	#define REMAPPED_LOW_INTERRUPT_VECTOR_ADDRESS	0x1018
#elif defined(PROGRAMMABLE_WITH_USB_MCHPUSB_BOOTLOADER)	
	#define REMAPPED_RESET_VECTOR_ADDRESS			0x800
	#define REMAPPED_HIGH_INTERRUPT_VECTOR_ADDRESS	0x808
	#define REMAPPED_LOW_INTERRUPT_VECTOR_ADDRESS	0x818
#else	
	#define REMAPPED_RESET_VECTOR_ADDRESS			0x00
	#define REMAPPED_HIGH_INTERRUPT_VECTOR_ADDRESS	0x08
	#define REMAPPED_LOW_INTERRUPT_VECTOR_ADDRESS	0x18
#endif

#if defined(PROGRAMMABLE_WITH_USB_HID_BOOTLOADER) || defined(PROGRAMMABLE_WITH_USB_MCHPUSB_BOOTLOADER)
	extern void _startup (void);
	#pragma code REMAPPED_RESET_VECTOR = REMAPPED_RESET_VECTOR_ADDRESS
	void _reset (void)
	{
	    _asm goto _startup _endasm
	}
#endif

#pragma code REMAPPED_HIGH_INTERRUPT_VECTOR = REMAPPED_HIGH_INTERRUPT_VECTOR_ADDRESS
void Remapped_High_ISR (void)
{
     _asm goto highPriorityISRCode _endasm
}

#pragma code REMAPPED_LOW_INTERRUPT_VECTOR = REMAPPED_LOW_INTERRUPT_VECTOR_ADDRESS
void Remapped_Low_ISR (void)
{
     _asm goto lowPriorityISRCode _endasm
}

#if defined(PROGRAMMABLE_WITH_USB_HID_BOOTLOADER) || defined(PROGRAMMABLE_WITH_USB_MCHPUSB_BOOTLOADER)
#pragma code HIGH_INTERRUPT_VECTOR = 0x08
void High_ISR (void)
{
     _asm goto REMAPPED_HIGH_INTERRUPT_VECTOR_ADDRESS _endasm
}

#pragma code LOW_INTERRUPT_VECTOR = 0x18
void Low_ISR (void)
{
     _asm goto REMAPPED_LOW_INTERRUPT_VECTOR_ADDRESS _endasm
}
#endif

// High-priority ISR handling function
#pragma interrupt highPriorityISRCode
void highPriorityISRCode()
{
	// Application specific high-priority ISR code goes here
	
	#if defined(USB_INTERRUPT)
		// Perform USB device tasks
		USBDeviceTasks();
	#endif
	
	//    if (INTCONbits.TMR0IF)
	if (INTCONbits.T0IF)
	   {		  
	    TMR0H	 = 0x16;
	    TMR0L	 = 0x18;	
	 			
	    // Clear timer flag
		INTCONbits.INT0IF = 0;
		INTCONbits.T0IF=0;
	
		if (++overflowTMR0 >= trigger)
		{
			if (trigger == 100)
			{
			Delay10TCYx(0x5C);			/// FINE Tune
			//Nop();
			}			
			timersOff();
		}		 	
//	 	mDebugStatus6_toggle();
	}
		
	//////Timer1 -- High prioritoy is off (Look at low priority).
	if (PIR1bits.TMR1IF)
		{ 
	  	PIR1bits.TMR1IF = 0;
//	  	mDebugStatus_Toggle3();
	  	overflowTMR1++;
		}
}

// Low-priority ISR handling function
#pragma interruptlow lowPriorityISRCode
void lowPriorityISRCode()
{
	// Application specific low-priority ISR code goes here
	
//	//    if (INTCONbits.TMR0IF)
//	if (INTCONbits.T0IE && INTCONbits.T0IF)
//	   {
//		// Timer 0 interrupt   
//	    TMR0H	 = 0x15;
//	    TMR0L	 = 0xA0;	
//	 			
//	    // Clear timer flag
//		INTCONbits.INT0IF = 0;
//		INTCONbits.T0IF=0;
//	
//	 	//LATA.RA0=~LATA.RA0;
//	 	mDebugStatus5_Toggle();
//	 	overflowTMR0++;
//	}
	
	//////Timer1
	if (PIR1bits.TMR1IF)
		{ 
	  	PIR1bits.TMR1IF = 0;
//	  	mDebugStatus6_toggle();
	  	overflowTMR1++;
		}			
}

// String for creating debug messages
char debugString[64];
int c = 0;

// Vars for returning Device Version
char s_chr_DSN[]={DSN};
char s_chr_PSD[] ={PSD};
char s_chr_PSD0[]={PSD_p0};
char s_chr_PSD1[]={PSD_p1};
char s_chr_PSD2[]={PSD_p2};
char s_chr_PSD3[]={PSD_p3};
char s_chr_PSD4[]={PSD_p4};
char s_chr_PSD5[]={PSD_p5};
char s_chr_PSD6[]={PSD_p6};
char s_chr_PSD7[]={PSD_p7};
char s_chr_PSD8[]={PSD_p8};
char s_chr_PSD9[]={PSD_p9};
int index;


unsigned char ccc=0;
//int ddd=0;
unsigned long number =    0;	//unsigned long       32 bits  0 to 4,294,967,295


void doADC0(){
	  // configure A/D convertor
  OpenADC( ADC_FOSC_64      &
           ADC_RIGHT_JUST   &
           ADC_12_TAD,
           ADC_CH0          &
//           ADC_CH1          &
           ADC_REF_VDD_VSS  &
//-->           ADC_REF_VREFPLUS_VSS &
           //ADC_INT_OFF, ADC_CH10 );  // CH0 to CH10 active.
           ADC_INT_OFF, ADC_CH1 );     // CH0 and CH1 active.
 
  Delay10TCYx( 5 );     // Delay for 50TCY
  ConvertADC();         // Start conversion
  while( BusyADC() );   // Wait for completion
  result = ReadADC();   // Read result
  CloseADC();           // Disable A/D converter

}

  
// Main program entry point
void main(void)
{
    
	// Initialise and configure the PIC ready to go
    initialisePic();

	// If we are running in interrupt mode attempt to attach the USB device
    #if defined(USB_INTERRUPT)
        USBDeviceAttach();
    #endif
	
	// Initialise the debug log functions
    debugInitialise();
	// Print Device ID
	for (index = 0; index <PSDLENGTH;index++)
	{		
    	switch(EEPROM_getPlayer())
          {
	           	case 0x00:
	            {
	            	debugString[index] = s_chr_PSD0[index];	
	               	break;
	            }
	           	case 0x01:
	            {
	            	debugString[index] = s_chr_PSD1[index];	
	               	break;
	            }
	           	case 0x02:
	            {
	            	debugString[index] = s_chr_PSD2[index];	
	               	break;
	            }
	           	case 0x03:
	            {
	            	debugString[index] = s_chr_PSD3[index];	
	               	break;
	            }
	           	case 0x04:
	            {
	            	debugString[index] = s_chr_PSD4[index];	
	               	break;
	            }
	           	case 0x05:
	            {
	            	debugString[index] = s_chr_PSD5[index];	
	               	break;
	            }
	           	case 0x06:
	            {
	            	debugString[index] = s_chr_PSD6[index];	
	               	break;
	            }
	           	case 0x07:
	            {
	            	debugString[index] = s_chr_PSD7[index];	
	               	break;
	            }
	           	case 0x08:
	            {
	            	debugString[index] = s_chr_PSD8[index];	
	               	break;
	            }
	           	case 0x09:
	            {
	            	debugString[index] = s_chr_PSD9[index];	
	               	break;
	            }
	           	default:
	            {
	            	debugString[index] = s_chr_PSD[index];	
	               	break;
	            }            
		  }   
	}
	debugString[PSDLENGTH] = 0;
	debugOut(debugString);	
			
	// Print version number
	for (index = 0; index <DSNLENGTH;index++)
	{
		debugString[index] = s_chr_DSN[index];		
	}
	debugString[DSNLENGTH] = 0;
	debugOut(debugString);


	
	// Print copy right
	sprintf(debugString, "(C)2014 David Quesenberry - http://www.QBytesWorld.com");
	debugOut(debugString);
	
	sprintf(debugString, "USB Device Initialised.");
	debugOut(debugString);


 	OpenXLCD(	FOUR_BIT //&
 				//LINES_5X7&
 				//DISP_FLIP_NONE
 				);
 	
	while(BusyXLCD());
	putsXLCD(&qbytes);
	
	while(BusyXLCD());
	WriteCmdXLCD(0xC0);             // Line 2, POS 0
	Delay10KTCYx(0x10);
	
	while(BusyXLCD());
	putsXLCD(&version);
	
	for (ccc=0;ccc<10;ccc++)
	{	
	Delay10KTCYx(0x00);
	}
	
// Clear display
clearXLCD();


timersOn();

// ================================================
// ================================================
// ================================================
mInitStatusLeds();



	// Main processing loop
    while(1)
    {	
//if (m50MHz_get())
//{
//	mSW1_hi();
//	mSW2_hi();
//	mSW3_hi();
//	//mSW1_toggle();
//	//mSW2_toggle();
//	//mSW3_toggle();
//}	
//else 
//{
//	mSW1_lo();
//	mSW2_lo();
//	mSW3_lo();
//}	


		#if defined(USB_POLLING)
			// If we are in polling mode the USB device tasks must be processed here
			// (otherwise the interrupt is performing this task)
	        USBDeviceTasks();
        #endif
    	
    	// Process USB Commands
    	
        processUsbCommands();  
        
        // Note: Other application specific actions can be placed here    


		if (overflowTMR0 >= trigger)
		{
			mGate_on(); // Gate LED
			
			timersOff();

doADC0();

			trigger = doNumber( overflowTMR1 , (unsigned short)TMR1H, (unsigned short)TMR1L, result);		
						
			overflowTMR0=0;
			overflowTMR1=0;
		
			timersOn();
			
			mGate_off(); // Gate LED
		}	
   }
}


// Initialise the PIC
static void initialisePic(void)
{
    // PIC port set up --------------------------------------------------------

//http://www.winpicprog.co.uk/pic_tutorial11.htm
	// Default all pins to digital
   //ADCON1 = 0x0F;
CMCON = 0x1f;
   CMCON  = 0b00000111;   // Turn off Comparator
  ADCON0 = 0b00000001;   // A/D Converter module is enabled
   ADCON1 = 0b00001101;   // AN0 Analog, everything else digital
//     ADCON1 = 0b00000111;   // AN0 Analog, everything else digital 
	// Configure ports as inputs (1) or outputs(0)	
	TRISC = 0b00000001; //T13CKI - counter pin


//////Timer1
//INITIALIZATION OF PORT,TIMER1,INTERRUPTS 
//TRISCbits.TRISC0 = 1; 
//TRISCbits.TRISC1 = 1; 

	
#if defined(__18F4550)
	TRISD = 0b00000000;
	TRISE = 0b00000000;
#endif

	// Clear all ports
	PORTA = 0b00000000;
//	PORTB = 0b00000000;
	PORTC = 0b00000000;
	
#if defined(__18F4550)
	PORTD = 0b00000000;
	PORTE = 0b00000000;
#endif

	// If you have a VBUS sense pin (for self-powered devices when you
	// want to detect if the USB host is connected) you have to specify
	// your input pin in HardwareProfile.h
    #if defined(USE_USB_BUS_SENSE_IO)
    	tris_usb_bus_sense = INPUT_PIN;
    #endif
    
    // In the case of a device which can be both self-powered and bus-powered
    // the device must respond correctly to a GetStatus (device) request and
    // tell the host how it is currently powered.
    //
    // To do this you must device a pin which is high when self powered and low
    // when bus powered and define this in HardwareProfile.h
    #if defined(USE_SELF_POWER_SENSE_IO)
    	tris_self_power = INPUT_PIN;
    #endif

    // Application specific initialisation
    applicationInit();
    
    
    		
	//
//	EEPROM_setPlayer(6);
//	player = EEPROM_getPlayer();
//	player = 2;

    // Initialise the USB device
    USBDeviceInit();
}

// Application specific device initialisation
void applicationInit(void)
{
	// Initialise the status LEDs
	mInitStatusLeds();
	
	// Initialise the switch
//	mInitAllSwitches();
	
    // Initialize the variable holding the USB handle for the last transmission
    USBOutHandle = 0;
    USBInHandle = 0;
}

// Process USB commands
void processUsbCommands(void)
{   
    // Check if we are in the configured state; otherwise just return
    if((USBDeviceState < CONFIGURED_STATE) || (USBSuspendControl == 1))
    {
	    // We are not configured
	    return;
	}



	// Check if data was received from the host.
    if(!HIDRxHandleBusy(USBOutHandle))
    {   
		// Command mode 
		if (ReceivedDataBuffer[0]!=0x10 && ReceivedDataBuffer[0]!=0x81 && ReceivedDataBuffer[0]!=0x82 )
		{
//			if (mDebugStatus5 == 0x01)
//			{
//	       	sprintf(debugString, "Received command 0x%X from host.",ReceivedDataBuffer[0]);
//			debugOut(debugString);
//			}
		}
				
        switch(ReceivedDataBuffer[0])
		{		
			case 0x10:	// Debug information request from host
				// Copy any waiting debug text to the send data buffer
				copyDebugToSendBuffer((BYTE*)&ToSendDataBuffer[0]);
			        
		        // Transmit the response to the host
                if(!HIDTxHandleBusy(USBInHandle))
				{
					USBInHandle = HIDTxPacket(HID_EP,(BYTE*)&ToSendDataBuffer[0],64);
				}
				break;
				
			// Place application specific commands here:
			
//			case 0x10:	// Trigger information request from host
//				// Copy any waiting debug text to the send data buffer
//				copyDebugToSendBuffer((BYTE*)&ToSendDataBuffer[0]);
//
//		        // Transmit the response to the host
//                if(!HIDTxHandleBusy(USBInHandle))
//				{
//					//ToSendDataBuffer[0] = get_TRIGGERED();
//					if 	(get_TRIGGERED() == 0x01)
//					{	        
////						clear_TRIGGERED();
//						
//						sprintf(debugString, "TRIGGER");
//						debugOut(debugString);
//						copyDebugToSendBuffer((BYTE*)&ToSendDataBuffer[0]);					
//					}
//					USBInHandle = HIDTxPacket(HID_EP,(BYTE*)&ToSendDataBuffer[0],64);
//				}
//				break;
				
			// Place application specific commands here:			
			
			
//			// Joystick is a 4 or 8 way
//            case 0x48:  // Change Joystick 4 or 8 way
//				
//				if (ReceivedDataBuffer[1] == 0x04)
//					{
//						// 4 way joystick
//						mJoyDirection = 1;
//					}
//					else
//					{	
//						// Must be an 8 way joystick
//						mJoyDirection = 0;
//					}	
//					
//            	break;
            				
//            // Mouse has a LOW or HIGH DPI Resolusion
//            case 0x84:  // Change mouse DPI
//				
//				if (ReceivedDataBuffer[1] == 0x00)
//					{
//						// Low speed
//						mMouseSpeed = 0;
//					}
//					else
//					{	
//						// High Speed
//						mMouseSpeed = 1;
//					}	
//					
//            	break;
            	
			
            case 0x80:  // Toggle the LED
				// Toggle the LED0
//				mDebugStatus5_toggle();
					
            	break;            	
            	
            case 0x81:  // Read the push switch status
				ToSendDataBuffer[0] = 0x00;//PORTBbits.RB7;//XERR;

				// Transmit the response to the host
                if(!HIDTxHandleBusy(USBInHandle))
				{
					USBInHandle = HIDTxPacket(HID_EP,(BYTE*)&ToSendDataBuffer[0],64);
				}
            	break;
            	
            case 0x82:  // Read the Debug status
				// Get the debug state and put it in the send buffer
//				ToSendDataBuffer[0] = mDebugStatus5_get();
				
				// Transmit the response to the host
                if(!HIDTxHandleBusy(USBInHandle))
				{
					USBInHandle = HIDTxPacket(HID_EP,(BYTE*)&ToSendDataBuffer[0],64);
				}
            	break;

// =====================================================
			case PID_SET: // Set product ID (Device ID 0-9).
				
				// Ask the PIC to set the ID
				EEPROM_setPlayer((unsigned char) ReceivedDataBuffer[1]);
					
//			if (mDebugStatus5 == 0x01)
//			{
//		       	sprintf(debugString, "PID_SET - 0x%X 0x%X 0x%X round trip.",
//		       		ReceivedDataBuffer[0],ReceivedDataBuffer[1],EEPROM_getPlayer());
//				debugOut(debugString); 
//			}
	// Reset the device			
_asm 
   reset
_endasm
//				reset_cpu(); // or mclr is grounded to reset 
																
				break;				

// =====================================================
			case PID_GET: // Set product ID.
				
				// Ask the PIC to set the ID
		       	sprintf(debugString, "PID_GET - 0x%X to host.", EEPROM_getPlayer());
				debugOut(debugString); 
																
				break;				
				
// =====================================================
											
            default:	// Unknown command received
		       	sprintf(debugString, "OOPS - Invalid command 0x%X 0x%X 0x%X 0x%X 0x%X 0x%X from host.",
		       		ReceivedDataBuffer[0],ReceivedDataBuffer[1],ReceivedDataBuffer[2],ReceivedDataBuffer[3],ReceivedDataBuffer[4],ReceivedDataBuffer[5]);
				debugOut(debugString);            
           		break;
		}	
		 
        // Re-arm the OUT endpoint for the next packet
        USBOutHandle = HIDRxPacket(HID_EP,(BYTE*)&ReceivedDataBuffer,64);
  	}
}

// USB Callback handling routines -----------------------------------------------------------

// Call back that is invoked when a USB suspend is detected
void USBCBSuspend(void)
{
}

// This call back is invoked when a wakeup from USB suspend is detected.
void USBCBWakeFromSuspend(void)
{
}

// The USB host sends out a SOF packet to full-speed devices every 1 ms.
void USBCB_SOF_Handler(void)
{
    // No need to clear UIRbits.SOFIF to 0 here. Callback caller is already doing that.
}

// The purpose of this callback is mainly for debugging during development.
// Check UEIR to see which error causes the interrupt.
void USBCBErrorHandler(void)
{
    // No need to clear UEIR to 0 here.
    // Callback caller is already doing that.
}

// Check other requests callback
void USBCBCheckOtherReq(void)
{
    USBCheckHIDRequest();
}

// Callback function is called when a SETUP, bRequest: SET_DESCRIPTOR request arrives.
void USBCBStdSetDscHandler(void)
{
    // You must claim session ownership if supporting this request
}

//This function is called when the device becomes initialized
void USBCBInitEP(void)
{
    // Enable the HID endpoint
    USBEnableEndpoint(HID_EP,USB_IN_ENABLED|USB_OUT_ENABLED|USB_HANDSHAKE_ENABLED|USB_DISALLOW_SETUP);
    
    // Re-arm the OUT endpoint for the next packet
    USBOutHandle = HIDRxPacket(HID_EP,(BYTE*)&ReceivedDataBuffer,64);
}

// Send resume call-back
void USBCBSendResume(void)
{
    static WORD delay_count;
    
    // Verify that the host has armed us to perform remote wakeup.
    if(USBGetRemoteWakeupStatus() == FLAG_TRUE) 
    {
        // Verify that the USB bus is suspended (before we send remote wakeup signalling).
        if(USBIsBusSuspended() == FLAG_TRUE)
        {
            USBMaskInterrupts();
            
            // Bring the clock speed up to normal running state
            USBCBWakeFromSuspend();
            USBSuspendControl = 0; 
            USBBusIsSuspended = FLAG_FALSE;

            // Section 7.1.7.7 of the USB 2.0 specifications indicates a USB
            // device must continuously see 5ms+ of idle on the bus, before it sends
            // remote wakeup signalling.  One way to be certain that this parameter
            // gets met, is to add a 2ms+ blocking delay here (2ms plus at 
            // least 3ms from bus idle to USBIsBusSuspended() == FLAG_TRUE, yeilds
            // 5ms+ total delay since start of idle).
            delay_count = 3600U;        
            do
            {
                delay_count--;
            } while(delay_count);
            
            // Start RESUME signaling for 1-13 ms
            USBResumeControl = 1;
            delay_count = 1800U;
            do
            {
                delay_count--;
            } while(delay_count);
            USBResumeControl = 0;

            USBUnmaskInterrupts();
        }
    }
}

// USB callback function handler
BOOL USER_USB_CALLBACK_EVENT_HANDLER(USB_EVENT event, void *pdata, WORD size)
{
    switch(event)
    {
        case EVENT_TRANSFER:
            // Application callback tasks and functions go here
            break;
        case EVENT_SOF:
            USBCB_SOF_Handler();
            break;
        case EVENT_SUSPEND:
            USBCBSuspend();
            break;
        case EVENT_RESUME:
            USBCBWakeFromSuspend();
            break;
        case EVENT_CONFIGURED: 
            USBCBInitEP();
            break;
        case EVENT_SET_DESCRIPTOR:
            USBCBStdSetDscHandler();
            break;
        case EVENT_EP0_REQUEST:
            USBCBCheckOtherReq();
            break;
        case EVENT_BUS_ERROR:
            USBCBErrorHandler();
            break;
        default:
            break;
    }      
    return FLAG_TRUE; 
}

#endif
