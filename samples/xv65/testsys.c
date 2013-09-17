// testsys.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <xv65.h>
#include "sys.h"

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

void test_unlink() {
	sys_unlink(TEST_FILE);
}

void test_dirs() {
	sys_chdir("/tmp");
	sys_mkdir(TEST_DIR);
	sys_rmdir(TEST_DIR);
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
	{ test_unlink, "unlink" },
	{ test_dirs, "dirs" },
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

	*(char*)TRCLEVEL = 2;
	//*(char*)ERREXIT = 1;
	req_put(REQ_ARGC);
	req_end();
	argc = *(int *)REQDAT;
	argv = (char **)malloc(sizeof(char *) * (argc + 1));
	for (i = 0; i < argc; i++) {
		req_put(REQ_ARGV);
		req_put_word(0); // addr - don't care
		req_put_word(0); // len - not enough; will get right size
		req_put_word(i);
		req_end();
		len = *(int *)REQDAT;
		argv[i] = (char *)malloc(len);
		req_put(REQ_ARGV);
		req_put_word((unsigned)argv[i]);
		req_put_word(len);
		req_put_word(i);
		req_end();
	}
	argv[i] = 0;
	ret = main_with_args(argc, argv);
	sys_exit(ret);
	return 0;
}
