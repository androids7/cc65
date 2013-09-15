; print 256 color palette (xterm only)

	.include "xv65.inc"

STRPTR = 4

.code

setup_pointers:
	lda #>_data_start_
	sta REQPTRHI
	sta STRPTR+1

check_env:
	lda #<env
	sta REQPTRLO
	ldy #5
@l:	lda buf,y
	cmp xterm,y
	bne print_error
	dey
	bpl @l

print_palette:
	ldx #0
@l:	lda #<prefix
	sta STRPTR
	jsr put_string
	stx PUTUINT8
	lda #<postfix
	sta STRPTR
	jsr put_string
	txa
	and #$0f
	cmp #$0f
	bne @j
	lda #10
	sta PUTCHAR
@j:	inx
	bne @l
	brk

print_error:
	lda #<error_msg
	sta STRPTR
	jsr put_string
	brk

put_string:
	ldy #0
@l:	lda (STRPTR),y
	beq @r
	sta PUTCHAR
	iny
	bne @l
@r:	rts

.data
_data_start_:

env: req
	.byte REQ_ENV
	.word buf
	.word 6
	.byte "TERM", 0
endreq

error_msg:
	.byte "xterm not detected.", 10, 0

xterm:
	.byte "xterm", 0

prefix:
	.byte $1b, "[48;5;" , 0

postfix:
	.byte "m  ", $1b, "[0m", 0

buf:
