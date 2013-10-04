// xv65_env.c
// Written by Emanuele Fornara

#include <errno.h>
#include <xv65.h>

int __fastcall__ xv65_env(const char *name, char *buf, unsigned int *size) {
	req_put(REQ_ENV);
	req_put_word((unsigned int)buf);
	req_put_word(*size);
	req_put_string(name);
	req_end();
	*size = *(unsigned int *)REQDAT;
	return _mappederrno(req_res());
}
