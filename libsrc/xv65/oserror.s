;
; Ullrich von Bassewitz, 17.05.2000
; xv65 port by Emanuele Fornara
;
; int __fastcall__ _osmaperrno (unsigned char oserror);
; /* Map a system specific error into a system independent code */
;

        .include        "errno.inc"

.code

__osmaperrno:
        ldx     #ErrTabSize
@L1:    cmp     ErrTab-2,x      ; Search for the error code
        beq     @L2             ; Jump if found
        dex
        dex
        bne     @L1             ; Next entry

; Code not found, return EUNKNOWN

        lda     #<EUNKNOWN
        ldx     #>EUNKNOWN
        rts

; Found the code

@L2:    lda     ErrTab-1,x
        ldx     #$00            ; High byte always zero
        rts

.rodata

ErrTab:
	; matching codes from xv65.inc (not included for name clash)
	.byte 0, EOK
	.byte 2, ENOENT
	.byte 4, EINTR
	.byte 5, EIO
	.byte 9, EBADF
	.byte 11, EAGAIN
	.byte 13, EACCES
	.byte 16, EBUSY
	.byte 17, EEXIST
	.byte 19, ENODEV
	.byte 22, EINVAL
	.byte 24, EMFILE
	.byte 28, ENOSPC
	.byte 29, ESPIPE
	.byte 34, ERANGE

ErrTabSize = (* - ErrTab)
