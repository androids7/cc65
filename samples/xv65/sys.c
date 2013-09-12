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

void req_put_value(int size, long value) {
	int i;
	char *buf = (char *)&value;
	for (i = 0; i < size; i++)
		req_put(buf[i]);
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

void sys_exit(int /*status*/) {
	req_put(REQ_SYS_exit);
	req_end();
}

long sys_wait() {
	req_put(REQ_SYS_wait);
	req_end();
	if (req_res())
		return -1;
	return *(long *)REQDAT;
}

void sys_kill(long pid, byte sig) {
	req_put(REQ_SYS_kill);
	req_put(sig); // optional (15 - SIGTERM is the default)
	*(long *)REQDAT = pid;
	req_end();
}

long sys_getpid() {
	req_put(REQ_SYS_getpid);
	req_end();
	return *(long *)REQDAT;
}

void sys_sleep(unsigned w) {
	req_put(REQ_SYS_sleep);
	/*
		Trailing ints can be sent using 0 to 4 bytes.
		Value is sign-extended and default to 0.
	*/
	if (w == 0)
		req_put_value(0, w);
	else if (w > 127)
		req_put_value(4, w);
	else
		req_put_value(1, w);
	req_end();
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

void test3() {
	long pid;
	int w;

	/*
		The size of pid is assumed to be 4 bytes, so long is fine.
		To be conpatible with systems with pid == 8,
		you could treat pids as opaque data buffers and always
		reserve 8 bytes for each of them.
		The actual size used by xv65 (the amount you need to copy,
		check, etc... is available in PIDSIZE).
	*/
	printf("size of long is %d (expecting 4)\n", sizeof(long));
	printf("size of pid_t is %d (expecting 4)\n", *((char *)PIDSIZE));
	pid = sys_fork();
	if (pid > 0) {
		printf("parent: child=%ld\n", pid);
		printf("parent: waiting %ds\n", w = 3);
		sys_sleep(w);
		printf("parent: interrupting child\n");
		// SIGALRM is silently handled by the current vers. of xv65
		sys_kill(pid, KILL_SIGALRM);
		pid = sys_wait();
		printf("child %ld is done\n", pid);
	} else if (pid == 0) {
		pid = sys_getpid();
		printf("children (%ld): waiting %ds\n", pid, w = 1000);
		sys_sleep(w);
		printf("children: interrupted, exiting\n");
	}
}
int main(void) {
	test3();
	return 0;
}
