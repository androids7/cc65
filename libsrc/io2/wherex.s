;
; Ullrich von Bassewitz, 2003-05-02
; JBit port by Emanuele Fornara
;
; unsigned char wherex (void);
;

  	.export		_wherex

        .include        "io2.inc"

.proc   _wherex

        lda     CONCX
        ldx     #$00
  	rts

.endproc


