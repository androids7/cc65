; mainargs.s
; Written by Emanuele Fornara

	.constructor	initmainargs, 24
	.import		__argc
	.import		__argv
	.import		_xv65_put_c_runtime
	.import		_xv65_argc
	.import		aslax1
	.import		pushax
	.import		tosaddax
	.import		tossubax
	.import		swapstk
	.import		incax2
	.importzp	sp
	.importzp	ptr1

	.include	"xv65.inc"

.segment	"ONCE"

initmainargs:

	;jsr	_xv65_put_c_runtime

	; can takeover REQPTRHI since no user code has run yet
	lda	#>req_argv
	sta	REQPTRHI

	; get argc
	jsr	_xv65_argc
	sta	__argc	
	stx	__argc+1

	; compute how much memory is needed (result: TOS: "size")
	jsr	aslax1		; ax: sizeof(argv[]) == argc*2
	jsr	pushax		; push total
	pha			; save sizeof(argv[]) for later
	txa
	pha
@l0:	lda	#<req_argv
	sta	REQPTRLO
	lda	REQDAT
	ldx	REQDAT+1	; ax: size of argv[n][]
	jsr	tosaddax	; ax += old total
	jsr	pushax		; push total
	inc	argv_n		; n++
	bne	@j0
	inc	argv_n+1
@j0:	lda	argv_n
	cmp	__argc		; is n == argc? no: next
	bne	@l0
	lda	argv_n+1
	cmp	__argc+1
	bne	@l0

	; allocate "size" bytes on the stack
	lda	sp		; ax: sp
	ldx	sp+1
	jsr	swapstk		; ax: size, TOS: sp
	jsr	tossubax	; ax: sp - size
	jsr	incax2		; word at TOS not needed anymore
	sta	sp		; new sp
	stx	sp+1

	; find out &argv[0] and &argv[0][0]
	sta	__argv
	stx	__argv+1
	sta	ptr1
	stx	ptr1+1
	jsr	pushax		; TOS: &argv[0]
	pla			; recover sizeof(argv[])
	tax
	pla
	jsr	tosaddax	; ax: &argv[0][0]
	sta	argv_ptr
	stx	argv_ptr+1

	; for n = 0 to argc - 1
	lda	#0
	sta	argv_n
	sta	argv_n+1
@l1:	ldy	#0
	lda	argv_ptr	; store argv[n]
	sta	(ptr1),y
	iny
	lda	argv_ptr+1
	sta	(ptr1),y
	dey			; get argv[n][] size again
	sty	argv_size
	sty	argv_size+1
	lda	#<req_argv
	sta	REQPTRLO
	lda	REQDAT		; for the next request use the right size
	sta	argv_size
	ldx	REQDAT+1
	stx	argv_size+1
	jsr	pushax		; save the size, so argv[n+1] can be computed
	lda	#<req_argv	; fill argv[n][]
	sta	REQPTRLO
	lda	argv_ptr	; argv[n+1] = argv[n] + sizeof(argv[n][])
	ldx	argv_ptr+1
	jsr	tosaddax
	sta	argv_ptr
	stx	argv_ptr+1
	lda	ptr1		; let ptr1 point to argv[n+1]
	clc
	adc	#2
	sta	ptr1
	bne	@j1
	inc	ptr1+1
@j1:	inc	argv_n		; n++
	bne	@j2
	inc	argv_n+1
@j2:	lda	argv_n
	cmp	__argc		; is n == argc? no: next
	bne	@l1
	lda	argv_n+1
	cmp	__argc+1
	bne	@l1

	; done
	;jsr	_xv65_put_c_runtime
	rts


.segment	"DATA"

req_argv:
	.word	7
	.byte	REQ_ARGV
argv_ptr:
	.word	0
argv_size:
	.word	0
argv_n:
	.word	0
