; _exit.s
; Written by Emanuele Fornara

	.export		__exit
	.import		xv65_ret_res

	.include	"xv65.inc"

.segment	"CODE"

; int __fastcall__ _exit(int status)
__exit:
	ldy	#REQ_EXIT
	sty	REQPUT
	sta	REQPUT
	stx	REQPUT
	stx	REQEND
	jmp	xv65_ret_res
