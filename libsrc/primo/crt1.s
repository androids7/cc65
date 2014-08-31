;
; Written by Emanuele Fornara
;
; C runtime startup code (ROM)
;

	.export start1, _exit

	.import __RAM_START__, __RAM_SIZE__

	.import pusha, pushax, popa, addysp

	.importzp sp, tmp1

start1:
	; setup the stack
	ldy	#<(__RAM_START__ + __RAM_SIZE__)
	sty	sp
	ldy	#>(__RAM_START__ + __RAM_SIZE__)
	sty	sp+1

	; in jbit ram is initially 0-filled, there's no need for zerobss

	; saveax to avoid calling get_prog_info after pushax
	sta tmp1
	stx tmp1+1
	; keep a pointer to prog_info (needed for destructors)
	jsr pushax

	; constructor table info is at offset #2
	; jsr get_prog_info (not needed; tmp1, tmp1+1 is already set)
	ldy #2
	jsr do_condes

	; main ptr is at offset #0
	jsr get_prog_info
	ldy #0+1
	jsr do_call

_exit:
	; destructor table info is at offset #5
	jsr get_prog_info
	ldy #5
	jsr do_condes
	brk

get_prog_info:
	; recover prog_info from the stack
	ldy	#<(__RAM_START__ + __RAM_SIZE__ - 2)
	sty	tmp1+1
	ldy	#>(__RAM_START__ + __RAM_SIZE__ - 2)
	sty	tmp1+2
	ldy #0
	lda (tmp1+1),y
	sta tmp1
	iny
	lda (tmp1+1),y
	sta tmp1+1
	rts

do_condes:
	; push table ptr
	iny
	tya
	pha
	lda (tmp1),y
	tax
	dey
	lda (tmp1),y
	jsr pushax
	; push table count
	pla
	tay
	iny
	lda (tmp1),y
	jsr pusha
next_record:
	; any more records?
	jsr popa
	cmp #0
	bne callsub
	; no - pop table ptr and return
	ldy #2
	jmp addysp ; jsr+rts
callsub:
	; yes - prepare for next record
	sec
	sbc #1 ; a: n--
	jsr pusha ; update table count
	asl ; a : n*2
	tax ; save it
	; retrieve table ptr
	ldy #1
	lda (sp),y
	sta tmp1
	iny
	lda (sp),y
	sta tmp1+1
	; call routine
	txa ; restore n*2
	tay
	iny ; n*2+1
	jsr do_call
	; next iteration
	jmp next_record

do_call:
	lda (tmp1),y
	sta tmp1+2
	dey
	lda (tmp1),y
	sta tmp1+1
	dey
	lda #76 ; JMP opcode
	sta tmp1
	jmp tmp1 ; jsr+rts
