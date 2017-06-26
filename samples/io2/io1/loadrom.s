; Use data from "/cga.rom" to fill an IPNGGEN request.

	.include "io2.inc"

.code

	lda	#ENABLE_BGCOL|ENABLE_BGIMG
	sta	ENABLE
	lda	#>_data_start_
	sta	REQPTRHI
	lda	#<loadrom
	sta	REQPTRLO
	lda	#<ipnggen
	sta	REQPTRLO
	lda	#<setbgimg
	sta	REQPTRLO
	brk

.data
_data_start_:

IMAGE_ID = 1

loadrom: req
	.byte	REQ_LOADROM
	.word	ipnggen_data
	.byte	"/cga.rom", 0
	.word	'A' * 8 ; offset
	.word	24 ; size
endreq

ipnggen:
	.word	ipnggen_end - @start
@start:	.byte	REQ_IPNGGEN, IMAGE_ID
	.word	8 ; width
	.word	24 ; height
	.byte	1 ; depth
	.byte	IPNGGEN_CT_INDEXED_COLOR
	.byte	IPNGGEN_FLAGS_PALREF | IPNGGEN_FLAGS_ZOOM1
	.byte	1 ; palette 0..1 x (1 if PALREF is set, 3 (RGB) if not)
	.byte	COLOR_BLUE ; ref 0
	.byte	COLOR_RED ; ref 1
ipnggen_data:
	.byte	0,0,0,0,0,0,0,0
	.byte	0,0,0,0,0,0,0,0
	.byte	0,0,0,0,0,0,0,0
ipnggen_end:

setbgimg: req
	.byte	REQ_SETBGIMG, IMAGE_ID
endreq
