// execvp.c
// Written by Emanuele Fornara

#include <xv65.h>

int execvp(const char *filename, char *argv[]) {
	static int i;

	req_put(REQ_EXEC);
	req_put_string(filename);
	for (i = 0; argv[i]; i++)
		req_put_string(argv[i]);
	req_end();
	return req_res() ? -1 : 0;
}
