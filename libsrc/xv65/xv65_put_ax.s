; xv65_put_ax.s
; Written by Emanuele Fornara

	.export		_xv65_put_ax

	.include	"xv65.inc"

.segment	"CODE"

; void xv65_put_ax(void)
_xv65_put_ax:
	stx	PUTUINT8
	pha
	lda	#':'
	sta	PUTCHAR
	pla
	sta	PUTUINT8
	rts
