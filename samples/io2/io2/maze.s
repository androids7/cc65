; Take the ball out of the maze without touching the wall.
; Be careful! once you begin you cannot stop... literally.
; The maze is encoded as a standard IPNGGEN image and thus \
; can be edited by Paint.

	.include "io2.inc"
	.feature force_range

FPS = 10
SPEED = 2
DELAY = 1 * FPS

IMAGE_ID = 1
BALL_ID = 1
MAZE_ID = 0

; zero page
cx = 6
cy = 7
mz = 8

.code

	lda	#>_data_start_
	sta	REQPTRHI
	lda	#ENABLE_BGCOL|ENABLE_LAYERS
	sta	ENABLE
	jsr	init
	lda	#FPS * 4
	sta	FRMFPS
main_loop:
	lda	#MAZE_ID
	sta	SCWITH
	lda	SCWITH
	bne	restart
nocoll:	lda	#<bg_ok
	sta	REQPTRLO
next:	jsr	check_dir
	lda	#<lmove
	sta	REQPTRLO
	lda	#0
	sta	FRMDRAW
	jmp	main_loop

check_dir:
	sta	GKEY0
	lda	GKEY0
	and	#GKEY0_UP
	bne	up
	lda	GKEY0
	and	#GKEY0_DOWN
	bne	down
	lda	GKEY0
	and	#GKEY0_LEFT
	bne	left
	lda	GKEY0
	and	#GKEY0_RIGHT
	bne	right
	rts
up:	lda	#SPEED
	sta	dy
	lda	#0
	sta	dx
	rts
down:	lda	#-SPEED
	sta	dy
	lda	#0
	sta	dx
	rts
left:	lda	#0
	sta	dy
	lda	#SPEED
	sta	dx
	rts
right:	lda	#0
	sta	dy
	lda	#-SPEED
	sta	dx
	rts

restart:
	lda	#<bg_hit
	sta	REQPTRLO
	ldx	#DELAY
	lda	#0
@loop:	sta	FRMDRAW
	dex
	bne	@loop
	sta	GKEY0
	jsr	setup_view
	jmp	main_loop

init:
	lda	cols
	sta	lcols
	sta	pcols
	lda	rows
	sta	lrows
	lda	#<brick_image
	sta	REQPTRLO
	lda	#<maze_layer
	sta	REQPTRLO
	lda	#<ball_image
	sta	REQPTRLO
	lda	#<ball_layer
	sta	REQPTRLO
	lda	#<idestroy
	sta	REQPTRLO

	jsr	decode_maze

	jsr	find_center_of_display
	jsr	setup_view

	ldx	#LCTL_ENABLE
	lda	#MAZE_ID
	sta	LID
	stx	LCTL
	lda	#BALL_ID
	sta	LID
	stx	LCTL
	rts

decode_maze:
	ldx	#0
@l1:	lda	maze_put,x
	sta	REQPUT
	inx
	cpx	#maze_put_end - maze_put
	bne	@l1
	lda	#<maze
	sta	mz
	lda	#>maze
	sta	mz+1
	lda	cols
	lsr
	lsr
	lsr
	ldy	rows
@l3:	tax
@l2:	jsr	decode_byte
	dex
	bne	@l2
	dey
	bne	@l3
	sta	REQEND
	rts

decode_byte:
	pha
	tya
	pha
	txa
	pha
	ldy	#0
	ldx	#8
	lda	(mz),y
@loop:	asl
	bcs	@put1
@put0:	ldy	#0
	sty	REQPUT
	beq	@next
@put1:	ldy	#1
	sty	REQPUT
@next:	dex
	bne	@loop
	inc	mz
	bne	@end
	inc	mz+1
@end:	pla
	tax
	pla
	tay
	pla
	rts

find_center_of_display:
	lda	#REQ_DPYINFO
	sta	REQPUT
	sta	REQEND
	lsr	REQDAT+DPYINFO_WIDTH+1
	ror	REQDAT+DPYINFO_WIDTH+0
	lda	REQDAT+DPYINFO_WIDTH+0
	sta	cx
	lsr	REQDAT+DPYINFO_HEIGHT+1
	ror	REQDAT+DPYINFO_HEIGHT+0
	lda	REQDAT+DPYINFO_HEIGHT+0
	sta	cy
	rts

setup_view:
	lda	cx
	sta	px
	lda	cy
	sta	py
	lda	#MAZE_ID
	sta	pid
	lda	#<lsetpos
	sta	REQPTRLO
	lda	#BALL_ID
	sta	pid
	lda	#<lsetpos
	sta	REQPTRLO
	lda	#BALL_ID
	sta	did
	lda	#-4
	sta	dx
	sta	dy
	lda	#<lmove
	sta	REQPTRLO
	lda	#MAZE_ID
	sta	did
	lda	#-8
	sta	dx
	sta	dy
	lda	#<lmove
	sta	REQPTRLO
	lda	org_x
	sta	dx
	lda	org_y
	sta	dy
	ldx	#16
	lda	#<lmove
@l0:	sta	REQPTRLO
	dex
	bne	@l0
	lda	#0
	sta	dx
	sta	dy
	rts

.data
_data_start_:

bg_ok: req
	.byte	REQ_SETBGCOL, COLOR_GREEN
endreq

bg_hit: req
	.byte	REQ_SETBGCOL, COLOR_RED
endreq

