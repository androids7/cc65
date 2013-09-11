;
; xv65.inc
;

PUTCHAR = $0200

REQPUT = $0201
REQEND = $0202
REQRES = $0203

REQPTRLO = $0204
REQPTRHI = $0205

.macro	req
@_req_: .word @_endreq_ - @_req_ - 2
.endmacro

.macro	endreq
@_endreq_:
.endmacro
