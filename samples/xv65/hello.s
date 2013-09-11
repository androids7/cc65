; Hello World in assembly

	.include "xv65.inc"

.code

	ldx	#0
@l1:	lda	msg,X
	beq	exit
	sta	PUTCHAR
	inx
	bne	@l1
exit:
	brk

.data

msg: 
	.byte	"Hello, World!", 10, 0
