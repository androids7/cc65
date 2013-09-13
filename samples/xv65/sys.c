// test system calls

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

/*

These are just quick tests. A proper implementation should be written
in assembly, hence the non-standard sys_ prefix.

The size of pid is assumed to be 4 bytes, so long is fine. To be
compatible with systems with pid == 8, you could treat pids as opaque
data buffers and always reserve 8 bytes for each of them. The actual
size used by xv65 (the amount you need to copy, check, etc... is
available in PIDSIZE).

REQRES is a return code set at every request. REQERRNO is a "sticky"
code that remembers the last failed return code - it can be (re)set by
the program.

*/

void req_put_value(int size, long value) {
	int i;
	char *buf = (char *)&value;
	for (i = 0; i < size; i++)
		req_put(buf[i]);
}

void req_put_string(const char *s) {
	char c;
	while (c = *s++)
		req_put(c);
	req_put(0);
}

#define CHECK(name) printf("syscall %s returned %d\n", name, ret)

long sys_fork() {
	req_put(REQ_FORK);
	req_end();
	if (req_res())
		return -1;
	return *(long *)REQDAT;
}

void sys_exit(int status) {
	req_put(REQ_EXIT);
	req_put_value(status, 2);
	req_end();
}

long sys_wait() {
	req_put(REQ_WAIT);
	req_end();
	if (req_res())
		return -1;
	return *(long *)REQDAT;
}

void sys_kill(long pid, byte sig) {
	req_put(REQ_KILL);
	req_put(sig); // optional (15 - SIGTERM is the default)
	*(long *)REQDAT = pid;
	req_end();
}

long sys_getpid() {
	req_put(REQ_GETPID);
	req_end();
	return *(long *)REQDAT;
}

