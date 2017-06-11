;
; Written by Emanuele Fornara
;
; header.s
;

	.import		__RODATA_LOAD__
	.import		__EOD_LOAD__
	.import		__RAM_START__


.segment	"HEADER"

	; JBit Signature (4 bytes, charset is ASCII)
	.byte	"JBit"

	; Header Length (Hi)
	.byte	0

	; Header Length (Lo)
	.byte	12

	; File Version (Major)
	.byte	1

	; File Version (Minor)
	.byte	0

	; Code Size (in pages)
	.byte	>(__RODATA_LOAD__ - __RAM_START__)

	; Data Size (in pages)
	.byte	>(__EOD_LOAD__ - __RODATA_LOAD__)

	; Device ID
	.ifdef	JBFMT_DEVID
	.byte	JBFMT_DEVID
	.else
	.byte	2
	.endif

	; Reserved for future use
	.byte	0

	; The header is followed by the program itself.
	; The program is structured as code pages followed by data pages.
	; Pages are 256-bytes long and are zero filled (compression is
	; delegated to the Jar).

	; The program is loaded at address $300 (768), where it starts.
	; Page 2 is where the IO chip is mapped, page 255 is reserved
	; for future use.


.segment	"EOD"

	; end of data

