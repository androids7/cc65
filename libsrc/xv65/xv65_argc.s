; xv65_argc.s
; Written by Emanuele Fornara

	.export		_xv65_argc

	.include	"xv65.inc"

.segment	"CODE"

; unsigned int xv65_argc(void)
_xv65_argc:
	lda	#REQ_ARGC
	sta	REQPUT
	sta	REQEND
	lda	REQDAT
	ldx	REQDAT+1
	rts
