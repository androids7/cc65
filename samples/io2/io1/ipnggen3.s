; Show a (mafgnified) multi-color image stored inside the program. \
; The RGB palette is used.

	.include "io2.inc"

.code

	lda	#ENABLE_BGCOL|ENABLE_BGIMG
	sta	ENABLE
	lda	#>_data_start_
	sta	REQPTRHI
	lda	#<setpal
	sta	REQPTRLO
	lda	#<setbgcol
	sta	REQPTRLO
	lda	#<ipnggen
	sta	REQPTRLO
	lda	#<setbgimg
	sta	REQPTRLO
	brk

.data
_data_start_:

IMAGE_ID = 1

setpal: req
	.byte	REQ_SETPAL
	.byte	SETPAL_RGB
endreq

setbgcol: req
	.byte	REQ_SETBGCOL, 10
endreq

setbgimg: req
	.byte	REQ_SETBGIMG, IMAGE_ID
endreq

ipnggen: req
	.byte	REQ_IPNGGEN, IMAGE_ID
	.word	16 ; width
	.word	16 ; height
	.byte	2 ; depth
	.byte	IPNGGEN_CT_INDEXED_COLOR
	.byte	IPNGGEN_FLAGS_PALREF | IPNGGEN_FLAGS_ZOOM1
	.byte	3 ; palette 0..3 x (1 if PALREF is set, 3 (RGB) if not)
	.byte	10,0,124,93 ; refs
	.byte	0,0,0,0
	.byte	0,0,0,0
	.byte	0,0,0,0
	.byte	51,51,51,48
	.byte	85,85,85,84
	.byte	86,106,89,148
	.byte	86,101,149,164
	.byte	86,106,89,148
	.byte	86,101,153,148
	.byte	105,106,89,148
	.byte	85,85,85,84
	.byte	51,51,51,48
	.byte	0,0,0,0
	.byte	0,0,0,0
	.byte	0,0,0,0
	.byte	0,0,0,0
endreq
