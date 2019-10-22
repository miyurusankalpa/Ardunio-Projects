#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <avr/interrupt.h>
#define F_CPU 16000000


void init_lcd(void);
void moveto(unsigned char, unsigned char);
void stringout(char *);
void writecommand(unsigned char);
void writedata(unsigned char);
void writenibble(unsigned char);


int sec1 = 5;
int sec2 =0;
int min1 = 5;
int min2=9;
int hour1 = 1;
int hour2=1;
char M_1='P';
char M_2='P';

int min1_a  = 0;
int min2_a  = 0;
int hour1_a = 0;
int hour2_a = 0;


int button_1_clicks = 0;
int button_2_clicks = 0;
int button_3_clicks = 0;
int button_4_clicks = 0;

int clock_setmode = 0;
int alarm_setmode = 0;


ISR(TIMER1_COMPA_vect)
{
	if(clock_setmode==0)
	 {	
		sec2= sec2+1;
		
		if(sec2 ==10){
			
			sec2=0;
			sec1 = sec1 + 1;
		}
		
		if (sec1 ==6)
		{
			sec1 = 0;
			sec2= 0;
			
			min2 = min2 + 1;		
		}
		
		if (min2 ==10)
		{
			min2 = 0;
			sec1 =0;
			sec2 =0;
			min1 = min1 +1;
		}
		
		if (min1 == 6)
		{
			min1 = 0;
			min2 = 0;
			sec1 =0;
			sec2=0;
			hour2 = hour2 +1;
		}

		if(hour2 ==10)
		{
			hour2=0;
			min1 = 0;
			min2 = 0;
			sec1 =0;
			sec2=0;
			hour1=hour1 + 1;
		}
			
		if(hour1==1 && hour2==3)
		{
			min1 = 0;
			min2 = 0;
			sec1 =0;
			sec2=0;
			
			hour2=1;
			hour1=0;
		}
			
			
		if (hour1==1 && hour2==2 && min1==0 && min1 ==0 && sec1==0 && sec2==0)
		{
			if (M_1 =='A')
			{
				M_1='P';
			} else M_1 ='A';
		}
			
			
			
		//_ms_delay(100);
		
		//moveto(1,0);
		//sprintf(out, " %d%d:%d%d:%d%d",  hour1,hour2 ,min1,min2, sec1,sec2);
		//stringout(out);
		
		//	sec
	 }
}

int main(void) {

	DDRC = 0x00;
		
	int a=1;
	char out[100];

	/* Main program goes here */

	init_lcd();
	  
	DDRB &= 0x03;
	PORTB |= 0xFC;

	 TCCR1B = (1<<WGM12);
	 OCR1A = 15625;
	 TIMSK1 = (1<<OCIE1A);

	  sei();
	  

	 TCCR1B |= (1<<CS12) | (1<<CS10);
	 


		//stringout("Clock");
		//moveto(0,0);
		 
		
	while (1) {
		
		//sec2++;
		//sec2 = 1;
		moveto(0,0);
		
		if(alarm_setmode==0){
			sprintf(out, "Clock:%d%d:%d%d:%d%d%cM",  hour1,hour2 ,min1,min2, sec1,sec2,M_1);
			stringout(out);
		}
		
		//moveto(0,0);
		//sprintf(out, "Alarm:%d%d:%d%d:%cM",  hour1_a,hour2_a ,min1_a,min2_a,M_2);
		//stringout(out);
		
		
		if((PINC & (0x01)) != 0)
		{
		   _delay_ms(5000);
		   
		   button_1_clicks++;
		   if (button_1_clicks == 1 )
		   {
			   clock_setmode=1;
				moveto(1,0);
				stringout("Clock set ");
		   }
		   
		   if (button_1_clicks == 2 )
		   {
			   clock_setmode=0;
			   alarm_setmode=1;
			   
			   moveto(0,0);
			   stringout("teeeest");
			   moveto(1,0);
			   stringout("Alarm set ");
		   }
		   
		   
		 if (button_1_clicks == 3 )
		{
		 alarm_setmode=0;
		 button_1_clicks = 0;
		 moveto(1,0);
			stringout("                ");
			
		}
	}
		
		if((PINC & (0x02)) != 0)
		{
			 _delay_ms(5000);
			 
			 button_2_clicks++;
			 
			if (clock_setmode == 1)
			{
				
				hour2++;
				if(hour2 ==10)
				{
					hour2=0;
					//min1 = 0;
					//min2 = 0;
					//sec1 =0;
					//sec2=0;
					hour1=hour1 + 1;
				}
				
				
				if(hour1==1 && hour2==3){
					
					
					//min1 = 0;
					//min2 = 0;
					//sec1 =0;
					//sec2=0;
					
					hour2=1;
					hour1=0;
					
					
					
					
				}
				
				
				
			}
			
			
		}
		if((PINC & (0x04)) != 0)
		{
			_delay_ms(5000);
			
			button_3_clicks++;
			
			if (clock_setmode == 1)
			{
				
				min2++;
				if (min2 ==10)
				{
					min2 = 0;
					//sec1 =0;
					//sec2 =0;
					min1 = min1 +1;
				}
				
				if (min1 == 6)
				{
					min1 = 0;
					min2 = 0;
					//sec1 =0;
					//sec2=0;
					//hour2 = hour2 +1;
				}
				
				
			}
			
			
		}
		if((PINC & (0x08)) != 0)
		{
			_delay_ms(5000);
			
			button_4_clicks++;
			
			if (clock_setmode == 1)
			{
			  if (M_1 =='A')
			  {
				  M_1='P';
			  }
			  else M_1 ='A';
			}
		}
		//_delay_ms(2000);
					   // Loop forever
	   }

		return 0;   /* never reached */
}

