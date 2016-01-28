;
; Written by Emanuele Fornara
;
; C runtime startup code
;

	.export		_exit
        .export         __STARTUP__ : absolute = 1      ; Mark as startup

	.import		__RAM_START__, __RAM_SIZE__

	.importzp	sp
	.import		initlib, donelib, callmain

	.include	"io2.inc"


.include	"header.s"


.segment       	"STARTUP"

start:
	lda	#<(__RAM_START__ + __RAM_SIZE__)
	sta	sp
	lda	#>(__RAM_START__ + __RAM_SIZE__)
	sta	sp+1
	jsr	initlib
       	jsr    	callmain
_exit:
	jsr	donelib
   	brk

