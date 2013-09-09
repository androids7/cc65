;
; Written by Emanuele Fornara
;
; void vsync (void);
;

	.export		_vsync

	.include	"jbit.inc"


.code

.proc	_vsync

	sta	FRMDRAW
	rts

.endproc

