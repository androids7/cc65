;
; Written by Emanuele Fornara
;
; unsigned char __fastcall__ textcolor (unsigned char color);
; unsigned char __fastcall__ bgcolor (unsigned char color);
; unsigned char __fastcall__ bordercolor (unsigned char color);
;

	.export		_textcolor,_bgcolor,_bordercolor
	.export		TEXTCOLOR,BGCOLOR

	.include	"jbit.inc"


.code

.proc	_textcolor

	ldx	TEXTCOLOR
 	sta	TEXTCOLOR
	txa
	rts

.endproc


.proc	_bgcolor

	ldx	BGCOLOR
	sta	BGCOLOR
	txa
	rts

.endproc


.proc	_bordercolor

	ldx	#REQ_SETBGCOL
	stx	REQPUT
	sta	REQPUT
	sta	REQEND
       	ldx    	BORDERCOLOR
	sta	BORDERCOLOR
	txa
	rts

.endproc


.data

TEXTCOLOR:
	.byte	COLOR_BLACK

BGCOLOR:
	.byte	COLOR_WHITE

BORDERCOLOR:
	.byte	COLOR_WHITE

