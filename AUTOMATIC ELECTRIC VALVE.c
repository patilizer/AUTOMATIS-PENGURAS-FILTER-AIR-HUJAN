/*******************************************************
Date    : 23/02/2020
Chip type               : ATtiny85
AVR Core Clock frequency: 1,000000 MHz
Memory model            : Small
External RAM size       : 0
Data Stack size         : 128
*******************************************************/

#include <tiny85.h>
#include <sfr_defs.h>
#include <delay.h> 
#include <sleep.h>

#define level   PINB.3  //water level   (input)
#define valve   PINB.0  //electric valve    (output)

// Declare your global variables here
//unsigned char temp=0;
//unsigned char batas_tunggu=0;

void main(void)
{
// Declare your local variables here

// Crystal Oscillator division factor: 1
#pragma optsize-
CLKPR=(1<<CLKPCE);
CLKPR=(0<<CLKPCE) | (0<<CLKPS3) | (0<<CLKPS2) | (0<<CLKPS1) | (0<<CLKPS0);
#ifdef _OPTIMIZE_SIZE_
#pragma optsize+
#endif  

// Input/Output Ports initialization
// Port B initialization
// Function: Bit5=In Bit4=In Bit3=In Bit2=Out Bit1=Out Bit0=Out 
DDRB=(0<<DDB5) | (0<<DDB4) | (0<<DDB3) | (1<<DDB2) | (1<<DDB1) | (1<<DDB0);
// State: Bit5=T Bit4=T Bit3=T Bit2=0 Bit1=0 Bit0=0 
PORTB=(1<<PORTB5) | (1<<PORTB4) | (1<<PORTB3) | (0<<PORTB2) | (0<<PORTB1) | (0<<PORTB0);

// Timer/Counter 0 initialization
// Clock source: System Clock
// Clock value: Timer 0 Stopped
// Mode: Normal top=0xFF
// OC0A output: Disconnected
// OC0B output: Disconnected
TCCR0A=(0<<COM0A1) | (0<<COM0A0) | (0<<COM0B1) | (0<<COM0B0) | (0<<WGM01) | (0<<WGM00);
TCCR0B=(0<<WGM02) | (0<<CS02) | (0<<CS01) | (0<<CS00);
TCNT0=0x00;
OCR0A=0x00;
OCR0B=0x00;

//Power Management Sleep Mode
MCUCR=(0<<ISC01) | (0<<ISC00) | (1<<SE) | (1<<SM1) | (0<<SM0);  //idle mode

while (1)
      {
        if(level==1)    //PINB.3 
        {  
        delay_ms(10);
        valve=1;        //PINB.0
        delay_ms(10);
        }
        else
        {
        valve=0;
        } 

        PINB.1=1;      
        delay_ms(10);
        
        while(bit_is_set(PINB,3));  //tunggu water level cpen=0/clear
        
        PINB.1=0;
        delay_ms(10);
        
        valve=0; 
      }
}
