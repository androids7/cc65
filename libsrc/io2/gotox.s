;
; Ullrich von Bassewitz, 07.08.1998
; JBit port by Emanuele Fornara
;
; void gotox (unsigned char x);
;

	.export		_gotox

	.include	"io2.inc"

_gotox:	sta	CONCX		; Set new position
	rts



