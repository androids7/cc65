// xv65_argv.c
// Written by Emanuele Fornara

#include <xv65.h>

int __fastcall__ xv65_argv(unsigned int i, char *buf, unsigned int *size) {
        req_put(REQ_ARGV);
        req_put_word((unsigned int)buf);
        req_put_word(*size);
        req_put_word(i);
        req_end();
        *size = *(unsigned int *)REQDAT;
        return req_res() ? -1 : 0;
}
