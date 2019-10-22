#include <avr/io.h>
#include <util/delay.h>

#define DOT_LENGTH  300         /* Define the length of a "dot" time in msec */

void dot(void);
void dash(void);
void makeOutput(char);
char checkInput(char);

int main(void)
{

    // Initialize appropriate DDR registers
	DDRB |= (1 << DDB0); /* Set PB0 for output */
	//DDRB |= (0 << DDB2); /* Set PB2 for input */
	
    // Initialize the LED output to 0
	PORTB |= (1 << PB0); /* LED off */
	
    // Enable the pull-up resistors for the 
    // 3 button inputs 
	

    // Loop forever
    while (1) {                 
    
	//check input of PB2 (output - S)
	if(checkInput(2)==1)
	 {
		dot();
		dot();
		dot();
	 }
	 
	 _delay_ms(DOT_LENGTH);
	 
	 //check input of PB3 (output - O)
	if(checkInput(3)==1)
	 {
		dash();
		dash();
		dash();
	 }
	 
	 _delay_ms(DOT_LENGTH);
	 
	//check input of PB4 (output - C)
	if(checkInput(4)==1)
	 {
		dash();
		dot();
		dash();
		dot();
	 }

	 _delay_ms(DOT_LENGTH);
	
	// Use if statements and the checkInput()
	//  function to determine if a button
	//  is being pressed and then output
	//  the correct dot/dash sequence by
	//  calling the dot(), dash(), and 
	//  using appropriate delay functions

    }

    return 0;   /* never reached */
}

/*
  dot() - Makes the output LED blink a "dot".
  Write code to generate a dot by turning the
  output ON and OFF with appropriate delays.
  Be sure you don't forget to also delay an
  appropriate time after you turn the output off
*/
void dot()
{
	makeOutput(1);
	_delay_ms(DOT_LENGTH);
	makeOutput(0);
	_delay_ms(DOT_LENGTH);
}

/*
  dash() - Makes the output LED blink a "dash".
  Write code to generate a dash by turning the
  output ON and OFF with appropriate delays.
  Be sure you don't forget to also delay
  appropriate time after you turn the output off
*/
void dash()
{
	makeOutput(1);
	_delay_ms(DOT_LENGTH*3);
	makeOutput(0);
	_delay_ms(DOT_LENGTH);
}

/*
  makeOutput() - Changes the output bit to either a zero 
  or one, based on the input argument "value".
  
  If the argument is zero, turn the output OFF,
  otherwise turn the output ON. 
  
  Do not use any delays here.  Just use bit-wise operations
  to make the appropriate PORT bit turn on or off.
*/
void makeOutput(char value)
{
	if(value==0) 
		PORTB &= ~(1 << PB0); /* LED off */ 
	else
		PORTB |= (1 << PB0); /* LED on */
}

/*
  checkInput(bit) - Checks the state of the input bit specified by the
  "bit" argument (0-7), and returns either 0 or 1 depending on its state.
  
  COMPLETE -- DO NOT CHANGE
*/
char checkInput(char bit)
{
    if ((PIND & (1 << bit)) != 0)
        return(1);
    else
        return(0);
}
