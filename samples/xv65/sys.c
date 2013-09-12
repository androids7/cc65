// test system calls

#include <xv65.h>

#define putchar(x)	(*(unsigned char*)PUTCHAR = (x))
#define req_put(x)	(*(unsigned char*)REQPUT = (x))
#define req_end()	(*(unsigned char*)REQEND = 0)
#define req_res()	(*(unsigned char*)REQRES)
#define req_dat(x)	(((unsigned char*)REQRES)[(x)])

typedef unsigned char byte;

void print(const char *s) {
	unsigned char i, c;
	for (i = 0; c = s[i]; i++)
		putchar(c);
	putchar('\n');
}

void debug(byte mode) {
	req_put(REQ_DEBUG);
	req_put(mode);
	req_end();
}

// These are just quick tests. A proper implementation should be written
// in assembly, hence the non-standard sys_ prefix.

long sys_fork() {
	req_put(REQ_SYS_fork);
	req_end();
	if (req_res())
		return -1;
	return *(long *)REQDAT;
}

void sys_exit(byte status) {
	req_put(REQ_SYS_exit);
	req_put(status); // it's actually optional (default: 0)
	req_end();
}

long sys_wait() {
	req_put(REQ_SYS_wait);
	req_end();
	if (req_res())
		return -1;
	return *(long *)REQDAT;
}

void test1() {
	sys_exit(0);
	print("error: should not be reached");
}

void test2() {
	long pid;

	pid = sys_fork();
	if (pid > 0) {
		print("parent");
		pid = sys_wait();
		print("child is done");
	} else if (pid == 0) {
		print("childern: exiting");
		sys_exit(0);
	} else {
		print("fork error");
	}
}

int main(void) {
	test2();
	return 0;
}
