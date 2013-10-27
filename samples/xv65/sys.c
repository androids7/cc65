// sys.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "sys.h"

/*

These are just quick tests. A proper implementation should be written
in assembly, hence the non-standard sys_ prefix.

REQRES is a return code set at every request. REQERRNO is a "sticky"
code that remembers the last failed return code - it can be (re)set by
the program.

*/

sys_pid_t sys_fork(void) {
	req_put(REQ_FORK);
	req_end();
	if (req_res())
		return -1;
	return *(sys_pid_t *)REQDAT;
}

int __fastcall__ sys_exit(int status) {
	req_put(REQ_EXIT);
	req_put_word(status);
	req_end();
	return req_res() ? -1 : 0;
}

sys_pid_t sys_wait(void) {
	req_put(REQ_WAIT);
	req_end();
	if (req_res())
		return -1;
	return *(sys_pid_t *)REQDAT;
}

int __fastcall__ sys_kill(sys_pid_t pid, byte sig) {
	req_put(REQ_KILL);
	req_put(sig); // optional (15 - SIGTERM is the default)
	*(long *)REQDAT = pid;
	req_end();
	return req_res() ? -1 : 0;
}

sys_pid_t sys_getpid() {
	req_put(REQ_GETPID);
	req_end();
	return *(sys_pid_t *)REQDAT;
}

unsigned __fastcall__ sys_sleep(unsigned seconds) {
	req_put(REQ_SLEEP);
	/*
		Trailing ints can be sent using 0 to 4 bytes.
		Value is UNSIGNED and default to 0. Example:

		if (seconds == 0)
			req_put_word(seconds);
		else if (seconds > 255)
			req_put_word(seconds);
		else
			req_put_word(seconds);
	*/
	req_put_word(seconds);
	req_end();
	return req_res() ? *(unsigned *)REQDAT : 0;
}

int sys_execvp(const char *filename, char *argv[]) {
	static int i;

	req_put(REQ_EXEC);
	req_put_string(filename);
	for (i = 0; argv[i]; i++)
		req_put_string(argv[i]);
	req_end();
	return req_res() ? -1 : 0;
}

int __fastcall__ sys_fstat(int fd, struct sys_stat *buf) {
	req_put(REQ_FSTAT);
	req_put(fd);
	req_end();
	if (req_res())
		return -1;
	buf->type = *(unsigned char *)REQDAT;
	buf->size = ((unsigned long *)REQDAT2)[0];
	buf->size_hi = ((unsigned long *)REQDAT2)[1];
	return 0;
}

int sys_open(const char *filename, int flags, ...) {
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
	req_put_word((unsigned)buf);
	req_put_word(n);
	req_end();
	if (req_res())
		return -1;
	return *(int *)REQDAT;
}

int __fastcall__ sys_read(int fd, void *buf, int n) {
	return do_rdwr(fd, buf, n, REQ_READ);
}

int __fastcall__ sys_write(int fd, void *buf, int n) {
	return do_rdwr(fd, buf, n, REQ_WRITE);
}

int __fastcall__ sys_close(int fd) {
	req_put(REQ_CLOSE);
	req_put(fd);
	req_end();
	return req_res() ? -1 : 0;
}

int __fastcall__ sys_pipe(int *p) {
	req_put(REQ_PIPE);
	req_end();
	if (req_res())
		return -1;
	p[0] = *(int *)REQDAT;
	p[1] = *(int *)(REQDAT + 8);
	return 0;
}

int __fastcall__ sys_dup(int fd) {
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
	return req_res() ? -1 : 0;
}

int __fastcall__ sys_chdir(const char *filename) {
	return do_filename(filename, REQ_CHDIR);
}

int __fastcall__ sys_mkdir(const char *filename) {
	return do_filename(filename, REQ_MKDIR);
}

int __fastcall__ sys_unlink(const char *filename) {
	return do_filename(filename, REQ_UNLINK);
}

int __fastcall__ sys_rmdir(const char *filename) {
	return do_filename(filename, REQ_RMDIR);
}

unsigned long __fastcall__ sys_time(unsigned long *t) {
	req_put(REQ_TIME);
	req_end();
	if (t)
		*t = *(unsigned long *)REQDAT;
	return *(unsigned long *)REQDAT;
}

long __fastcall__ sys_lseek(int fd, long offset, int whence) {
	int w;
	switch (whence) {
	case SEEK_SET:
		w = XV65_SEEK_SET;
		break;
	case SEEK_CUR:
		w = XV65_SEEK_CUR;
		break;
	case SEEK_END:
		w = XV65_SEEK_END;
		break;
	default:
		return -1;
	}
	req_put(REQ_LSEEK);
	req_put(fd);
	req_put(w);
	req_put_word((unsigned)offset);
	req_end();
	if (req_res())
		return -1;
	return *(long *)REQDAT;
}

unsigned int sys_argc(void) {
	req_put(REQ_ARGC);
	req_end();
	return *(unsigned int *)REQDAT;
}

int __fastcall__ sys_argv(unsigned int i, char *buf, unsigned int *size) {
	req_put(REQ_ARGV);
	req_put_word((unsigned int)buf);
	req_put_word(*size);
	req_put_word(i);
	req_end();
	*size = *(unsigned int *)REQDAT;
	return req_res() ? -1 : 0;
}

int __fastcall__ sys_env(const char *name, char *buf, unsigned int *size) {
	req_put(REQ_ENV);
	req_put_word((unsigned int)buf);
	req_put_word(*size);
	req_put_string(name);
	req_end();
	*size = *(unsigned int *)REQDAT;
	return req_res() ? -1 : 0;
}
