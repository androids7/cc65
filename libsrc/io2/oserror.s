;
; Ullrich von Bassewitz, 17.05.2000
; JBit port by Emanuele Fornara
;
; int __fastcall__ _osmaperrno (unsigned char oserror);
; /* Map a system specific error into a system independent code */
;

        .include        "errno.inc"

.code

__osmaperrno:
        lda     #<EUNKNOWN
        ldx     #>EUNKNOWN
        rts
