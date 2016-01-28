;
; Written by Emanuele Fornara
;
; char cgetc (void);
;

	.export		_cgetc

	.include	"io2.inc"


.code

.proc	_cgetc

	lda	KEYBUF
	beq	wait
	sta	KEYBUF		; consume char
	ldx	#0		; consume 1 char
	rts
wait:	sta	FRMDRAW		; vsync (TODO: replace with 'wait')
	beq	_cgetc

.endproc

