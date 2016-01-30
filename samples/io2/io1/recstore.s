; Test the Record Store API.

	.include "io2.inc"

SIZE = 10

.code

	lda #>_data_start_
	sta REQPTRHI

update_screen:
	ldx #39
@loop:
	lda screen,x
	sta CONVIDEO,x
	dex
	bpl @loop

load_record:
	lda #<rload
	sta REQPTRLO
	lda REQRES
	beq show

not_found:
	lda #'?'
	jsr set

show:
	ldx #0
@loop:
	lda buffer,x
	sta CONROW3,x
	inx
	cpx #SIZE
	bne @loop

wait_key:
	sta FRMDRAW
next:
	lda KEYBUF
	beq next
	sta KEYBUF

command:
	cmp #'*'
	beq quit
	cmp #'#'
	beq delete_record

save_record:
	jsr set
	lda #<rsave
	sta REQPTRLO
	jmp update_screen

delete_record:
	lda #<rdelete
	sta REQPTRLO
	jmp update_screen

set:
	ldx #0
@loop:
	sta buffer,x
	inx
	cpx #SIZE
	bne @loop
	rts

quit:
	brk

.data
_data_start_:

screen:
	.byte "0-9: save "
	.byte "#:delete  "
	.byte "*:exit    "
	.byte "          "

rload: req
	.byte REQ_RLOAD
	.word buffer
	.word SIZE
	.byte "recstore", 0
endreq

rsave: req
	.byte REQ_RSAVE
	.word buffer
	.word SIZE
	.byte "recstore", 0
endreq

rdelete: req
	.byte REQ_RDELETE
	.byte "recstore", 0
endreq

buffer:
