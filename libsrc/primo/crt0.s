;
; Written by Emanuele Fornara
;
; C runtime startup code (RAM)
;

	.export __STARTUP__ : absolute = 1 ; Mark as startup

	.import __CONSTRUCTOR_TABLE__, __CONSTRUCTOR_COUNT__
	.import __DESTRUCTOR_TABLE__, __DESTRUCTOR_COUNT__

	.import start1
	.import _main

	.include "jbit.inc"
	.include "header.s"

	.segment "STARTUP"

start0:
	lda #<prog_info
	ldx #>prog_info
	jmp start1

	.segment "RODATA"

prog_info:
	.word _main
	.word __CONSTRUCTOR_TABLE__
	.byte <__CONSTRUCTOR_COUNT__
	.word __DESTRUCTOR_TABLE__
	.byte <__DESTRUCTOR_COUNT__
