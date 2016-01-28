; Create and show some dummies (press any key to go to the next one).
; Dummies let you quickly create sample images to be used \
; as sprites or tiles.
; Known bug: the size of a tile might be too small for its content to \
; be readable.

	.include "io2.inc"

.code

	lda	#ENABLE_BGCOL|ENABLE_BGIMG
	sta	ENABLE
	lda	#>_data_start_
	sta	REQPTRHI
	lda	#<idummy_simple1
	jsr	update
	lda	#<idummy_simple2
	jsr	update
	lda	#<idummy_sprite
	jsr	update
	lda	#<idummy_tiles1
	jsr	update
	lda	#<idummy_tiles2
	jsr	update
	brk

update:	sta	REQPTRLO
	lda	#<setbgimg
	sta	REQPTRLO
	lda	#0
L1:	sta	FRMDRAW
	lda	KEYBUF
	beq	L1
	lda	#1
	sta	KEYBUF
	rts

.data
_data_start_:

IMAGE_ID = 1

setbgimg: req
	.byte	REQ_SETBGIMG, IMAGE_ID
endreq

idummy_simple1: req
	.byte	REQ_IDUMMY, IMAGE_ID
	.byte	IDUMMY_SIMPLE
	.word	48 ; width
	.word	48 ; height
	.byte	COLOR_BLUE ; background
	.byte	COLOR_RED ; foreground
endreq

idummy_simple2: req
	.byte	REQ_IDUMMY, IMAGE_ID
	.byte	IDUMMY_SIMPLE
	.word	48 ; width
	.word	48 ; height
	.byte	COLOR_BLUE ; background
	.byte	COLOR_RED ; foreground
	.byte	"Test" ; id
endreq

idummy_sprite: req
	.byte	REQ_IDUMMY, IMAGE_ID
	.byte	IDUMMY_SPRITE
	.byte	32 ; sprite width
	.byte	32 ; sprite height
	.byte	3 ; frames
	.byte	COLOR_BLUE ; background
	.byte	COLOR_GREEN ; foreground
	.byte	"A" ; id
endreq

idummy_tiles1: req
	.byte	REQ_IDUMMY, IMAGE_ID
	.byte	IDUMMY_TILES
	.byte	8 ; tile width
	.byte	8 ; tile height
	.byte	6 ; columns
	.byte	6 ; rows
	.byte	COLOR_BLUE ; background
	.byte	COLOR_YELLOW ; foreground
endreq

idummy_tiles2: req
	.byte	REQ_IDUMMY, IMAGE_ID
	.byte	IDUMMY_TILES
	.byte	8 ; tile width
	.byte	8 ; tile height
	.byte	8 ; columns
	.byte	8 ; rows
	.byte	COLOR_LIGHTBLUE ; sky background
	.byte	COLOR_GRAY1 ; sky foreground
	.byte	10 ; # of tiles for the sky
	.byte	COLOR_BLUE ; sea background
	.byte	COLOR_WHITE ; sea foreground
	.byte	5 ; # of tiles for the sea
	.byte	COLOR_GREEN ; vegetation background
	.byte	COLOR_BROWN ; vegetation foreground
	.byte	30 ; # of tiles for the vegetation
	.byte	COLOR_GRAY2 ; city background
	.byte	COLOR_GRAY1 ; city foreground
		; # of tiles omitted (all the remaining tiles)
endreq
