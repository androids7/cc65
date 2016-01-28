; Small TiledLayer with dynamic content and manual scroll (infinite loop).

	.include "io2.inc"
	.feature force_range

IMAGE_ID = 1
TILES_ID = 0

N_OF_COLUMNS = 16

; zero page
tmp1 = 2
tmp2 = 4

.code

	lda	#>_data_start_
	sta	REQPTRHI

	lda	#ENABLE_BGCOL
	sta	ENABLE

	jsr	compute_rows
	lda	#<tiles_image
	sta	REQPTRLO
	lda	#<tiles_layer
	sta	REQPTRLO
	lda	#<idestroy
	sta	REQPTRLO
	lda	#<lsetpos
	sta	REQPTRLO

	lda	#TILES_ID
	sta	LID
	lda	#LCTL_ENABLE
	sta	LCTL
	lda	#ENABLE_BGCOL|ENABLE_LAYERS
	sta	ENABLE

	ldx	#255
L1:	txa
	and	#7
	sta	LY
	cmp	#7
	bne	next
	jsr	generate_row
	lda	#<ltlput
	sta	REQPTRLO
	lda	#<ltlscrll
	sta	REQPTRLO
next:	dex
	lda	#0
	sta	FRMDRAW
	jmp	L1

compute_rows:
	lda	#REQ_DPYINFO
	sta	REQPUT
	sta	REQEND
	lda	#>REQPUT
	sta	tmp1+1
	sta	tmp2+1
	lda	#<REQDAT+DPYINFO_HEIGHT+0
	sta	tmp1
	lda	#<REQDAT+DPYINFO_HEIGHT+1
	sta	tmp2
	jsr	pixels_to_tiles
	sta	rows
	sta	srows
	sec
	sbc	#1
	sta	prows
	rts

pixels_to_tiles:
	ldy	#0
	ldx	#3
L2:	lda	(tmp2),y	
	lsr
	sta	(tmp2),y
	lda	(tmp1),y
	ror
	sta	(tmp1),y
	dex
	bne	L2
	clc
	adc	#3
	rts

generate_row:
	ldy	#0
L3:
	lda	row,y
	beq	last
	lda	#0
	sta	row,y
	iny
	cpy	#N_OF_COLUMNS	
	bne	L3
	rts
last:	lda	#1
	sta	row,y
	rts

.data
_data_start_:

tiles_image: req
	.byte	REQ_IDUMMY, IMAGE_ID
	.byte	IDUMMY_TILES
	.byte	8 ; tile width
	.byte	8 ; tile height
	.byte	8 ; columns
	.byte	8 ; rows
	.byte	COLOR_BLUE ; background
	.byte	COLOR_YELLOW ; foreground
endreq

tiles_layer:
	.word	end - begin
begin:	.byte	REQ_LTILED, TILES_ID
	.byte	IMAGE_ID ; source image
	.byte	8 ; tile width
	.byte	8 ; tile height
	.byte	0 ; # of anim tiles
	.byte	DATATYPE_U8
cols:	.byte	N_OF_COLUMNS ; # of columns
rows:	.byte	0 ; # of rows (computed)
end:

idestroy: req
	.byte	REQ_IDESTROY, IMAGE_ID
endreq

lsetpos: req
	.byte	REQ_LSETPOS, TILES_ID
	.byte	DATATYPE_I8
	.byte	0 ; x
	.byte	-8 ; y
endreq

ltlput:
	.word	ltlput_end - @start
@start:	.byte	REQ_LTLPUT, TILES_ID
	.word	0 ; x pos
prows:	.word	0 ; y pos (computed)
	.word	N_OF_COLUMNS ; columns
row:	.byte	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
ltlput_end:

ltlscrll:
	.word	ltlscrll_end - @start
@start:	.byte	REQ_LTLSCRLL, TILES_ID
	.byte	0 ; type (not used for now; must be 0)
	.byte	DATATYPE_I8
	.byte	0 ; x pos
	.byte	0 ; y pos
	.byte	N_OF_COLUMNS ; columns
srows:	.byte	0 ; rows (computed)
	.byte	0 ; dx
	.byte	-1 ; dy
ltlscrll_end:
