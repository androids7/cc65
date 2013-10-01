; rmdir.s
; Written by Emanuele Fornara

	.export		_rmdir
	.import		xv65_file1

	.include	"xv65.inc"

.segment	"CODE"

; int __fastcall__ rmdir(const char *filename)  [unistd]
_rmdir:
	ldy	#REQ_RMDIR
	jmp	xv65_file1
