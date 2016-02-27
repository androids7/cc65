; Use 2, 4, 6 and 8 to collect the items. Hit the bomb when you get bored.

	.include "io2.inc"
	.include "silk.inc"

; zero page
posx = 2
posy = 3
item = 4
cols = 5
rows = 6

.code

	lda #>_data_start_
	sta REQPTRHI
	lda #<setbgcol
	sta REQPTRLO
	lda #<gameset
	sta REQPTRLO
	ldx REQDAT+GAMESET_COLS
	dex
	stx cols
	ldx REQDAT+GAMESET_ROWS
	dex
	stx rows

	lda #SILK_bomb
	jsr place
	lda #SILK_emoticon_smile
	jsr place
	stx posx
	sty posy
	lda #1
	sta item
	jsr place

loop:
	jsr waitkey
	jsr clear
	jsr move
	jsr update
	jmp loop

clear:
	; accumulator (waitkey result) must be kept
	ldx posx
	stx TCOLLO
	ldx posy
	stx TROWLO
	ldx #0
	stx TCELL
	rts

move:
	cmp #'2'
	beq @up
	cmp #'4'
	beq @left
	cmp #'6'
	beq @right
	cmp #'8'
	beq @down
@ret:
	rts
@up:
	lda posy
	beq @ret
	dec posy
	rts
@left:
	lda posx
	beq @ret
	dec posx
	rts
@right:
	lda posx
	cmp cols
	beq @ret
	inc posx
	rts
@down:
	lda posy
	cmp rows
	beq @ret
	inc posy
	rts

update:
	lda posx
	sta TCOLLO
	lda posy
	sta TROWLO
	lda TCELL
	pha
	lda #SILK_emoticon_smile
	sta TCELL
	pla
	beq @ret
	cmp #SILK_bomb
	beq exit
	bne @next
@next:
	ldx item
@skip:
	inx
	cpx #SILK_emoticon_smile
	beq @skip
	cpx #SILK_emoticon_unhappy
	beq @skip
	cpx #SILK_bomb
	beq @skip
	cpx #SILK__n + 1
	bne @ok
	ldx #1
@ok:
	stx item
	txa
	jsr place
@ret:
	rts

place:
	pha
	ldx cols
	stx RANDOM 
	ldx RANDOM
	stx TCOLLO
	ldy rows
	sty RANDOM 
@retry:
	ldy RANDOM
	sty TROWLO
	lda TCELL
	bne @retry
	pla
	sta TCELL
	rts

exit:
	lda #SILK_emoticon_unhappy
	sta TCELL
	jsr waitkey
	brk

waitkey:
	sta FRMDRAW
	lda KEYBUF
	beq waitkey
	sta KEYBUF
	rts

.data

_data_start_:

setbgcol: req
	.byte REQ_SETBGCOL
	.byte 100, 200, 100
endreq

gameset: req
	.byte REQ_GAMESET
endreq