void sys_sleep(unsigned w) {
	req_put(REQ_SLEEP);
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

void sys_exec(const char *filename, char *argv[]) {
	int i;

	req_put(REQ_EXEC);
	req_put_string(filename);
	for (i = 0; argv[i]; i++)
		req_put_string(argv[i]);
	req_end();
}

int sys_open(const char *filename, int flags) {
	req_put(REQ_OPEN);
	req_put_string(filename);
	req_put(flags);
	req_end();
	if (req_res())
		return -1;
	return *(byte *)REQDAT;
}

int do_rdwr(int fd, void *buf, int n, int req_id) {
	req_put(req_id);
	req_put(fd);
	req_put_value(2, (long)buf);
	req_put_value(2, n);
	req_end();
	if (req_res())
		return -1;
	return *(int *)REQDAT;
}

int sys_read(int fd, void *buf, int n) {
	return do_rdwr(fd, buf, n, REQ_READ);
}

int sys_write(int fd, void *buf, int n) {
	return do_rdwr(fd, buf, n, REQ_WRITE);
}

int sys_close(int fd) {
	req_put(REQ_CLOSE);
	req_put(fd);
	req_end();
	if (req_res())
		return -1;
}

int sys_pipe(int *p) {
	req_put(REQ_PIPE);
	req_end();
	if (req_res())
		return -1;
	p[0] = *(int *)REQDAT;
	p[1] = *(int *)(REQDAT + 8);
	return 0;
}

int sys_dup(int fd) {
	req_put(REQ_DUP);
	req_put(fd);
	req_end();
	if (req_res())
		return -1;
	return *(byte *)REQDAT;
}

int do_filename(const char *filename, int req_id) {
	req_put(req_id);
	req_put_string(filename);
	req_end();
	if (req_res())
		return -1;
	return 0;
}

int sys_chdir(const char *filename) {
	return do_filename(filename, REQ_CHDIR);
}

int sys_mkdir(const char *filename) {
	return do_filename(filename, REQ_MKDIR);
}

int sys_unlink(const char *filename) {
	return do_filename(filename, REQ_UNLINK);
}

void test_exit() {
	sys_exit(0);
	printf("error: should not be reached\n");
}

void test_fork() {
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

void test_kill() {
	long pid;
	int w;

	printf("size of long is %d (expecting 4)\n", sizeof(long));
	printf("size of pid_t is %d (expecting 4)\n", *((char *)PIDSIZE));
	pid = sys_fork();
	if (pid > 0) {
		printf("parent: child=%ld\n", pid);
		printf("parent: waiting %ds\n", w = 3);
		sys_sleep(w);
		printf("parent: interrupting child\n");
		// SIGALRM is silently handled by the current vers. of xv65
		sys_kill(pid, XV65_SIGALRM);
		pid = sys_wait();
		printf("child %ld is done\n", pid);
	} else if (pid == 0) {
		pid = sys_getpid();
		printf("children (%ld): waiting %ds\n", pid, w = 1000);
		sys_sleep(w);
		printf("children: errno %d, remaining %ds - exiting\n", *(char *)REQERRNO, *(int *)REQDAT);
	}
}

void test_exec() {
	long pid;

	printf("starting child for uname...\n");
	pid = sys_fork();
	if (pid > 0) {
		pid = sys_wait();
		printf("...done\n");
	} else if (pid == 0) {
		char *args[3];

		args[0] = "uname";
		args[1] = "-a";
		args[2] = 0;
		sys_exec("/bin/uname", args);
	}
}

#define TEST_FILE "/tmp/cc65_xv65_test.dat"
#define TEST_DIR "/tmp/cc65_xv65_test_dir"

void test_write() {
	static const char *msg = "File created by xv65\n";
	int fd, n, len;

	fd = sys_open(TEST_FILE, XV65_O_WRONLY|XV65_O_CREAT);
	if (fd == -1) {
		printf("couldn't open " TEST_FILE " for writing\n");
		return;
	}
	len = strlen(msg);
	n = sys_write(fd, msg, len);
	printf("write returned %d (expected %d)\n", n, len);
	sys_close(fd);
}

void test_read() {
	char *buf;
	int fd, i, n, len = 1024;

	if ((buf = malloc(len)) == NULL) {
		printf("couldn't allocate buf (%d bytes)\n", len);
		return;
	}
	fd = sys_open(TEST_FILE, XV65_O_RDONLY);
	if (fd == -1) {
		printf("couldn't open " TEST_FILE " for reading\n");
		free(buf);
		return;
	}
	n = sys_read(fd, buf, len);
	printf("read returned %d\n", n);
	if (n > 0) {
		printf("content follows: \n");
		for (i = 0; i < n; i++)
			putchar(buf[i]);
	}
	sys_close(fd);
}

void test_filename() {
	int ret;

	ret = sys_chdir("/tmp");
	CHECK("chdir");
	ret = sys_mkdir(TEST_DIR);
	CHECK("mkdir " TEST_DIR);
	ret = sys_unlink(TEST_FILE);
	CHECK("unlink" TEST_FILE);
}

void test_pipe() {
	int p[2];
	char *argv[3];

	argv[0] = "wc";
	argv[1] = "-c";
	argv[2] = 0;

	sys_pipe(p);
	if (sys_fork() == 0) {
		sys_close(0);
		sys_dup(p[0]);
		sys_close(p[0]);
		sys_close(p[1]);
		sys_exec("/usr/bin/wc", argv);
	} else {
		sys_write(p[1], "hello world\n", 12);
		sys_close(p[0]);
		sys_close(p[1]);
	}
}

struct test {
	void (*f)(void);
	const char *id;
};

struct test test_cases[] = {
	{ test_exit, "exit" },
	{ test_fork, "fork" },
	{ test_kill, "kill" },
	{ test_exec, "exec" },
	{ test_write, "write" },
	{ test_read, "read" },
	{ test_filename, "filename" },
	{ test_pipe, "pipe" },
};

#define N_OF_TEST_CASES (sizeof(test_cases) / sizeof(struct test))

int main_with_args(int argc, char *argv[]) {
	int i = 0;
	if (argc != 2) {
		printf("usage: %s test_case\n", argv[0]);
		return 1;
	}
	for (i = 0; i < N_OF_TEST_CASES; i++) {
		if (!strcmp(argv[1], test_cases[i].id)) {
			test_cases[i].f();
			return 0;
		}
	}
	printf("%s: unknown test case, select one from:\n", argv[0]);
	for (i = 0; i < N_OF_TEST_CASES; i++)
		printf("%s\n", test_cases[i].id);
	return 1;
}

int main(void) {
	int i, len, ret, argc;
	char **argv;

	req_put(REQ_ARGC);
	req_end();
	argc = *(int *)REQDAT;
	argv = (char **)malloc(sizeof(char *) * (argc + 1));
	for (i = 0; i < argc; i++) {
		req_put(REQ_ARGV);
		req_put_value(2, 0); // addr - don't care
		req_put_value(2, 0); // len - not enough; will get right size
		req_put_value(4, i); // 4 bytes should be enough ;)
		req_end();
		len = *(int *)REQDAT;
		argv[i] = (char *)malloc(len);
		req_put(REQ_ARGV);
		req_put_value(2, (long)argv[i]);
		req_put_value(2, len);
		req_put_value(4, i);
		req_end();
//		printf("%d %s\n", i, argv[i]);
	}
	argv[i] = 0;
	ret = main_with_args(argc, argv);
	sys_exit(ret);
	return 0;
}
