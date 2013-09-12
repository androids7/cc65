; test requests

	.include "xv65.inc"

.code

	lda	#REQ_GETPID
	sta	REQPUT
	sta	REQEND

	lda	#>_data_start_
	sta	REQPTRHI
	lda	#<getpid
	sta	REQPTRLO

	brk

.data
_data_start_:

getpid: req
	.byte	REQ_GETPID
endreq
