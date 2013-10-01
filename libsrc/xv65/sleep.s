; sleep.s
; Written by Emanuele Fornara

	.export		_sleep
	.import		_xv65_req_put_word

	.include	"xv65.inc"

.segment	"CODE"

; unsigned __fastcall__ sleep (unsigned seconds)  [unistd.h]
_sleep:
	ldy	#REQ_SLEEP
	sty	REQPUT
	jsr	_xv65_req_put_word
	sta	REQEND
	lda	REQRES
	beq	@r0
	lda	REQDAT
	ldx	REQDAT+1
	rts
@r0:	tax
	rts
