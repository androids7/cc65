; xv65_put_c_runtime.s
; Written by Emanuele Fornara

	.export		_xv65_put_c_runtime
	.import		_xv65_put_string
	.import		_xv65_put_ax
	.importzp	sp
	.importzp	sreg

	.include	"xv65.inc"

.macro saveax
	pha
	txa
	pha
.endmacro

.macro restoreax
	pla
	tax
	pla
.endmacro

.macro putchar chr
	lda	#chr
	sta	PUTCHAR
.endmacro

.macro putstring str
	lda	#<str
	ldx	#>str
	jsr	_xv65_put_string
.endmacro

.segment	"CODE"

; void xv65_put_c_runtime(void)
_xv65_put_c_runtime:
	saveax
	putstring header_msg
	restoreax
	jsr	_xv65_put_ax
	saveax
	putstring sreg_msg
	lda	sreg
	ldx	sreg+1
	jsr	_xv65_put_ax
	putstring sp_msg
	lda	sp
	ldx	sp+1
	jsr	_xv65_put_ax
	putstring sp_top_msg
	tya
	pha
	ldy	#0
@l0:	putchar ' '
	lda	(sp),y
	sta	PUTUINT8
	iny
	cpy	#16
	bne	@l0
	pla
	tay
	putstring trailer_msg
	restoreax
	rts

.segment	"RODATA"

header_msg: .byte "*** C RunTime ***", 10, "ax ", 0
sreg_msg: .byte "  sreg ", 0
sp_msg: .byte 10, "sp ", 0
sp_top_msg: .byte " ->", 0
trailer_msg: .byte 10, 10, 0
