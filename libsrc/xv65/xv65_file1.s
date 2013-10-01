; xv65_file1.s
; Written by Emanuele Fornara

	.export		xv65_file1
	.import		_xv65_req_put_string
	.import		xv65_ret_res

	.include	"xv65.inc"

.segment	"CODE"

xv65_file1:
	sty	REQPUT
	jsr	_xv65_req_put_string
	sta	REQEND
	jmp	xv65_ret_res
