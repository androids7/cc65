;
; Written by Groepaz/Hitmen <groepaz@gmx.net>
; Cleanup by Ullrich von Bassewitz <uz@cc65.org>
; JBit port by Emanuele Fornara
;
; void cputcxy (unsigned char x, unsigned char y, char c);
; void cputc (char c);
;

    	.export	       	_cputcxy, _cputc, cputdirect, putchar
	.export		newline
        .constructor    conioinit
	.import		popa, _gotoxy
	.import		TEXTCOLOR, BGCOLOR

        .importzp       tmp3,tmp4

	.include	"io2.inc"

;-----------------------------------------------------------------------------
                      
.code

_cputcxy:
	pha	      		; Save C
	jsr	popa  		; Get Y
	jsr	_gotoxy		; Set cursor, drop x
	pla	      		; Restore C

; Plot a character - also used as internal function

_cputc: cmp     #$0d 		; CR?
    	bne	L1
    	lda	#0
    	sta	CONCX
       	beq    	plot		; Recalculate pointers

L1: 	cmp	#$0a  	  	; LF?
       	beq	newline		; Recalculate pointers

; Printable char of some sort

cputdirect:
  	jsr	putchar		; Write the character to the screen

; Advance cursor position

advance:
	ldy	CONCX
   	iny
   	cpy	CONCOLS
   	bne	L3
       	inc     CONCY           ; new line
   	ldy	#0    	  	; + cr
L3:	sty	CONCX
	jmp     plot

newline:
	inc	CONCY

; Set cursor position, calculate RAM pointers

plot:	ldy	CONCX
	ldx	CONCY
	rts


; Write one character to the screen without doing anything else, return X
; position in Y

putchar:
	sta	CONCCHR
	lda	BGCOLOR
	sta	CONCBG
	lda	TEXTCOLOR
	sta	CONCFG
	ldy	CONCX
	rts

;-----------------------------------------------------------------------------
; Initialize the conio subsystem. Code goes into the INIT segment, which may
; be reused after startup.

.segment        "INIT"

; Enlarge the console to fill the display (default size is 10x4)

conioinit:
	lda	#0
	sta	CONROWS
	sta	CONCOLS
	rts


