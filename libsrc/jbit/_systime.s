;
; Written by Emanuele Fornara
;
; time_t _systime (void);
;

	.export		__systime
	.importzp	sreg

	.include	"jbit.inc"


.code

.proc	__systime

	; ask for time in seconds relative to "epoch"

	lda	#REQ_TIME
	sta	REQPUT
	lda	#TIME_ABS
	sta	REQPUT
	lda	#TIME_1
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

