; chdir.s
; Written by Emanuele Fornara

	.export		_chdir
	.import		xv65_file1

	.include	"xv65.inc"

.segment	"CODE"

; int __fastcall__ chdir(const char *filename)  [unistd]
_chdir:
	ldy	#REQ_CHDIR
	jmp	xv65_file1
