; Show an image stored inside the program.
; Color is at 4:13; bitmap starts at 4:14 (24px x 21px = 63bytes).

	.include "io2.inc"

.code

	lda	#ENABLE_BGCOL|ENABLE_BGIMG
	sta	ENABLE
	lda	#>_data_start_
	sta	REQPTRHI
	lda	#<ipnggen
	sta	REQPTRLO
	lda	#<setbgimg
	sta	REQPTRLO
	brk

.data
_data_start_:

IMAGE_ID = 1

ipnggen: req
	.byte	REQ_IPNGGEN, IMAGE_ID
	.word	24 ; width
	.word	21 ; height
	.byte	1 ; depth
	.byte	IPNGGEN_CT_INDEXED_COLOR
	.byte	IPNGGEN_FLAGS_PALREF | IPNGGEN_FLAGS_IDX0TRANSP
	.byte	1 ; palette 0..1 x (1 if PALREF is set, 3 (RGB) if not)
	.byte	COLOR_GRAY3 ; ref 0 - unused because IDX0TRANSP is set
	.byte	COLOR_BLACK ; ref 1
	.byte	0,127,0,1,255,192,3,255,224,3,231,224
	.byte	7,217,240,7,223,240,7,217,240,3,231,224
	.byte	3,255,224,3,255,224,2,255,160,1,127,64
	.byte	1,62,64,0,156,128,0,156,128,0,73,0,0,73,0
	.byte	0,62,0,0,62,0,0,62,0,0,28,0
endreq

setbgimg: req
	.byte	REQ_SETBGIMG, IMAGE_ID
endreq
