// test system calls

#include <stdio.h>
#include <xv65.h>

#define putchar(x)	(*(unsigned char*)PUTCHAR = (x))
#define req_put(x)	(*(unsigned char*)REQPUT = (x))
#define req_end()	(*(unsigned char*)REQEND = 0)
#define req_res()	(*(unsigned char*)REQRES)
#define req_dat(x)	(((unsigned char*)REQRES)[(x)])

typedef unsigned char byte;

int __fastcall__ write (int, const void* buf, unsigned count) {
	const char *s = (const char *)buf;
	unsigned i;
	for (i = 0; i < count; i++)
		putchar(s[i]);
	return count;
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
	printf("error: should not be reached\n");
}

void test2() {
	long pid;

	pid = sys_fork();
	if (pid > 0) {
		printf("parent: child=%ld\n", pid);
		pid = sys_wait();
		printf("child %ld is done\n", pid);
	} else if (pid == 0) {
		printf("childern: exiting\n");
		sys_exit(0);
	} else {
		printf("fork error\n");
	}
}

int main(void) {
	test2();
	return 0;
}
