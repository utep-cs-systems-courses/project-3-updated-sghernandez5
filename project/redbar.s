	.arch msp430g2553
	.p2align 1,0
	
	.text
	.extern drawPixel
	
	.global redbar
redbar:
	sub #6, r1		;center, c and sum of center+c
	mov #50, 0(r1) 		; center
	mov #0, 2(r1)		; c
	mov r12, r15		; color in r14
	
loop:   cmp #40, 2(r1)		; a-b or 2(r1)-40
	jc body			; no carry a<=b signed comparison
	jmp end			; 
body:
	mov 2(r1), 6(r1)	; 6(r1) = c
	add 0(r1), 6(r1)	; center+c
	mov 6(r1), r12		; r12 = center+c
	mov #150, r13
        mov r15, r14		; 
	call #drawPixel 	; r12= center+c, r13 = 150, r14= color
	mov 6(r1), r12		;
	mov r15, r14
	mov #151, r13		;
	call #drawPixel 	;
	mov 6(r1), r12		;
	mov r15, r14
	mov #152, r13		;
	call #drawPixel 	;
	mov 6(r1), r12		;
	mov r15, r14		; 
	mov #153, r13		;
	call #drawPixel 	;
	mov 6(r1), r12		;
	mov r15, r14
	mov #154, r13		;
	call #drawPixel  	;
	add #1,2(r1)		; c++
	jmp loop		; 
end:
	add #6, r1		; free local variables
	pop r0			; 
	
