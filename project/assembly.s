
	.arch msp430g2553
	.p2align 1,0

	
	.data
dimState:
	.byte 0			; dimState = 0
	
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
	cmp #4, &dimState		;  dimState - 4
	jc out 				;
	mov.b &dimState, R12		; 
	add.b R12,R12
	mov.b  jt(R12), R0		;

case0:
	mov.b #1, &red_on		;
	mov.b #1, &dimState			;
	jmp  out			; 
	
case1:
	mov.b #1, &red_on		;
	mov.b #2, &dimState		;
	jmp out				;
case2:
	mov.b #1, &red_on		;
	mov.b #3, &dimState			;
	jmp out				;
case3:
	mov.b #0, &red_on		;
	mov.b #0, &dimState			;
	jmp out				;
out:
	mov.b #1, &led_changed		;
	call #led_update
	pop R0			; 
