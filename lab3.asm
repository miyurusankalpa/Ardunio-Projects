
.ORG 0	;location for reset
	JMP	MAIN
.ORG 0x02 ;loc. for external INT0
  JMP EX0_ISR
.ORG 0x04 ;loc. for external INT1
  JMP EX1_ISR

MAIN:
  LDI R20,HIGH(RAMEND)
  OUT SPH,R20
  LDI R20,LOW(RAMEND)
  OUT SPL,R20 ;initialize stack

     LDI R16,0
     LDI R17,1
	 LDI r18, 255 ;set loop cycle


 SBI  DDRB,0
 SBI  DDRB,1
 SBI  DDRB,2	;make PD7 an output 7

 LDI R20,10 ;set falling edge
 STS EICRA,R20

  clr R20

  LDI R20,3 ;enable INT0 and INT1
  OUT EIMSK,R20

	SEI	
HERE:	JMP	HERE	

EX0_ISR:
    ADD R16,R17
	OUT PORTB,R16
	RJMP loop
	RETI	

EX1_ISR:
    SUB R16,R17
	OUT PORTB,R16
	RJMP loop
	RETI	

loop:  NOP        
       DEC r18  ;dec
       BRNE loop
	   LDI r18, 255 ;set loop cycle
	RETI