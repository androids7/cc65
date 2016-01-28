; Scan for gamekeys (infinite loop).

	.include "io2.inc"

.code

main_loop:
	sta	GKEY0

	ldx	#up - table
	lda	GKEY0
	and	#GKEY0_UP
	jsr	show

	ldx	#down - table
	lda	GKEY0
	and	#GKEY0_DOWN
	jsr	show

	ldx	#left - table
	lda	GKEY0
	and	#GKEY0_LEFT
	jsr	show

	ldx	#right - table
	lda	GKEY0
	and	#GKEY0_RIGHT
	jsr	show

	ldx	#fire - table
	lda	GKEY1
	and	#GKEY1_FIRE
	jsr	show

	ldx	#gkeya - table
	lda	GKEY1
	and	#GKEY1_A
	jsr	show

	ldx	#gkeyb - table
	lda	GKEY1
	and	#GKEY1_B
	jsr	show

	ldx	#gkeyc - table
	lda	GKEY1
	and	#GKEY1_C
	jsr	show

	ldx	#gkeyd - table
	lda	GKEY1
	and	#GKEY1_D
	jsr	show

	lda	#0
	sta	FRMDRAW
	jmp	main_loop

show:
	bne	on
off:	ldy	#' '
	bne	put	
on:	ldy	table+1,x
put:	lda	table,x
	tax
	tya
	sta	IO,x
	rts

.data

table:

up:	.byte	<CONROW0 + 1, 'U'
down:	.byte	<CONROW2 + 1, 'D'
left:	.byte	<CONROW1 + 0, 'L'
right:	.byte	<CONROW1 + 2, 'R'
fire:	.byte	<CONROW1 + 1, 'X'
gkeya:	.byte	<CONROW3 + 6, 'A'
gkeyb:	.byte	<CONROW3 + 7, 'B'
gkeyc:	.byte	<CONROW3 + 8, 'C'
gkeyd:	.byte	<CONROW3 + 9, 'D'
