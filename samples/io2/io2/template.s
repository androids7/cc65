; Starting point for simple mini-games.

	.include "io2.inc"

.code

startup:  jmp startup_impl
nextfrm:  jmp nextfrm_impl

startup_impl:

	lda	#>_data_start_
	sta	REQPTRHI
	lda	#<setbgcol
	sta	REQPTRLO
	lda	#ENABLE_BGCOL|ENABLE_LAYERS
	sta	ENABLE
	jsr	setup_skin
	lda	#<lmview
	sta	REQPTRLO
	lda	#TILES_ID
	sta	LID
	lda	#LCTL_ENABLE
	sta	LCTL
	jmp	main

setup_skin:

	; compute tiled layer size
	lda	#REQ_DPYINFO
	sta	REQPUT
	sta	REQEND
	ldx	#3
	lda	flags
	and	#IPNGGEN_FLAGS_ZOOM0
	beq	@l0
	lda	#16
	sta	tilew
	sta	tileh
	ldx	#4
@l0:	lsr	REQDAT+1
	ror	REQDAT
	lsr	REQDAT+3
	ror	REQDAT+2
	dex
	bne	@l0

	; fill cols, if requested
	lda	cols
	bne	@l1
	lda	REQDAT
	sta	cols

	; fill rows, if requested
@l1:	lda	rows
	bne	@l2
	lda	REQDAT+2
	sta	rows

	; set up the layer
@l2:	lda	#>ipnggen
	sta	REQPTRHI
	lda	#<ipnggen
	sta	REQPTRLO
	lda	#>_data_start_
	sta	REQPTRHI
	lda	#<ltiled
	sta	REQPTRLO
	lda	#<idestroy
	sta	REQPTRLO
	rts

nextfrm_impl:

	; wait for the next frame
	sta	FRMDRAW
	lda	KEYBUF
	beq	@ret

	; got a keypress, consume it
	pha
	lda	#1
	sta	KEYBUF
	pla

@ret:	rts

.align	256

main:
	lda	#1
	sta	TCELL

	.res	14 * 256

.data

	.byte	0
.align	256

_data_start_:

IMAGE_ID = 1
TILES_ID = 7

seed:
	.word	0 ; not used anymore; kept for compatibility

setbgcol: req
	.byte	REQ_SETBGCOL
	.byte	255, 255, 255
endreq

ltiled:
	.word	lt_e - lt_s
lt_s:	.byte	REQ_LTILED, TILES_ID
	.byte	IMAGE_ID ; source image
tilew:	.byte	8 ; tile width
tileh:	.byte	8 ; tile height
	.byte	0 ; # of anim tiles
	.byte	DATATYPE_U8
cols:	.byte	0 ; # of columns
rows:	.byte	0 ; # of rows
lt_e:

idestroy: req
	.byte	REQ_IDESTROY, IMAGE_ID
endreq

lmview: req
	.byte	REQ_LMVIEW, TILES_ID ; wiew is (0,0)-(tiles.width,tiles.height)
endreq

.align	256

ipnggen:
	.word	ig_e - ig_s
ig_s:	.byte	REQ_IPNGGEN, IMAGE_ID
	.word	8 * 8 ; width
	.word	12 * 8 ; height
	.byte	4 ; depth
	.byte	IPNGGEN_CT_INDEXED_COLOR
flags:	.byte	IPNGGEN_FLAGS_IDX0TRANSP
	.byte	15 ; palette 0..1 x (1 if PALREF is set, 3 (RGB) if not)
	.byte	$FF, $FF, $FF ; White
	.byte	$00, $00, $00 ; Black
	.byte	$BE, $1A, $24 ; Red
	.byte	$30, $E6, $C6 ; Cyan
	.byte	$B4, $1A, $E2 ; Purple
	.byte	$1F, $D2, $1E ; Green
	.byte	$21, $1B, $AE ; Blue
	.byte	$DF, $F6, $0A ; Yellow
	.byte	$B8, $41, $04 ; Orange
	.byte	$6A, $33, $04 ; Brown
	.byte	$FE, $4A, $57 ; Light Red
	.byte	$42, $45, $40 ; Dark Gray
	.byte	$70, $74, $6F ; Medium Gray
	.byte	$59, $FE, $59 ; Light Green
	.byte	$5F, $53, $FE ; Light Blue
	.byte	$A4, $A7, $A2 ; Light Gray		
	.res	(12 * 8) * 8 * 4
ig_e:

	.res	6 * 256
