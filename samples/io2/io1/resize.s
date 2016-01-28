; Resize the console.

	.include "io2.inc"

.code

	ldx	#0
	stx	CONCOLS
	stx	CONROWS
	lda	#'X'
	sta	CONCCHR
	ldy	CONCOLS
	dey
	sty	CONCX
	sta	CONCCHR
	ldy	CONROWS
	dey
	sty	CONCY
	sta	CONCCHR
	stx	CONCX
	sta	CONCCHR
	brk
