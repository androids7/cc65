// xv65_req_put_string.c
// Written by Emanuele Fornara

#include <xv65.h>

void __fastcall__ xv65_req_put_string(const char *s) {
        unsigned char c;
        while (c = *s++)
                *(unsigned char *)REQPUT = c;
	*(unsigned char *)REQPUT = 0;
}
