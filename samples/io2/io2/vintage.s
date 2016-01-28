; TiledLayer+Sprite with custom graphics (infinite loop).

	.include "io2.inc"
	.feature force_range

IMAGE_ID = 1
SPRITE_ID = 0
CHARS_ID = 1

FPS = 25
SPRITE_X_ORG = 0
SPRITE_Y_ORG = 0
SPRITE_X_INC = 2
SPRITE_Y_INC = 2
BORDER_SIZE = 4
MAX_SIZE = 32 - BORDER_SIZE

; zero page
tmp1 = 2
tmp2 = 4

.code

	lda	#>_data_start_
	sta	REQPTRHI

	lda	#ENABLE_BGCOL
	sta	ENABLE
	lda	#<setbgcol
	sta	REQPTRLO

	jsr	compute_cols_and_rows
	lda	#<chars_image
	sta	REQPTRLO
	lda	#<chars_layer
	sta	REQPTRLO
	lda	#<sprite_image
	sta	REQPTRLO
	lda	#<sprite_layer
	sta	REQPTRLO
	lda	#<idestroy
	sta	REQPTRLO
	lda	#<lmview
	sta	REQPTRLO
	lda	#<ltlfill
	sta	REQPTRLO
	lda	#<ltlput
	sta	REQPTRLO
	lda	#<lsetpos
	sta	REQPTRLO

	ldx	#LCTL_ENABLE
	lda	#CHARS_ID
	sta	LID
	stx	LCTL
	lda	#SPRITE_ID
	sta	LID
	stx	LCTL
	lda	#ENABLE_BGCOL|ENABLE_LAYERS
	sta	ENABLE
	ldx	#0
	stx	FRMDRAW
	lda	#ENABLE_LAYERS
	sta	ENABLE
	lda	#FPS * 4
	sta	FRMFPS

	lda	#SPRITE_X_ORG
	sta	LX
	lda	#SPRITE_Y_ORG
	sta	LY
L1:	lda	LX
	clc
	adc	#SPRITE_X_INC
	sta	LX
	lda	LY
	clc
	adc	#SPRITE_Y_INC
	sta	LY
	stx	FRMDRAW
	jmp	L1

compute_cols_and_rows:
	lda	#REQ_DPYINFO
	sta	REQPUT
	sta	REQEND
	lda	#>REQPUT
	sta	tmp1+1
	sta	tmp2+1
	lda	#<REQDAT+DPYINFO_WIDTH+0
	sta	tmp1
	lda	#<REQDAT+DPYINFO_WIDTH+1
	sta	tmp2
	jsr	pixels_to_tiles
	sta	cols
	lda	#<REQDAT+DPYINFO_HEIGHT+0
	sta	tmp1
	lda	#<REQDAT+DPYINFO_HEIGHT+1
	sta	tmp2
	jsr	pixels_to_tiles
	sta	rows
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
	sec
	sbc	#BORDER_SIZE
	cmp	#MAX_SIZE
	bmi	ok
	lda	#MAX_SIZE
ok:	rts

.data
_data_start_:

setbgcol: req
	.byte	REQ_SETBGCOL, COLOR_LIGHTBLUE
endreq

chars_image: req
	.byte	REQ_IPNGGEN, IMAGE_ID
	.word	8 * 1 ; width
	.word	8 * 9 ; height
	.byte	1 ; depth
	.byte	IPNGGEN_CT_INDEXED_COLOR
	.byte	IPNGGEN_FLAGS_PALREF
	.byte	1 ; number of entries - 1
	.byte	COLOR_BLUE    ; ref 0
	.byte	COLOR_LIGHTBLUE ; ref 1
	.byte	0,0,0,0,0,0,0,0 ; ' '
	.byte	124,102,102,124,120,108,102,0 ; 'R'
	.byte	126,96,96,120,96,96,126,0 ; 'E'
	.byte	24,60,102,126,102,102,102,0 ; 'A'
	.byte	120,108,102,102,102,108,120,0 ; 'D'
	.byte	102,102,102,60,24,24,24,0 ; 'Y'
	.byte	0,0,0,0,0,24,24,0 ; '.'
	.byte	102,102,102,102,102,102,60,0 ; 'U'
	.byte	102,118,126,126,110,102,102,0 ; 'N'
endreq

chars_layer:
	.word	end - begin
begin:	.byte	REQ_LTILED, CHARS_ID
	.byte	IMAGE_ID ; source image
	.byte	8 ; tile width
	.byte	8 ; tile height
	.byte	0 ; # of anim tiles
	.byte	DATATYPE_U8
cols:	.byte	0 ; # of columns (computed)
rows:	.byte	0 ; # of rows (computed)
end:

sprite_image: req
	.byte	REQ_IPNGGEN, IMAGE_ID
	.word	24 ; width
	.word	21 ; height
	.byte	1 ; depth
	.byte	IPNGGEN_CT_INDEXED_COLOR
	.byte	IPNGGEN_FLAGS_PALREF | IPNGGEN_FLAGS_IDX0TRANSP
	.byte	1 ; number of entries - 1
	.byte	COLOR_BLACK  ; ref 0 - unused because IDX0TRANSP is set
	.byte	COLOR_VIOLET ; ref 1
	.byte	0,127,0,1,255,192,3,255,224,3,231,224
	.byte	7,217,240,7,223,240,7,217,240,3,231,224
	.byte	3,255,224,3,255,224,2,255,160,1,127,64
	.byte	1,62,64,0,156,128,0,156,128,0,73,0,0,73,0
	.byte	0,62,0,0,62,0,0,62,0,0,28,0
endreq

sprite_layer: req
	.byte	REQ_LSPRITE, SPRITE_ID
	.byte	IMAGE_ID ; source image
endreq

idestroy: req
	.byte	REQ_IDESTROY, IMAGE_ID
endreq

lmview: req
	.byte	REQ_LMVIEW, CHARS_ID ; wiew is (0,0)-(chars.width,chars.height)
endreq

ltlfill: req
	.byte	REQ_LTLFILL, CHARS_ID
	.byte	1 ; " "
endreq

ltlput: req
	.byte	REQ_LTLPUT, CHARS_ID
	.word	0 ; x pos
	.word	1 ; y pos
	.word	6 ; columns
	.byte	2,3,4,5,6,7 ; "READY."
	.byte	2,8,9,1,1,1 ; "RUN   "
endreq

lsetpos: req
	.byte	REQ_LSETPOS, SPRITE_ID
	.byte	DATATYPE_I8
	.byte	-32 ; x
	.byte	-32 ; y
endreq
