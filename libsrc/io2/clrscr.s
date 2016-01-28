;
; Written by Emanuele Fornara
;
; void clrscr (void);
;

	.export		_clrscr

	.importzp	tmp3
	.import		BGCOLOR, TEXTCOLOR

	.include	"io2.inc"


.proc	_clrscr

	; should I save Y? just to be sure I save it
	sty	tmp3
	ldy	#0
L2:	sty	CONCY
	ldx	#0
L1:	stx	CONCX
	lda	#' '
	sta	CONCCHR
	lda	BGCOLOR
	sta	CONCBG
	lda	TEXTCOLOR
	sta	CONCFG
	inx
	cpx	CONCOLS
	bne	L1
	iny
	cpy	CONROWS
	bne	L2
	ldy	tmp3
	lda	#0
	sta	CONCX
	sta	CONCY
	rts

.endproc

