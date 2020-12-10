
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
	cmp #4, &dimState		; dimState - 4 unsigned comparinson  a-b ,a>=b
	jc out 				; go out 
	mov.b  &dimState, r12		; r12 = dimState
	add  r12,r12			; r12*2
	mov  jt(r12), r0		;

case0:
	mov #1, &red_on			;turn on red	
	mov.b #1, &dimState		;set dimState to 1
	jmp  out			;go out
	
case1:
	mov #1, &red_on			;turn on red 
	mov.b #2, &dimState		;set dimState to 2
	jmp out				;go out
case2:
	mov #1, &red_on			;turn on red
	mov.b #3, &dimState		;set dimState to 3
	jmp out				;go out
case3:
	mov #0, &red_on			;turn off red
	mov.b #0, &dimState		;set dimState to 0 to repeat
	jmp out				;go out 
out:
	mov #1, &led_changed		;set led_changed to 1
	call #led_update		;call led_update to activate the red LED to on/off
	pop r0				
	
