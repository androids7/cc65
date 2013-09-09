;
; Ullrich von Bassewitz, 2003-05-02
; JBit port by Emanuele Fornara
;
; unsigned char wherex (void);
;

  	.export		_wherex

        .include        "jbit.inc"

.proc   _wherex

        lda     CONCX
        ldx     #$00
  	rts

.endproc


