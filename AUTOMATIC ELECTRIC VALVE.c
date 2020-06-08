/*******************************************************
Date    : 27/02/2020
Chip type               : ATtiny85
AVR Core Clock frequency: 1,000000 MHz
Memory model            : Small
External RAM size       : 0
Data Stack size         : 128
*******************************************************/

#include <tiny85.h>
#include <sfr_defs.h>
//#include <sleep.h>
#include <delay.h>


// Declare your global variables here

void main(void)
{
// Declare your local variables here

// Input/Output Ports initialization
// Port B initialization
// Function: Bit5=Out Bit4=Out Bit3=Out Bit2=In Bit1=In Bit0=In 
DDRB=(1<<DDB5) | (1<<DDB4) | (1<<DDB3) | (0<<DDB2) | (0<<DDB1) | (0<<DDB0);
// State: Bit5=0 Bit4=0 Bit3=0 Bit2=P Bit1=P Bit0=P 
PORTB=(0<<PORTB5) | (0<<PORTB4) | (0<<PORTB3) | (1<<PORTB2) | (1<<PORTB1) | (1<<PORTB0);    

while (1)
      {      
        while(bit_is_set(PINB,0));
        PINB.3=1;
        while(bit_is_clear(PINB,0));
        PINB.3=0;
        
        /*
            
        if(PINB.0==1)    //PINB.0 
        {  
        delay_ms(10);
        PINB.3=1;        //PINB.3
        delay_ms(10);
        }
        
        if(PINB.0==0);
        {
        delay_ms(10);
        PINB.3=0;     
        delay_ms(10);
        } 
        
        */
        
        

      }
}
