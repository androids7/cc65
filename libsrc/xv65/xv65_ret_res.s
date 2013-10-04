; xv65_ret_res.s
; Written by Emanuele Fornara

	.export		xv65_ret_res_incspy
	.export		xv65_ret_res
	.import		__mappederrno
	.import		addysp

	.include	"xv65.inc"

.segment	"CODE"

xv65_ret_res_incspy:
	jsr	addysp
xv65_ret_res:
	lda	REQRES
	jmp	__mappederrno
