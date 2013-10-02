; _systime.s
; Written by Emanuele Fornara

	.export		__systime
	.importzp	sreg

	.include	"xv65.inc"

.segment	"CODE"

__systime:
	lda	#REQ_TIME
	sta	REQPUT
	sta	REQEND
	lda	REQRES
	beq	r0
	lda	#$ff
	sta	sreg
	sta	sreg+1
	tax
	rts
r0:	lda	REQDAT
	ldx	REQDAT+1
	ldy	REQDAT+2
	sty	sreg
	ldy	REQDAT+3
	sty	sreg+1
	rts
