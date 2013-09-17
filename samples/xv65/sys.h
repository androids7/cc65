// sys.h

#define putchar(x)	(*(unsigned char*)PUTCHAR = (x))
#define req_put(x)	(*(unsigned char*)REQPUT = (x))
#define req_end()	(*(unsigned char*)REQEND = 0)
#define req_res()	(*(unsigned char*)REQRES)

/*
The size of pid is assumed to be 4 bytes, so long is fine. To be
compatible with systems with pid == 8, you could treat pids as opaque
data buffers and always reserve 8 bytes for each of them. The actual
size used by xv65 (the amount you need to copy, check, etc... is
available in PIDSIZE).
*/
typedef long xv65_pid_t;

typedef unsigned char byte;

void req_put_word(unsigned int value);
void req_put_string(const char *s);

#define DEFINE_MINI_SYS \
int __fastcall__ write (int, const void* buf, unsigned count) { \
	const char *s = (const char *)buf; \
	unsigned i; \
	for (i = 0; i < count; i++) \
		putchar(s[i]); \
	return count; \
} \
void req_put_word(unsigned int value) { \
	unsigned char *p = (unsigned char *)&value; \
	req_put(p[0]); \
	req_put(p[1]); \
} \
void req_put_string(const char *s) { \
	char c; \
	while (c = *s++) \
		req_put(c); \
	req_put(0); \
}

xv65_pid_t sys_fork(void);
int sys_exit(int status);
xv65_pid_t sys_wait(void);
int sys_kill(xv65_pid_t pid, byte sig);
xv65_pid_t sys_getpid(void);
int sys_sleep(unsigned int sec);
int sys_exec(const char *filename, char *argv[]);
int sys_open(const char *filename, int flags);
int sys_read(int fd, void *buf, int n);
int sys_write(int fd, void *buf, int n);
int sys_close(int fd);
int sys_pipe(int *p);
int sys_dup(int fd);
int sys_chdir(const char *filename);
int sys_mkdir(const char *filename);
int sys_unlink(const char *filename);

int sys_rmdir(const char *filename);
