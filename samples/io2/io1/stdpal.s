; Show the standard palette.

	.include "io2.inc"

.code

	ldx	#1
	ldy	#0
	stx	CONCY
L1:	stx	CONCX
	sty	CONCBG
	inx
	iny
	cpy	#8
	bne	L1
	ldx	#1
	inc	CONCY
L2:	stx	CONCX
	sty	CONCBG
	inx
	iny
	cpy	#16
	bne	L2
	brk
