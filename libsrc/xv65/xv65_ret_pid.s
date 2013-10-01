; xv65_ret_pid.s
; Written by Emanuele Fornara

	.export		xv65_ret_pid
	.importzp	sreg

	.include	"xv65.inc"

.segment	"CODE"

xv65_ret_pid:
	lda	REQDAT+3
	sta	sreg+1
	lda	REQDAT+2
	sta	sreg
	ldx	REQDAT+1
	lda	REQDAT
	rts
