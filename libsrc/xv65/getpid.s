; getpid.s
; Written by Emanuele Fornara

	.export		_getpid
	.import		xv65_ret_pid

	.include	"xv65.inc"

.segment	"CODE"

; pid_t getpid(void)
_getpid:
	lda	#REQ_GETPID
	sta	REQPUT
	sta	REQEND
	jmp	xv65_ret_pid
