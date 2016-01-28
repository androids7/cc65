; Define a custom palette (press any key except * to switch palette, \
; use * to exit).

	.include "io2.inc"

RED_LO = 2
RED_HI = 3
GREEN_LO = 4
GREEN_HI = 5
BLUE_LO = 6
BLUE_HI = 7

.code

setup:
	lda	#>_data_start_
	sta	RED_HI
	sta	GREEN_HI
	sta	BLUE_HI
	jsr	fill_row
	inc	CONCY
	jsr	fill_row
	inc	CONCY
	jsr	fill_row
	inc	CONCY
	jsr	fill_row

main_loop:
	jsr	custom_palette
	jsr	check_key
	jsr	standard_palette
	jsr	check_key
	jmp	main_loop

fill_row:
	ldy	#0
L1:	sty	CONCX
	stx	CONCBG
	inx
	iny
	cpy	#10
	bne	L1
	rts

custom_palette:
	lda	#REQ_SETPAL
	sta	REQPUT

	lda	#<empty
	sta	GREEN_LO
	sta	BLUE_LO
	lda	#<full
	sta	RED_LO
	jsr	spread	

	lda	#<empty
	sta	RED_LO
	sta	BLUE_LO
	lda	#<full
	sta	GREEN_LO
	jsr	spread	

	lda	#<empty
	sta	RED_LO
	sta	GREEN_LO
	lda	#<full
	sta	BLUE_LO
	jsr	spread	

	lda	#<full
	sta	RED_LO
	sta	GREEN_LO
	sta	BLUE_LO
	jsr	spread	

	sta	REQEND
	rts

spread:
	ldy	#0
L2:	lda	(RED_LO),y
	sta	REQPUT
	lda	(GREEN_LO),y
	sta	REQPUT
	lda	(BLUE_LO),y
	sta	REQPUT
	iny
	cpy	#10
	bne	L2
	rts

standard_palette:
	lda	#REQ_SETPAL
	sta	REQPUT
	sta	REQEND
	rts

check_key:
	lda	#0
	sta	FRMDRAW
	lda	KEYBUF
	beq	check_key
	cmp	#'*'
	beq	quit
	lda	#1
	sta	KEYBUF
	rts

quit:
	brk

.data
_data_start_:

full:
	.byte	30,55,80,105,130,155,180,205,230,255
empty:
	.byte	0,0,0,0,0,0,0,0,0,0
