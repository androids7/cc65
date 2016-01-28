; Keep updating a character on the screen (infinite loop). \
; To stop the program press a soft key.
; CPU Instructions: INC (INCrement memory), NOP (No OPeration) \
; and JMP (JuMP).
; IO: Writing into 2:18 suspends the CPU until the screen \
; has been redrawn (refresh rate is 10 frames per second).

	.include "io2.inc"

.code

L1:	inc	CONVIDEO
	sta	FRMDRAW
	nop
	jmp	L1
