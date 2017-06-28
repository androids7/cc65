; Load the image "/icon.png" from the jar and show it.

	.include "io2.inc"

.code

	lda	#>_data_start_
	sta	REQPTRHI
	lda	#ENABLE_BGCOL|ENABLE_BGIMG
	sta	ENABLE
	lda	#<setbgcol
	sta	REQPTRLO
	lda	#<iload
	sta	REQPTRLO
	lda	#<setbgimg
	sta	REQPTRLO
	brk

.data
_data_start_:

IMAGE_ID = 1

setbgcol: req
	.byte REQ_SETBGCOL
	.byte 50, 150, 50
endreq

iload: req
	.byte	REQ_ILOAD, IMAGE_ID, "/icon.png", 0
endreq

setbgimg: req
	.byte	REQ_SETBGIMG, IMAGE_ID
endreq
