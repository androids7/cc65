; unlink.s
; Written by Emanuele Fornara

	.export		_unlink
	.import		xv65_file1

	.include	"xv65.inc"

.segment	"CODE"

; int __fastcall__ unlink(const char *filename)  [unistd.h]
_unlink:
	ldy	#REQ_UNLINK
	jmp	xv65_file1
