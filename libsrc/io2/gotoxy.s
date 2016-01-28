;
; Ullrich von Bassewitz, 06.08.1998
; JBit port by Emanuele Fornara
;
; void gotoxy (unsigned char x, unsigned char y);
;

	.export		_gotoxy
	.import		popa

        .include        "io2.inc"

_gotoxy:
	sta	CONCY		; Set Y
	jsr 	popa		; Get X
	sta	CONCX		; Set X
	rts


