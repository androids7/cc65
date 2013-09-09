;
; Ullrich von Bassewitz, 06.08.1998
; JBit port by Emanuele Fornara
;
; int kbhit (void);
;

	.export		_kbhit

	.import		return0, return1

	.include	"jbit.inc"


.code

.proc	_kbhit

	lda	KEYBUF
	bne   	L1
	jmp	return0
L1:	jmp	return1

.endproc