brick_image: req
	.byte	REQ_IPNGGEN, IMAGE_ID
	.word	16, 16
	.byte	1
	.byte	IPNGGEN_CT_INDEXED_COLOR
	.byte	IPNGGEN_FLAGS_PALREF
	.byte	1
	.byte	COLOR_BROWN
	.byte	COLOR_GRAY3
	.byte	%11111111,%11111111
	.byte	%11111111,%11111111
	.byte	%00000001,%10000000
	.byte	%00000001,%10000000
	.byte	%00000001,%10000000
	.byte	%00000001,%10000000
	.byte	%00000001,%10000000
	.byte	%00000001,%10000000
	.byte	%11111111,%11111111
	.byte	%11111111,%11111111
	.byte	%10000000,%00000001
	.byte	%10000000,%00000001
	.byte	%10000000,%00000001
	.byte	%10000000,%00000001
	.byte	%10000000,%00000001
	.byte	%10000000,%00000001
endreq

maze_layer:
	.word	maze_layer_end - @start
@start:	.byte	REQ_LTILED, MAZE_ID
	.byte	IMAGE_ID ; source image
	.byte	16 ; tile width
	.byte	16 ; tile height
	.byte	0 ; # of anim tiles
	.byte	DATATYPE_U8
lcols:	.byte	0 ; # of columns (set by code)
lrows:	.byte	0 ; # of rows (set by code)
maze_layer_end:

maze_put:
	.byte   REQ_LTLPUT, MAZE_ID
	.word   0 ; x pos
	.word   0 ; y pos
pcols:	.word	0 ; cols
maze_put_end:

ball_image: req
	.byte	REQ_IPNGGEN, IMAGE_ID
	.word	8, 8
	.byte	1
	.byte	IPNGGEN_CT_INDEXED_COLOR
	.byte	IPNGGEN_FLAGS_PALREF | IPNGGEN_FLAGS_IDX0TRANSP
	.byte	1
	.byte	COLOR_RED
	.byte	COLOR_BLACK
	.byte	%00111100
	.byte	%01111110
	.byte	%11111111
	.byte	%11111111
	.byte	%11111111
	.byte	%11111111
	.byte	%01111110
	.byte	%00111100
endreq

ball_layer: req
	.byte   REQ_LSPRITE, BALL_ID
	.byte	IMAGE_ID ; source image
endreq

idestroy: req
	.byte	REQ_IDESTROY, IMAGE_ID
endreq

lsetpos:
	.word	lsetpos_end - @start
@start:	.byte	REQ_LSETPOS
pid:	.byte	0
	.byte	DATATYPE_U8
px:	.byte	0
py:	.byte	0
lsetpos_end:

lmove:
	.word	lmove_end - @start
@start:	.byte	REQ_LMOVE
did:	.byte	0
	.byte	DATATYPE_I8
dx:	.byte	0
dy:	.byte	0
lmove_end:

org_x:	.byte	-37 ; negated, 0-based
org_y:	.byte	-29 ; negated, 0-based

maze_image:
	.word	maze_image_end - @start
@start:	.byte	REQ_IPNGGEN, IMAGE_ID
cols:	.word	40 ; must be divisible by 8
rows:	.word	31
	.byte	1
	.byte	IPNGGEN_CT_INDEXED_COLOR
	.byte	IPNGGEN_FLAGS_PALREF
	.byte	1
	.byte	COLOR_WHITE
	.byte	COLOR_BLACK
maze:
	.byte	%11111111,%11111111,%11111111,%11111111,%11111110
	.byte	%00100010,%00001000,%00000000,%00100000,%00000010
	.byte	%10101011,%11101111,%11101111,%10101111,%11111010
	.byte	%10101000,%10100010,%00101000,%00001000,%00000010
	.byte	%10101010,%10111011,%10101110,%11111011,%11111110
	.byte	%10101010,%10001000,%10100010,%10001010,%00100010
	.byte	%10101011,%10101010,%10111010,%11101010,%10111010
	.byte	%10101000,%10101010,%00100010,%10001000,%10000010
	.byte	%10111110,%11101011,%11111110,%10111111,%11111010
	.byte	%10000000,%00001010,%00001000,%00100010,%10000010
	.byte	%10111111,%11111011,%10101011,%10101010,%10111110
	.byte	%10100010,%00101000,%00101010,%00101010,%10000010
	.byte	%10101110,%10101011,%11101010,%11101010,%11101010
	.byte	%10100000,%10000010,%10001010,%10001010,%00101010
	.byte	%10111111,%11111110,%10111010,%10111011,%10101010
	.byte	%10100010,%00000000,%10100010,%10100010,%10001010
	.byte	%10101110,%11111110,%10101110,%10111110,%11111010
	.byte	%10100000,%10001000,%10101000,%10000010,%10000010
	.byte	%10111111,%11101110,%10101011,%11111010,%10111110
	.byte	%10100000,%00101000,%10101000,%10000010,%10000010
	.byte	%10101111,%10101011,%10101110,%10101110,%11111110
	.byte	%10100010,%00001010,%00100010,%00100000,%10000010
	.byte	%10111010,%11111010,%11111010,%11111111,%10111010
	.byte	%10100010,%00100000,%10100010,%00000000,%00100010
	.byte	%10101111,%10101011,%10101111,%11111111,%11111010
	.byte	%10100010,%10101000,%10001000,%00001000,%00001010
	.byte	%10111010,%10101110,%10101011,%11111011,%11101010
	.byte	%10000010,%10001000,%10101010,%00001010,%00100010
	.byte	%11111010,%11111010,%10101010,%10101010,%10111110
	.byte	%10000010,%00000010,%00101000,%10100000,%10000010
	.byte	%11111111,%11111111,%11111111,%11111111,%11111110
maze_image_end:
