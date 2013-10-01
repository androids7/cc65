; xv65_mkdir.s
; Written by Emanuele Fornara

	.export		_xv65_mkdir
	.import		xv65_file1

	.include	"xv65.inc"

.segment	"CODE"

; int __fastcall__ xv65_mkdir(const char *filename)
_xv65_mkdir:
	ldy	#REQ_MKDIR
	jmp	xv65_file1
