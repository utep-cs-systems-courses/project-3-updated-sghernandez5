
	.arch msp430g2553
	.p2align 1,0
	.text

	.extern red_on
	.extern led_update
	.extern led_changed
	
jt:
	.word case0		;state 0
	.word case1		;state 1
	.word case2		;state 2
	.word case3 		;state 3
	
	.global dim75
	
dim75:					
	mov.b #0, R12			; dimState
	cmp #5, R12			; dimState - 5
	jc out 				;

	mov.b R12, R14			; 

	add.b R14, R14			;

	mov  jt(R14), R0		;

case0:
	mov.b #0, &red_on		;
	mov.b #1, R12			;
	jmp  out			; 
	
case1:
	mov.b #1, &red_on		;
	mov.b #2, R12			;
	jmp out				;
case2:
	mov.b #1, &red_on		;
	mov.b #3, R12			;
	jmp out				;
case3:
	mov.b #1, &red_on		;
	mov.b #0, R12			;
	jmp out				;
out:
	mov #1, &led_changed		;
	call #led_update		;
	pop r0				; 
