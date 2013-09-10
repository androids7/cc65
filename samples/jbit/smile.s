; Test assembler (no C runtime).

	.include "jbit.inc"

.code

	lda	#ENABLE_BGCOL|ENABLE_BGIMG
	sta	ENABLE
	lda	#>_data_start_
	sta	REQPTRHI
	lda	#<ipnggen
	sta	REQPTRLO
	lda	#<setbgcol
	sta	REQPTRLO
	lda	#<setbgimg
	sta	REQPTRLO
	brk

.data
_data_start_:

IMAGE_ID = 1

ipnggen: req
	.byte	REQ_IPNGGEN, IMAGE_ID
	.word	8 ; width
	.word	8 ; height
	.byte	1 ; depth
	.byte	IPNGGEN_CT_INDEXED_COLOR
	.byte	IPNGGEN_FLAGS_PALREF | IPNGGEN_FLAGS_IDX0TRANSP | IPNGGEN_FLAGS_ZOOM0 | IPNGGEN_FLAGS_ZOOM1
	.byte	1 ; palette 0..1 x (1 if PALREF is set, 3 (RGB) if not)
	.byte	COLOR_WHITE  ; ref 0 - unused because IDX0TRANSP is set
	.byte	COLOR_YELLOW ; ref 1
	.byte	%01111110
	.byte	%11111111
	.byte	%11011011
	.byte	%11111111
	.byte	%11000011
	.byte	%11100111
	.byte	%11111111
	.byte	%01111110
endreq

setbgcol: req
	.byte	REQ_SETBGCOL, COLOR_GREEN
endreq

setbgimg: req
	.byte	REQ_SETBGIMG, IMAGE_ID
endreq
