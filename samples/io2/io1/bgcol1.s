; Set the background color.
; Requests can be sent to the IO chip by streaming them into 2:1 and \
; then terminating them by putting any value into 2:2.
; The console is disabled using the register 2:16.

	.include "io2.inc"

.code

	lda	#ENABLE_BGCOL
	sta	ENABLE
	lda	#REQ_SETBGCOL
	sta	REQPUT
	lda	#COLOR_BLACK
	sta	REQPUT
	sta	REQEND
	brk
