/************************************************************************
	usb_descriptors.c

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

#ifndef USB_DESCRIPTORS_C
#define USB_DESCRIPTORS_C

// Local includes
#include "HardwareProfile.h"

// Microchip Application Library includes
#include "./USB/usb.h"
#include "./USB/usb_function_hid.h"

// Device Descriptor
ROM USB_DEVICE_DESCRIPTOR device_dsc=
{
    0x12,    				// Size of this descriptor in bytes
    USB_DESCRIPTOR_DEVICE,  // DEVICE descriptor type
    0x0200,                 // USB Spec Release Number in BCD format
    0x00,                   // Class Code
    0x00,                   // Subclass code
    0x00,                   // Protocol code
    USB_EP0_BUFF_SIZE,      // Max packet size for EP0, see usb_config.h
    USB_VID,				// Vendor ID
    USB_PID,				// Product ID
    0x0002,                 // Device release number in BCD format
    0x01,                   // Manufacturer string index
    0x02,                   // Product string index
    0x03,                   // Device serial number string index
    0x01                    // Number of possible configurations
};

// Device Descriptor P0
ROM USB_DEVICE_DESCRIPTOR device_dsc_p0=
{
    0x12,    				// Size of this descriptor in bytes
    USB_DESCRIPTOR_DEVICE,  // DEVICE descriptor type
    0x0200,                 // USB Spec Release Number in BCD format
    0x00,                   // Class Code
    0x00,                   // Subclass code
    0x00,                   // Protocol code
    USB_EP0_BUFF_SIZE,      // Max packet size for EP0, see usb_config.h
    USB_VID,				// Vendor ID
    USB_PID_p0,				// Product ID
    0x0002,                 // Device release number in BCD format
    0x01,                   // Manufacturer string index
    0x02,                   // Product string index
    0x03,                   // Device serial number string index
    0x01                    // Number of possible configurations
};

// Device Descriptor P1
ROM USB_DEVICE_DESCRIPTOR device_dsc_p1=
{
    0x12,    				// Size of this descriptor in bytes
    USB_DESCRIPTOR_DEVICE,  // DEVICE descriptor type
    0x0200,                 // USB Spec Release Number in BCD format
    0x00,                   // Class Code
    0x00,                   // Subclass code
    0x00,                   // Protocol code
    USB_EP0_BUFF_SIZE,      // Max packet size for EP0, see usb_config.h
    USB_VID,				// Vendor ID
    USB_PID_p1,				// Product ID
    0x0002,                 // Device release number in BCD format
    0x01,                   // Manufacturer string index
    0x02,                   // Product string index
    0x03,                   // Device serial number string index
    0x01                    // Number of possible configurations
};

// Device Descriptor P2
ROM USB_DEVICE_DESCRIPTOR device_dsc_p2=
{
    0x12,    				// Size of this descriptor in bytes
    USB_DESCRIPTOR_DEVICE,  // DEVICE descriptor type
    0x0200,                 // USB Spec Release Number in BCD format
    0x00,                   // Class Code
    0x00,                   // Subclass code
    0x00,                   // Protocol code
    USB_EP0_BUFF_SIZE,      // Max packet size for EP0, see usb_config.h
    USB_VID,				// Vendor ID
    USB_PID_p2,				// Product ID
    0x0002,                 // Device release number in BCD format
    0x01,                   // Manufacturer string index
    0x02,                   // Product string index
    0x03,                   // Device serial number string index
    0x01                    // Number of possible configurations
};

// Device Descriptor P3
ROM USB_DEVICE_DESCRIPTOR device_dsc_p3=
{
    0x12,    				// Size of this descriptor in bytes
    USB_DESCRIPTOR_DEVICE,  // DEVICE descriptor type
    0x0200,                 // USB Spec Release Number in BCD format
    0x00,                   // Class Code
    0x00,                   // Subclass code
    0x00,                   // Protocol code
    USB_EP0_BUFF_SIZE,      // Max packet size for EP0, see usb_config.h
    USB_VID,				// Vendor ID
    USB_PID_p3,				// Product ID
    0x0002,                 // Device release number in BCD format
    0x01,                   // Manufacturer string index
    0x02,                   // Product string index
    0x03,                   // Device serial number string index
    0x01                    // Number of possible configurations
};

// Device Descriptor P4
ROM USB_DEVICE_DESCRIPTOR device_dsc_p4=
{
    0x12,    				// Size of this descriptor in bytes
    USB_DESCRIPTOR_DEVICE,  // DEVICE descriptor type
    0x0200,                 // USB Spec Release Number in BCD format
    0x00,                   // Class Code
    0x00,                   // Subclass code
    0x00,                   // Protocol code
    USB_EP0_BUFF_SIZE,      // Max packet size for EP0, see usb_config.h
    USB_VID,				// Vendor ID
    USB_PID_p4,				// Product ID
    0x0002,                 // Device release number in BCD format
    0x01,                   // Manufacturer string index
    0x02,                   // Product string index
    0x03,                   // Device serial number string index
    0x01                    // Number of possible configurations
};

// Device Descriptor P5
ROM USB_DEVICE_DESCRIPTOR device_dsc_p5=
{
    0x12,    				// Size of this descriptor in bytes
    USB_DESCRIPTOR_DEVICE,  // DEVICE descriptor type
    0x0200,                 // USB Spec Release Number in BCD format
    0x00,                   // Class Code
    0x00,                   // Subclass code
    0x00,                   // Protocol code
    USB_EP0_BUFF_SIZE,      // Max packet size for EP0, see usb_config.h
    USB_VID,				// Vendor ID
    USB_PID_p5,				// Product ID
    0x0002,                 // Device release number in BCD format
    0x01,                   // Manufacturer string index
    0x02,                   // Product string index
    0x03,                   // Device serial number string index
    0x01                    // Number of possible configurations
};

// Device Descriptor P6
ROM USB_DEVICE_DESCRIPTOR device_dsc_p6=
{
    0x12,    				// Size of this descriptor in bytes
    USB_DESCRIPTOR_DEVICE,  // DEVICE descriptor type
    0x0200,                 // USB Spec Release Number in BCD format
    0x00,                   // Class Code
    0x00,                   // Subclass code
    0x00,                   // Protocol code
    USB_EP0_BUFF_SIZE,      // Max packet size for EP0, see usb_config.h
    USB_VID,				// Vendor ID
    USB_PID_p6,				// Product ID
    0x0002,                 // Device release number in BCD format
    0x01,                   // Manufacturer string index
    0x02,                   // Product string index
    0x03,                   // Device serial number string index
    0x01                    // Number of possible configurations
};

// Device Descriptor P7
ROM USB_DEVICE_DESCRIPTOR device_dsc_p7=
{
    0x12,    				// Size of this descriptor in bytes
    USB_DESCRIPTOR_DEVICE,  // DEVICE descriptor type
    0x0200,                 // USB Spec Release Number in BCD format
    0x00,                   // Class Code
    0x00,                   // Subclass code
    0x00,                   // Protocol code
    USB_EP0_BUFF_SIZE,      // Max packet size for EP0, see usb_config.h
    USB_VID,				// Vendor ID
    USB_PID_p7,				// Product ID
    0x0002,                 // Device release number in BCD format
    0x01,                   // Manufacturer string index
    0x02,                   // Product string index
    0x03,                   // Device serial number string index
    0x01                    // Number of possible configurations
};

// Device Descriptor P8
ROM USB_DEVICE_DESCRIPTOR device_dsc_p8=
{
    0x12,    				// Size of this descriptor in bytes
    USB_DESCRIPTOR_DEVICE,  // DEVICE descriptor type
    0x0200,                 // USB Spec Release Number in BCD format
    0x00,                   // Class Code
    0x00,                   // Subclass code
    0x00,                   // Protocol code
    USB_EP0_BUFF_SIZE,      // Max packet size for EP0, see usb_config.h
    USB_VID,				// Vendor ID
    USB_PID_p8,				// Product ID
    0x0002,                 // Device release number in BCD format
    0x01,                   // Manufacturer string index
    0x02,                   // Product string index
    0x03,                   // Device serial number string index
    0x01                    // Number of possible configurations
};

// Device Descriptor P9
ROM USB_DEVICE_DESCRIPTOR device_dsc_p9=
{
    0x12,    				// Size of this descriptor in bytes
    USB_DESCRIPTOR_DEVICE,  // DEVICE descriptor type
    0x0200,                 // USB Spec Release Number in BCD format
    0x00,                   // Class Code
    0x00,                   // Subclass code
    0x00,                   // Protocol code
    USB_EP0_BUFF_SIZE,      // Max packet size for EP0, see usb_config.h
    USB_VID,				// Vendor ID
    USB_PID_p9,				// Product ID
    0x0002,                 // Device release number in BCD format
    0x01,                   // Manufacturer string index
    0x02,                   // Product string index
    0x03,                   // Device serial number string index
    0x01                    // Number of possible configurations
};


// Configuration 1 Descriptor
ROM BYTE configDescriptor1[]=
{
    // Configuration Descriptor
    0x09,							// Size of this descriptor in bytes (sizeof(USB_CFG_DSC))
    USB_DESCRIPTOR_CONFIGURATION,	// CONFIGURATION descriptor type
    0x29,0x00,						// Total length of data for this cfg
    1,								// Number of interfaces in this cfg
    1,								// Index value of this configuration
    0,								// Configuration string index
    _DEFAULT | _SELF,				// Attributes, see usb_device.h
    50,								// Max power consumption (2X mA)
							
    // Interface Descriptor
    0x09,							// Size of this descriptor in bytes (sizeof(USB_INTF_DSC))
    USB_DESCRIPTOR_INTERFACE,		// INTERFACE descriptor type
    0,								// Interface Number
    0,								// Alternate Setting Number
    2,								// Number of endpoints in this intf
    HID_INTF,						// Class code
    0,								// Subclass code
    0,								// Protocol code
    0,								// Interface string index

    // HID Class-Specific Descriptor
    0x09,							// Size of this descriptor in bytes (sizeof(USB_HID_DSC)+3)
    DSC_HID,						// HID descriptor type
    0x11,0x01,						// HID Spec Release Number in BCD format (1.11)
    0x00,							// Country Code (0x00 for Not supported)
    HID_NUM_OF_DSC,					// Number of class descriptors, see usbcfg.h
    DSC_RPT,						// Report descriptor type
    HID_RPT01_SIZE,0x00,			// Size of the report descriptor (sizeof(hid_rpt01))
    
    // Endpoint Descriptor
    0x07,							// sizeof(USB_EP_DSC)
    USB_DESCRIPTOR_ENDPOINT,		// Endpoint Descriptor
    HID_EP | _EP_IN,				// Endpoint Address
    _INTERRUPT,						// Attributes
    0x40,0x00,						// size
    0x01,							// Interval

    // Endpoint Descriptor
    0x07,							// sizeof(USB_EP_DSC)
    USB_DESCRIPTOR_ENDPOINT,		// Endpoint Descriptor
    HID_EP | _EP_OUT,				// EndpointAddress
    _INTERRUPT,						// Attributes
    0x40,0x00,						// size
    0x01							// Interval
};

// Language code string descriptor
ROM struct{BYTE bLength;BYTE bDscType;WORD string[1];}sd000={
sizeof(sd000),USB_DESCRIPTOR_STRING,{0x0409
}};

// Manufacturer string descriptor (set in HardwareProfile.h)
ROM struct{BYTE bLength;BYTE bDscType;WORD string[MSDLENGTH];}sd001={
sizeof(sd001),USB_DESCRIPTOR_STRING,
{MSD}};

// ============================================================================
// Product string descriptor (set in HardwareProfile.h)
ROM struct{BYTE bLength;BYTE bDscType;WORD string[PSDLENGTH];}sd002={
sizeof(sd002),USB_DESCRIPTOR_STRING,
{PSD}};

ROM struct{BYTE bLength;BYTE bDscType;WORD string[PSDLENGTH];}sd002_p0={
sizeof(sd002_p0),USB_DESCRIPTOR_STRING,
{PSD_p0}};
ROM struct{BYTE bLength;BYTE bDscType;WORD string[PSDLENGTH];}sd002_p1={
sizeof(sd002_p1),USB_DESCRIPTOR_STRING,
{PSD_p1}};
ROM struct{BYTE bLength;BYTE bDscType;WORD string[PSDLENGTH];}sd002_p2={
sizeof(sd002_p2),USB_DESCRIPTOR_STRING,
{PSD_p2}};
ROM struct{BYTE bLength;BYTE bDscType;WORD string[PSDLENGTH];}sd002_p3={
sizeof(sd002_p3),USB_DESCRIPTOR_STRING,
{PSD_p3}};
ROM struct{BYTE bLength;BYTE bDscType;WORD string[PSDLENGTH];}sd002_p4={
sizeof(sd002_p4),USB_DESCRIPTOR_STRING,
{PSD_p4}};
ROM struct{BYTE bLength;BYTE bDscType;WORD string[PSDLENGTH];}sd002_p5={
sizeof(sd002_p5),USB_DESCRIPTOR_STRING,
{PSD_p5}};
ROM struct{BYTE bLength;BYTE bDscType;WORD string[PSDLENGTH];}sd002_p6={
sizeof(sd002_p6),USB_DESCRIPTOR_STRING,
{PSD_p6}};
ROM struct{BYTE bLength;BYTE bDscType;WORD string[PSDLENGTH];}sd002_p7={
sizeof(sd002_p7),USB_DESCRIPTOR_STRING,
{PSD_p7}};
ROM struct{BYTE bLength;BYTE bDscType;WORD string[PSDLENGTH];}sd002_p8={
sizeof(sd002_p8),USB_DESCRIPTOR_STRING,
{PSD_p8}};
ROM struct{BYTE bLength;BYTE bDscType;WORD string[PSDLENGTH];}sd002_p9={
sizeof(sd002_p9),USB_DESCRIPTOR_STRING,
{PSD_p9}};



// Device serial number string descriptor
ROM struct{BYTE bLength;BYTE bDscType;WORD string[DSNLENGTH];}sd003={
sizeof(sd003),USB_DESCRIPTOR_STRING,
{DSN}};

// Class specific descriptor - HID 
ROM struct{BYTE report[HID_RPT01_SIZE];}hid_rpt01={
{
    0x06, 0x00, 0xFF,       // Usage Page = 0xFF00 (Vendor Defined Page 1)
    0x09, 0x01,             // Usage (Vendor Usage 1)
    0xA1, 0x01,             // Collection (Application)
    0x19, 0x01,             //      Usage Minimum 
    0x29, 0x40,             //      Usage Maximum 	//64 input usages total (0x01 to 0x40)
    0x15, 0x01,             //      Logical Minimum (data bytes in the report may have minimum value = 0x00)
    0x25, 0x40,      	  	//      Logical Maximum (data bytes in the report may have maximum value = 0x00FF = unsigned 255)
    0x75, 0x08,             //      Report Size: 8-bit field size
    0x95, 0x40,             //      Report Count: Make sixty-four 8-bit fields (the next time the parser hits an "Input", "Output", or "Feature" item)
    0x81, 0x00,             //      Input (Data, Array, Abs): Instantiates input packet fields based on the above report size, count, logical min/max, and usage.
    0x19, 0x01,             //      Usage Minimum 
    0x29, 0x40,             //      Usage Maximum 	//64 output usages total (0x01 to 0x40)
    0x91, 0x00,             //      Output (Data, Array, Abs): Instantiates output packet fields.  Uses same report size and count as "Input" fields, since nothing new/different was specified to the parser since the "Input" item.
    0xC0}                   // End Collection
};                  


// Array of configuration descriptors
ROM BYTE *ROM USB_CD_Ptr[]=
{
    (ROM BYTE *ROM)&configDescriptor1
};

// Array of string descriptors
ROM BYTE *ROM USB_SD_Ptr[]=
{
    (ROM BYTE *ROM)&sd000,
    (ROM BYTE *ROM)&sd001,
    (ROM BYTE *ROM)&sd002,
    (ROM BYTE *ROM)&sd003
};

ROM BYTE *ROM USB_SD_Ptr_p0[]=
{
    (ROM BYTE *ROM)&sd000,
    (ROM BYTE *ROM)&sd001,
    (ROM BYTE *ROM)&sd002_p0,
    (ROM BYTE *ROM)&sd003
};

ROM BYTE *ROM USB_SD_Ptr_p1[]=
{
    (ROM BYTE *ROM)&sd000,
    (ROM BYTE *ROM)&sd001,
    (ROM BYTE *ROM)&sd002_p1,
    (ROM BYTE *ROM)&sd003
};

ROM BYTE *ROM USB_SD_Ptr_p2[]=
{
    (ROM BYTE *ROM)&sd000,
    (ROM BYTE *ROM)&sd001,
    (ROM BYTE *ROM)&sd002_p2,
    (ROM BYTE *ROM)&sd003
};

ROM BYTE *ROM USB_SD_Ptr_p3[]=
{
    (ROM BYTE *ROM)&sd000,
    (ROM BYTE *ROM)&sd001,
    (ROM BYTE *ROM)&sd002_p3,
    (ROM BYTE *ROM)&sd003
};

ROM BYTE *ROM USB_SD_Ptr_p4[]=
{
    (ROM BYTE *ROM)&sd000,
    (ROM BYTE *ROM)&sd001,
    (ROM BYTE *ROM)&sd002_p4,
    (ROM BYTE *ROM)&sd003
};

ROM BYTE *ROM USB_SD_Ptr_p5[]=
{
    (ROM BYTE *ROM)&sd000,
    (ROM BYTE *ROM)&sd001,
    (ROM BYTE *ROM)&sd002_p5,
    (ROM BYTE *ROM)&sd003
};

ROM BYTE *ROM USB_SD_Ptr_p6[]=
{
    (ROM BYTE *ROM)&sd000,
    (ROM BYTE *ROM)&sd001,
    (ROM BYTE *ROM)&sd002_p6,
    (ROM BYTE *ROM)&sd003
};

ROM BYTE *ROM USB_SD_Ptr_p7[]=
{
    (ROM BYTE *ROM)&sd000,
    (ROM BYTE *ROM)&sd001,
    (ROM BYTE *ROM)&sd002_p7,
    (ROM BYTE *ROM)&sd003
};

ROM BYTE *ROM USB_SD_Ptr_p8[]=
{
    (ROM BYTE *ROM)&sd000,
    (ROM BYTE *ROM)&sd001,
    (ROM BYTE *ROM)&sd002_p8,
    (ROM BYTE *ROM)&sd003
};

ROM BYTE *ROM USB_SD_Ptr_p9[]=
{
    (ROM BYTE *ROM)&sd000,
    (ROM BYTE *ROM)&sd001,
    (ROM BYTE *ROM)&sd002_p9,
    (ROM BYTE *ROM)&sd003
};

#endif
