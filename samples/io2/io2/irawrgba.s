; Same as ipnggen2, but using a MIDP2-only feature.
; The generation of the image is faster, but only RGBA8 is supported.

	.include "io2.inc"

RED = 2
BLUE = 3
ALPHA = 4

WIDTH = 32
HEIGHT = 32
RED_INC = 255 / WIDTH
BLUE_INC = 255 / HEIGHT

.code

	lda	#>_data_start_
	sta	REQPTRHI
	lda	#ENABLE_BGCOL|ENABLE_BGIMG
	sta	ENABLE
	ldx	#0
L1:	lda	irawrgba+2,x
	sta	REQPUT
	inx
	cpx	irawrgba
	bne	L1
	ldy	#HEIGHT
	lda	#0
	sta	BLUE
L3:	ldx	#WIDTH
	lda	#0
	sta	RED
L2:	lda	RED
	sta	REQPUT
	lda	#0 ; green
	sta	REQPUT
	lda	BLUE
	sta	REQPUT
	stx	ALPHA
	tya           ; a = y [1..32]
	clc
	adc	ALPHA ; a = x + y [2..64]
	asl
	asl           ; a = 4 * (x + y) [8..256]
	sec
	sbc	#1    ; a = 4 * (x + y) - 1 [7..255]
	sta	REQPUT
	clc
	lda	RED
	adc	#RED_INC
	sta	RED
	dex
	bne	L2
	clc
	lda	BLUE
	adc	#BLUE_INC
	sta	BLUE
	dey
	bne	L3
	sta	REQEND
	lda	#<setbgimg
	sta	REQPTRLO
	brk

.data
_data_start_:

IMAGE_ID = 1

irawrgba: req
	.byte	REQ_IRAWRGBA, IMAGE_ID
	.word	WIDTH
	.word	HEIGHT
	.byte	IRAWRGBA_FLAGS_ALPHA
endreq

setbgimg: req
	.byte	REQ_SETBGIMG, IMAGE_ID
endreq
