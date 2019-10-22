/*
 * GccApplication1.c
 *
 * Created: 8/31/2018 12:57:13 PM
 * Author : miyuru
 */ 
 
#define F_CPU 16000000ul
#include <avr/io.h>
#include <util/delay.h>
int i=0;


int main(void)
{
	DDRB |= (1 << DDB5); //port 13 output
	DDRD = 0x0; //all as input
	PORTD |= 0x80; //PORTD5 as pull up 
	
	//DDRD|= (0 << ); /* Set PB5 for input
	
	
	
	PORTB |= (0 << PB5); /* LED off */
	
    /* Replace with your application code */
    while (1) 
    {
		
		 if ((PIND & (0x80)) == 0)
		 {
			 _delay_ms(200); /* Wait 500 milliseconds */
			 //incrment
			 i++;
		 }
		
		 
		 
		 if(i==5)
		 {
			 PORTB |= (1 << PB5); /* LED on */
			 i=0;
		 }
		  else
		  {
			  PORTB &= ~(1 << PB5); /* LED off */
		  }
	}
}

