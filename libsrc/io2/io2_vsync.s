;
; Written by Emanuele Fornara
;
; void io2_vsync (void);
;

	.export		_io2_vsync

	.include	"io2.inc"


.code

.proc	_io2_vsync

	sta	FRMDRAW
	rts

.endproc

