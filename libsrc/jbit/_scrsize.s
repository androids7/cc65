;
; Written by Emanuele Fornara
;

	.export	   	screensize

        .include        "jbit.inc"


.code

.proc   screensize

        ldx	CONCOLS
        ldy	CONROWS
        rts

.endproc

