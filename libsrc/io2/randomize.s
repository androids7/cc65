;
; Ullrich von Bassewitz, 05.11.2002
; JBit port by Emanuele Fornara
;
; void _randomize (void);
; /* Initialize the random number generator */
;

    	.export	       	__randomize
	.import		_srand

	.include	"io2.inc"

__randomize:              
	lda	#REQ_TIME
	sta	REQPUT
	lda	#TIME_ABS
	sta	REQPUT
	sta	REQEND          ; Use absolute time (in  ms)
        ldx     REQDAT+2	; The least significant byte is ignored
        lda     REQDAT+1        ; (resolution is unlikely to be 1ms)
        jmp     _srand          ; Initialize generator