/*
  init_lcd - Configure the I/O ports and send the initialization commands
*/
void init_lcd()
{
    /* ??? */                   // Set the DDR register bits for ports B and D
	DDRD|=0xF0;
	DDRB|=0x03;
    _delay_ms(15);              // Delay at least 15ms

	
	writecommand(0x03);
    /* ??? */                   // Use writenibble to send 0011
    _delay_ms(5);               // Delay at least 4msec
	writecommand(0x03);
    /* ??? */                   // Use writenibble to send 0011
    _delay_us(120);             // Delay at least 100usec

    /* ??? */                   // Use writenibble to send 0011, no delay needed
	writecommand(0x03);

	writecommand(0x02);
    /* ??? */                   // Use writenibble to send 0010
    _delay_ms(2);               // Delay at least 2ms
    
    writecommand(0x28);         // Function Set: 4-bit interface, 2 lines
_delay_ms(2);
    writecommand(0x0f);         // Display and cursor on
_delay_ms(25); 

writecommand(0x01); 
_delay_ms(25); 
//writecommand(1);
}

/*
  moveto - Move the cursor to the row (0 or 1) and column (0 to 15) specified
*/
void moveto(unsigned char row, unsigned char col)
{
    /* Don't need this routine for Lab 5 */
	if(row==0){
		
		writecommand(0x80+col);
	}
	if(row==1){
		
		writecommand(0xc0+col);
	}
	
}

/*
  stringout - Write the string pointed to by "str" at the current position
*/
void stringout(char *str)
{
    /* Don't need this routine for Lab 5 */
	do{
		
		writedata(*str);
		str++;
		
	}while(*str!= '\0');
	
	
}

/*
  writecommand - Send the 8-bit byte "cmd" to the LCD command register
*/
void writecommand(unsigned char cmd)
{
	unsigned char temp;

PORTB&=~(0x01);
temp=cmd&0xF0;
writenibble(temp);
temp=cmd&0x0F;
temp=temp<<4;
writenibble(temp);
_delay_ms(3);

}

/*                                                                                                                                                                                                                        
  writedata - Send the 8-bit byte "dat" to the LCD data register
*/
void writedata(unsigned char dat)
{
unsigned char temp;

PORTB|=0x01;
temp=dat&0xF0;
writenibble(temp);
temp=dat&0x0F;
temp=temp<<4;
writenibble(temp);
_delay_ms(3);

}

/*
  writenibble - Send four bits of the byte "lcdbits" to the LCD
*/
void writenibble(unsigned char lcdbits)
{
PORTD = lcdbits;//&0xF0;
//PORTB |= 0x02;
PORTB &= ~(0x02);
PORTB |= 0x02;
PORTB &= ~(0x02);
}

