;
; Ullrich von Bassewitz, 2003-05-02
; JBit port by Emanuele Fornara
;
; unsigned char wherey (void);
;

 	.export		_wherey

        .include        "jbit.inc"

.proc   _wherey

        lda     CONCY
        ldx     #$00
  	rts

.endproc


