; xv65_ret_long.s
; Written by Emanuele Fornara

	.export		xv65_ret_long
	.importzp	sreg

	.include	"xv65.inc"

.segment	"CODE"

xv65_ret_long:
	lda	REQDAT+3
	sta	sreg+1
	lda	REQDAT+2
	sta	sreg
	ldx	REQDAT+1
	lda	REQDAT
	rts
