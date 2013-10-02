; read_write.s
; Written by Emanuele Fornara

	.export		_read
	.export		_write
	.import		_xv65_req_put_word
	.import		xv65_ret_res_incspy
	.import		pushax
	.import		ldaxysp
	.import		ldax0sp
	.import		incsp6
	.importzp	sp

	.include	"xv65.inc"

.segment	"CODE"

; int __fastcall__ read(int fd, void* buf, unsigned int count)  [unistd.h]
_read:
	ldy	#REQ_READ
	bne	j0
; int __fastcall__ write(int fd, void* buf, unsigned int count)  [unistd.h]
_write:
	ldy	#REQ_WRITE
j0:	sty	REQPUT
	jsr	pushax
	ldy	#4
	lda	(sp),y
	sta	REQPUT
	dey
	jsr	ldaxysp
	jsr	_xv65_req_put_word
	jsr	ldax0sp
	jsr	_xv65_req_put_word
	sta	REQEND
	lda	REQRES
	beq	@r0
	ldy	#6
	jmp	xv65_ret_res_incspy
@r0:	lda	REQDAT
	ldx	REQDAT+1
	jmp	incsp6
