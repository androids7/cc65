// xv65_req_put_string.c
// Written by Emanuele Fornara

#include <xv65.h>

void __fastcall__ xv65_req_put_string(const char *s) {
        unsigned char c;
        while (c = *s++)
                req_put(c);
	req_put(0);
}
