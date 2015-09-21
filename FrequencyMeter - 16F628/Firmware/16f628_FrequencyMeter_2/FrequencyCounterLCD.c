//  http://www.moty22.co.uk/lcd_counter.php
//
//
//          LCD counter             
//
// 
// Compile with free Hi Tech that comes with MPLAB . 
// This code is free to use, for more info   http://www.moty22.co.uk       
   
#define _LEGACY_HEADERS
   
#include <htc.h>

#define RS RA0
#define EN RA1
#define _XTAL_FREQ 400000

//prototypes
void display(char fig);
void init(void);
void main(void);
void clock(void);
void clear(void);

__CONFIG(WDTDIS & UNPROTECT & LVPDIS & INTCLK);	//INTIO // & BORDIS & PWRTEN

unsigned char d1,d2,d3,d4,d5,d6,d7,period;

void init(void){

	CMCON = 0b00000111;		//comparator off
	T1CON = 0b1110;        //TMR1 prescale 1:1, osc=on
	TRISB = 0b11000000;		 //RB 1,5,6,7 inputs
	TRISA = 0b11110000;
	OPTION = 0b10100000;	//TMR1 pre=1:2
	
	//LCD init
	__delay_ms(100);
	PORTA=0;
	PORTB=2; clock();	//4 bit
	PORTB=2; clock();	//function set: 4 bit
	PORTB=8; clock();	//function set: 1 line=0, 2 lines=8
	__delay_us(25); __delay_us(25);
	PORTB=0; clock();	//display set:
	PORTB=12; clock();	//display set:  curzor off=12, curzor on=14, curzor on and flashing=15
	__delay_us(25); __delay_us(25);
	PORTB=0; clock(); PORTB=1; clock();	//display clear
	__delay_ms(2);
	PORTB=0; clock();	//Entry mode:
	PORTB=6; clock();	//Entry mode:increment address	
}

void main(void){
	unsigned long total;
	unsigned int freq2;
	unsigned char freq1,nz;	
	init();
for(;;){	
	freq1 = 0;
	freq2 = 0;
	TMR1L = 0;
	TMR1H = 0;
	TMR1IF = 0;
	nz=0;
	TMR1ON = 1;		// open gate
	TMR0 = 0;		// start count
	T0IF=0;
	
	while (!TMR1IF){		//loop for 2 second
		if (T0IF){++freq2; T0IF=0;}
	}
	
	freq1=TMR0;		//stop count=copy reg
	TMR1ON = 0;		//close gate 

	total=(unsigned long)freq1 + (unsigned long)freq2 * 256; //binary to decimal
	d7=total/1000000+48;
	d6=(total/100000) %10+48;
	d5=(total/10000) %10+48;
	d4=(total/1000) %10+48;
	d3=(total/100) %10+48;
	d2=(total/10) %10+48;
	d1=total %10+48;
	clear();
	
	display(32);	//blank
	display(32);	//blank
			//remove leading zeros				
	if(d7 == 48){display(32); display(32);}
		else{display(d7); display(44); nz=1;} //44=,
	if(d6 == 48 && nz==0){display(32);}	
		else{display(d6); nz=1;}
	if(d5 == 48 && nz==0){display(32);}	
		else{display(d5); nz=1;}
	if(d4 == 48 && nz==0){display(32); display(32);}	
		else{display(d4); display(44);}		

	display(d3);
	display(d2);
	display(d1);
	display(32);	//blank
	display(72);	//H
	display(122);	//z
	
	//new line
	PORTB=12; clock(); PORTB=0; clock();
	__delay_ms(2);	//2ms
	
	nz=0;
	if(total<1000){total=1000000/total; period=117;}	//us
	else{total=1000000000/total; period=110;}			//ns
	
	d7=total/1000000+48;
	d6=(total/100000) %10+48;
	d5=(total/10000) %10+48;
	d4=(total/1000) %10+48;
	d3=(total/100) %10+48;
	d2=(total/10) %10+48;
	d1=total %10+48;
	
	display(32);	//blank
	display(32);	//blank
			//remove leading zeros				
	if(d7 == 48){display(32); display(32);}
		else{display(d7); display(44); nz=1;} //44=,
	if(d6 == 48 && nz==0){display(32);}	
		else{display(d6); nz=1;}
	if(d5 == 48 && nz==0){display(32);}	
		else{display(d5); nz=1;}
	if(d4 == 48 && nz==0){display(32); display(32);}	
		else{display(d4); display(44);}		

	display(d3);
	display(d2);
	display(d1);
	display(32);	//blank
	display(period);	//n, u
	display(115);	//s	     	       
	
        RB0 = 1;
        __delay_ms(1);
        RB0 = 0;
        __delay_ms(1);
        
        RB7 = 1;
        __delay_ms(1);
        RB7 = 0;
        __delay_ms(1);        	
	}
}

void clock(void){
	EN=1;
	__delay_us(25);
	EN=0;
	__delay_us(25);
}

void clear(void){
	RS=0;
	PORTB=0; clock(); PORTB=1; clock(); 	//clear display
	PORTB=0; clock(); PORTB=2; clock();	//return home
	__delay_ms(2);					//2ms
}

void display(char fig){
	RS=1;
	PORTB=(fig >> 4); clock();
	PORTB=fig & 0b00001111; clock();
	RS=0;
}						
