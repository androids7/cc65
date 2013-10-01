; xv65_ret_res.s
; Written by Emanuele Fornara

	.export		xv65_ret_res_incspy
	.export		xv65_ret_res
	.export		xv65_ret_res_error
	.export		xv65_ret_res_ok
	.import		addysp

	.include	"xv65.inc"

.segment	"CODE"

xv65_ret_res_incspy:
	jsr	addysp
xv65_ret_res:
	lda	REQRES
	beq	xv65_ret_res_ok
xv65_ret_res_error:
	; TODO: assume accumulator contains REQRES and set errno
	lda	#$ff
	tax
	rts
xv65_ret_res_ok:
	lda	#$0
	tax
	rts
