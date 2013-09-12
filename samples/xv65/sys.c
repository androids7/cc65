// test system calls

#include <xv65.h>

#define req_put(x)	(*(unsigned char*)REQPUT = (x))
#define req_end()	(*(unsigned char*)REQEND = 0)

typedef unsigned char byte;

void debug(byte mode) {
	req_put(REQ_DEBUG);
	req_put(mode);
	req_end();
}

int main(void) {
	debug(1);
	return 0;
}
