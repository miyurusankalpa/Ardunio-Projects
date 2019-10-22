;
; AssemblerApplication2.asm
;
; Created: 9/17/2019 2:36:48 PM
; Author : miyuru
;

; Replace with your application code
       CBI  DDRD,7	;make PD7 an input 7
       SBI  DDRB,0	;make PB0 an output 8
	   LDI  R16, 0  ;set led off
	   LDI  R18, 1  ;OR
	   LDI  R17, 255 ;set loop cycle
AGAIN: OUT  PORTB, R16  ;send r16 to led
	   SBIC PIND,7   	;skip next if PB0 is clear
       RJMP OVER		;(JMP is OK too)
       RJMP AGAIN		;we can use JMP too
OVER:  EOR R16,R18      ; OR r18
       RJMP loop		;jumpto loop
loop:  NOP        
       DEC r17  ;dec
       BRNE loop
	   LDI r17, 255 ;set loop cycle
 RJMP AGAIN
