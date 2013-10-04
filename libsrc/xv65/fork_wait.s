; fork_wait.s
; Written by Emanuele Fornara

	.export		_fork
	.export		_wait
	.import		xv65_ret_pid
	.import		__mappederrno
	.importzp	sreg

	.include	"xv65.inc"

.segment	"CODE"

; pid_t fork(void)
_fork:
	lda	#REQ_FORK
	bne	j0
; pid_t wait(void)
_wait:
	lda	#REQ_WAIT
j0:	sta	REQPUT
	sta	REQEND
	lda	REQRES
	beq	@r0
	ldx	#$ff
	stx	sreg
	stx	sreg+1
	jmp	__mappederrno
@r0:	jmp	xv65_ret_pid
