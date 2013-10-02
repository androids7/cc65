; close_dup.s
; Written by Emanuele Fornara

	.export		_close
	.export		_dup
	.import		xv65_ret_res

	.include	"xv65.inc"

.segment	"CODE"

; int __fastcall__ dup(int fd)
_dup:
	ldy	#REQ_DUP
	bne	j0
; int __fastcall__ close(int fd)  [unistd.h]
_close:
	ldy	#REQ_CLOSE
j0:	sty	REQPUT
	sta	REQPUT
	sta	REQEND
	jmp	xv65_ret_res
