; pipe.s
; Written by Emanuele Fornara

	.export		_pipe
	.import		__mappederrno
	.importzp	ptr1

	.include	"xv65.inc"

.segment	"CODE"

; int __fastcall__ pipe(int *p)
_pipe:
	sta	ptr1
	stx	ptr1+1
	ldy	#REQ_PIPE
	sty	REQPUT
	sta	REQEND
	lda	REQRES
	beq	@r0
	jmp	__mappederrno
@r0:	ldy	#0
	lda	REQDAT
	sta	(ptr1),y
	iny
	lda	#0
	sta	(ptr1),y
	iny
	lda	REQDAT+8
	sta	(ptr1),y
	iny
	lda	#0
	sta	(ptr1),y
	jmp	__mappederrno
