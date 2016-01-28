; Test some layer/sprite related registers: \
; LID (80), LCTL (81), LX (82), LY (83), LX with LCTL_SHIFTxx, \
; SFRAME (84), STRANSFM (85), STRANSFM with REQ_LSPREFPX \
; and SCWITH (86).
; Press any key to move to the next test case.

	.include "io2.inc"
	.feature force_range

IMAGE_ID = 1
SPRITE1_ID = 0
SPRITE2_ID = 1
SPRITE3_ID = 2

SPRITE_SIZE = 32
N_OF_FRAMES = 8
SLOW = 10
FAST = 80

; zero page
limit = 1
reg = 2

.code

	lda	#>_data_start_
	sta	REQPTRHI
	lda	#<sprite1_image
	sta	REQPTRLO
	lda	#<sprite1_layer
	sta	REQPTRLO
	lda	#<sprite2_image
	sta	REQPTRLO
	lda	#<sprite2_layer
	sta	REQPTRLO
	lda	#<sprite3_image
	sta	REQPTRLO
	lda	#<sprite3_layer
	sta	REQPTRLO
	lda	#<idestroy
	sta	REQPTRLO
	lda	#ENABLE_BGCOL|ENABLE_LAYERS
	sta	ENABLE
	lda	#SPRITE1_ID
	sta	LID
	lda	#>REQPUT
	sta	reg+1

	lda	#SLOW
	sta	FRMFPS
@a:	lda	LCTL
	eor	#LCTL_ENABLE
	sta	LCTL
	jsr	tick
	beq	@a
	lda	#LCTL_ENABLE
	sta	LCTL

	lda	#FAST
	sta	FRMFPS
	lda	#64
	sta	limit
	lda	#<LX
	sta	reg
	jsr	loop

	lda	#<LY
	sta	reg
	jsr	loop

	lda	#16
	sta	limit
	lda	#<LX
	sta	reg
	lda	#LCTL_ENABLE|LCTL_SHIFTX1
	sta	LCTL
	jsr	loop
	lda	#LCTL_ENABLE
	sta	LCTL


	lda	#SLOW
	sta	FRMFPS
	lda	#N_OF_FRAMES
	sta	limit
	lda	#<SFRAME
	sta	reg
	jsr	loop

	lda	#<lsetpos
	sta	REQPTRLO
	lda	#SPRITE2_ID
	sta	LID
	lda	#70
	sta	LX
	lda	#SPRITE_SIZE-2
	sta	LY
	lda	#LCTL_ENABLE
	sta	LCTL

	lda	#8
	sta	limit
	lda	#<STRANSFM
	sta	reg
	jsr	loop

	lda	#<lsprefpt
	sta	REQPTRLO

	lda	#8
	sta	limit
	lda	#<STRANSFM
	sta	reg
	jsr	loop

	lda	#SPRITE3_ID
	sta	LID
	lda	#10
	sta	LX
	lda	#SPRITE_SIZE-2
	sta	LY
	lda	#LCTL_ENABLE
	sta	LCTL

	lda	#SPRITE1_ID
	sta	LID
	lda	#FAST
	sta	FRMFPS
	ldx	#0
L1:	stx	LX
	inx
	lda	#LCTL_ENABLE
	sta	LCTL
	lda	#SPRITE2_ID
	sta	SCWITH
	lda	SCWITH
	bne	coll
	lda	#LCTL_ENABLE | LCTL_PXLCOLL
	sta	LCTL
	lda	#SPRITE3_ID
	sta	SCWITH
	lda	SCWITH
	bne	coll
nocoll:	lda	#<white_bg
	sta	REQPTRLO
	jmp	J1
coll:	lda	#<red_bg
	sta	REQPTRLO
J1:	jsr	tick
	beq	L1

	brk

tick:
	lda	#0
	sta	FRMDRAW
	lda	KEYBUF
	bne	key_pressed
	rts
key_pressed:
	lda	#1
	sta	KEYBUF
	rts

loop:
	ldy	#0
	ldx	#0
@b:	txa
	sta	(reg),y
	inx
	cpx	limit
	bne	@a
	ldx	#0
@a:	jsr	tick
	beq	@b
	lda	#0
	sta	(reg),y
	rts

.data
_data_start_:

sprite1_image: req
	.byte	REQ_IDUMMY, IMAGE_ID
	.byte	IDUMMY_SPRITE
	.byte	SPRITE_SIZE ; sprite width
	.byte	SPRITE_SIZE ; sprite height
	.byte	N_OF_FRAMES ; frames
	.byte	COLOR_LIGHTBLUE ; background
	.byte	COLOR_BLACK ; foreground
	.byte	"A" ; id
endreq

sprite1_layer: req
	.byte	REQ_LSPRITE, SPRITE1_ID
	.byte	IMAGE_ID
	.byte	SPRITE_SIZE ; frame width
	.byte	SPRITE_SIZE ; frame height
endreq

sprite2_image: req
	.byte	REQ_IDUMMY, IMAGE_ID
	.byte	IDUMMY_SPRITE
	.byte	SPRITE_SIZE ; sprite width
	.byte	SPRITE_SIZE ; sprite height
	.byte	1 ; frames
	.byte	COLOR_LIGHTGREEN ; background
	.byte	COLOR_BLACK ; foreground
	.byte	"B" ; id
endreq

sprite2_layer: req
	.byte	REQ_LSPRITE, SPRITE2_ID
	.byte	IMAGE_ID
endreq

sprite3_image: req
        .byte   REQ_IPNGGEN, IMAGE_ID
        .word   8, 8
        .byte   1
        .byte   IPNGGEN_CT_INDEXED_COLOR
        .byte   IPNGGEN_FLAGS_PALREF | IPNGGEN_FLAGS_IDX0TRANSP
        .byte   1
        .byte   COLOR_RED
        .byte   COLOR_BLACK
        .byte   %00011000
        .byte   %00011000
        .byte   %00011000
        .byte   %00011000
        .byte   %00111100
        .byte   %01111110
        .byte   %11111111
        .byte   %11111111
endreq

sprite3_layer: req
	.byte	REQ_LSPRITE, SPRITE3_ID
	.byte	IMAGE_ID
endreq

idestroy: req
	.byte	REQ_IDESTROY, IMAGE_ID
endreq

lsetpos: req
	.byte	REQ_LSETPOS, SPRITE1_ID
	.byte	DATATYPE_I8
	.byte	-SPRITE_SIZE ; x
	.byte	0 ; y
endreq

lsprefpt: req
	.byte	REQ_LSPREFPX, SPRITE2_ID
	.byte	DATATYPE_U8
	.byte	(SPRITE_SIZE / 2) - 1 ; ox
	.byte	(SPRITE_SIZE / 2) - 1 ; oy
endreq

white_bg: req
	.byte	REQ_SETBGCOL, COLOR_WHITE
endreq

red_bg: req
	.byte	REQ_SETBGCOL, COLOR_LIGHTRED
endreq
