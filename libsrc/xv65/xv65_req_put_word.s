; xv65_req_put_word.s
; Written by Emanuele Fornara

	.export		_xv65_req_put_word

	.include	"xv65.inc"

.segment	"CODE"

_xv65_req_put_word:
	sta	REQPUT
	stx	REQPUT
	rts
