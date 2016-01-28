;
; Written by Emanuele Fornara
;

	.export	   	screensize

        .include        "io2.inc"


.code

.proc   screensize

        ldx	CONCOLS
        ldy	CONROWS
        rts

.endproc

