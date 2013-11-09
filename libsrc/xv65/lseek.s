; lseek.s
; Written by Emanuele Fornara

	.export		_lseek
	.import		xv65_ret_res_incspy
	.import		xv65_ret_long
	.import		pushax
	.import		ldax0sp
	.import		ldeaxysp
	.import		incsp8
	.importzp	sp
	.importzp	sreg

	.include	"xv65.inc"

.segment	"CODE"

; off_t __fastcall__ lseek (int fd, off_t offset, int whence)  [unistd.h]
_lseek:
	jsr	pushax
	jsr	ldax0sp
	cpx	#0
	bne	invalid_whence
	jsr	map_whence
	bmi	invalid_whence
	pha
	lda	#REQ_LSEEK
	sta	REQPUT
	ldy	#6
	lda	(sp),y
	sta	REQPUT
	pla
	sta	REQPUT
	ldy	#5
	jsr	ldeaxysp
	sta	REQPUT
	stx	REQPUT
	ldy	sreg
	sty	REQPUT
	ldy	sreg+1
	sty	REQPUT
	sta	REQEND
	lda	REQRES
	bne	error
	jsr	xv65_ret_long
	jmp	incsp8

map_whence:
	cmp	#0 ; cc65 SEEK_CUR
	bne	@j0
	lda	#SEEK_CUR
	rts
@j0:	cmp	#1 ; cc65 SEEK_END
	bne	@j1
	lda	#SEEK_END
	rts
@j1:	cmp	#2 ; cc65 SEEK_SET
	bne	@j2
	lda	#SEEK_SET
	rts
@j2:	lda	#$ff
	rts

invalid_whence:
	lda	#EINVAL
error:
	ldy	#8
	jmp	xv65_ret_res_incspy
