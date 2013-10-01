; close.s
; Written by Emanuele Fornara

	.export		_close
	.import		xv65_ret_res

	.include	"xv65.inc"

.segment	"CODE"

; int __fastcall__ close(int fd)  [unistd.h]
_close:
	ldy	#REQ_CLOSE
	sty	REQPUT
	sta	REQPUT
	sta	REQEND
	jmp	xv65_ret_res
