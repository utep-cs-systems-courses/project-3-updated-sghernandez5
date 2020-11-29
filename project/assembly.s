	.arch msp430g2553
	.p2align 1,0
	.text
	
jt:
	.word case0		;state 0
	.word case1		;state 1
	.word case2		;state 2
	.word case3		;state 3
	.word case4 		;state 4
	
	.global led_advance()	
	
led_advance()			;transition led dimness state method 
	sub #4,R1 			;allocate space in the stack for count and state
	mov #0, 0(r1)			;  0(r1) is count
	mov #0, 2(r1)			; 2(r1) is state
