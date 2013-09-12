; test requests

	.include "xv65.inc"

.code

	lda	#REQ_DEBUG
	sta	REQPUT
	lda	#1
	sta	REQPUT
	sta	REQEND

	lda	#>_data_start_
	sta	REQPTRHI
	lda	#<debug
	sta	REQPTRLO

	brk

.data
_data_start_:

debug: req
	.byte	REQ_DEBUG, 0
endreq
