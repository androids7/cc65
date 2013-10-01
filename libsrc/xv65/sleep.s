; sleep.s
; Written by Emanuele Fornara

	.export		_sleep

	.include	"xv65.inc"

.segment	"CODE"

; unsigned __fastcall__ sleep (unsigned seconds)  [unistd.h]
_sleep:
	ldy	#REQ_SLEEP
	sty	REQPUT
	sta	REQPUT
	stx	REQPUT
	stx	REQEND
	lda	REQRES
	beq	@r0
	lda	REQDAT
	ldx	REQDAT+1
	rts
@r0:	tax
	rts
