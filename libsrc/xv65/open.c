// open.c
// Written by Emanuele Fornara

#include <errno.h>
#include <fcntl.h>
#include <xv65.h>

int open(const char *filename, int flags, ...) {
	req_put(REQ_OPEN);
	req_put_string(filename);
	req_put(flags);
	req_end();
	if (req_res())
		return _mappederrno(req_res());
	return *(unsigned char *)REQDAT;
}
