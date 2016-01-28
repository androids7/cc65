; Same as bgcol1, but using DMA.
; Requests can also be sent to the IO chip by putting the address of \
; the request in 2:5 (HI) and 2:4 (LO); the request starts with 2 bytes \
; storing the length of the data to be sent. \
; The DMA request is synchronous and starts when a value is written to 2:4.


	.include "io2.inc"

.code

	lda	#>_data_start_
	sta	REQPTRHI
	lda	#ENABLE_BGCOL
	sta	ENABLE
	lda	#<setbgcol
	sta	REQPTRLO
	brk

.data
_data_start_:

setbgcol: req
	.byte	REQ_SETBGCOL, COLOR_BLACK
endreq	
