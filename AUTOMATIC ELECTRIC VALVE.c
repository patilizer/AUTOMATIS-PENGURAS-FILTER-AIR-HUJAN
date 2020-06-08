/*******************************************************
Date    : 02/03/2020
Chip type               : ATtiny85
AVR Core Clock frequency: 8,000000 MHz
Memory model            : Small
External RAM size       : 0
Data Stack size         : 128
*******************************************************/

#include <tiny85.h>
#include <iobits.h>
#include <delay.h>
#include <sleep.h>

// Declare your global variables here
unsigned int batas_waktu=0;
unsigned int temp=0;

// Timer1 overflow interrupt service routine
interrupt [TIM1_OVF] void timer1_ovf_isr(void)
{
// Place your code here
TCNT1=0;
// Place your code here
    temp++;
    if(temp==1000)
    {
    batas_waktu++;
    temp=0;
    }

}

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
// State: Bit5=P Bit4=P Bit3=P Bit2=0 Bit1=0 Bit0=0 
PORTB=(1<<PORTB5) | (1<<PORTB4) | (0<<PORTB3) | (0<<PORTB2) | (0<<PORTB1) | (0<<PORTB0);  

// Timer/Counter 1 initialization
// Clock source: System Clock
// Clock value: 125,000 kHz
// Mode: Normal top=0xFF
// OC1A output: Disconnected
// OC1B output: Disconnected
// Timer Period: 2,048 ms
// Timer1 Overflow Interrupt: On
// Compare A Match Interrupt: Off
// Compare B Match Interrupt: Off
PLLCSR=(0<<PCKE) | (0<<PLLE) | (0<<PLOCK);

TCCR1=(0<<CTC1) | (0<<PWM1A) | (0<<COM1A1) | (0<<COM1A0) | (0<<CS13) | (1<<CS12) | (0<<CS11) | (0<<CS10);
GTCCR=(0<<TSM) | (0<<PWM1B) | (0<<COM1B1) | (0<<COM1B0) | (0<<PSR1) | (0<<PSR0);
TCNT1=0x00;
OCR1A=0x00;
OCR1B=0x00;
OCR1C=0x00;

// Timer(s)/Counter(s) Interrupt(s) initialization
TIMSK=(0<<OCIE1A) | (0<<OCIE1B) | (0<<OCIE0A) | (0<<OCIE0B) | (1<<TOIE1) | (0<<TOIE0);  

//Power Management Sleep Mode
MCUCR=(0<<ISC01) | (0<<ISC00) | (1<<SE) | (1<<SM1) | (0<<SM0);  //idle mode


// Global enable interrupts
#asm("sei")

while (1)
      {
      // Place your code here
        if(PINB.3==0)
        {
        /* Enter sleep mode */        
        powerdown();    //power down mode 
        }
        
        SETBIT(PORTB,0);
              
        while(batas_waktu<=1200)    //5 menit menyala
        {
        SETBIT(PORTB,0);              
        }
        
        
        SETBIT(PORTB,3);
        delay_ms(500);
        CLRBIT(PORTB,3);
        delay_ms(500); 
        batas_waktu=0;
        CLRBIT(PORTB,0);
        
        /* Enter sleep mode */        
        powerdown();    //power down mode 

      }
}
