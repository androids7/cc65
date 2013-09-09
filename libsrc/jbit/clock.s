;
; Written by Emanuele Fornara
;
; clock_t clock (void);
;

	.export		_clock
	.importzp	sreg

	.include	"jbit.inc"


.code

.proc	_clock

	; ask for time in 1/100th of a second relative to the
	; time the IO chip has been reset

	lda	#REQ_TIME
	sta	REQPUT
	lda	#TIME_RESET
	sta	REQPUT
	lda	#TIME_100
	sta	REQPUT
	sta	REQEND

	; the 8 bytes (!) result is located at REQDAT
	; (least significant bytes first)

	lda	REQDAT+3
	sta	sreg+1
	lda	REQDAT+2
	sta	sreg
	ldx	REQDAT+1
	lda	REQDAT+0
	rts

.endproc

