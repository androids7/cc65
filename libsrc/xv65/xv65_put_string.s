; xv65_put_string.s
; Written by Emanuele Fornara

	.export		_xv65_put_string
	.importzp	ptr4

	.include	"xv65.inc"

.segment	"CODE"

; void __fastcall__ xv65_put_string(const char *s)
_xv65_put_string:
	sta	ptr4
	stx	ptr4+1
	tya
	pha
	ldy	#0
@l0:	lda	(ptr4),y
	beq	@r0
	sta	PUTCHAR
	iny
	bne	@l0
@r0:	pla
	tay
	lda	ptr4
	rts
