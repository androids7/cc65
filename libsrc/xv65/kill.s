; kill.s
; Written by Emanuele Fornara

	.export		_kill
	.import		xv65_ret_res_incspy
	.import		ldeax0sp
	.importzp	sreg

	.include	"xv65.inc"

.segment	"CODE"

; int kill(pid_t pid, unsigned char sig)
_kill:
	ldx	#REQ_KILL
	stx	REQPUT
	sta	REQPUT
	jsr	ldeax0sp
	sta	REQDAT
	stx	REQDAT+1
	lda	sreg
	sta	REQDAT+2
	lda	sreg+1
	sta	REQDAT+3
	sta	REQEND
	ldy	#4
	jmp	xv65_ret_res_incspy
