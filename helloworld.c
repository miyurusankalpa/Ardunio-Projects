#include <avr/io.h>
#include <util/delay.h>

int main(void)
{

    // Initialize appropriate DDR registers
	DDRB |= (1 << DDB0); /* Set PB0 for output */
	
    // Initialize the LED output to 0
	PORTB |= (1 << PB0); /* LED off */
	

    // Loop forever
    while (1) {                 
    
	PORTB |= (1 << PB0); /* LED on */
	_delay_ms(500); /* Wait 500 milliseconds */
	PORTB &= ~(1 << PB0); /* LED off */
	_delay_ms(500); /* Wait 500 milliseconds */

    }

    return 0;   /* never reached */
}
