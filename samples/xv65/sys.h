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

struct xv65_stat {
	unsigned char type;
	unsigned long size;
	unsigned long size_hi;
};

typedef unsigned char byte;

#define DEFINE_MINI_SYS \
int __fastcall__ write (int, const void* buf, unsigned count) { \
	const char *s = (const char *)buf; \
	unsigned i; \
	for (i = 0; i < count; i++) \
		putchar(s[i]); \
	return count; \
}

xv65_pid_t sys_fork(void);
int __fastcall__ sys_exit(int status);
xv65_pid_t sys_wait(void);
int __fastcall__ sys_kill(xv65_pid_t pid, byte sig);
xv65_pid_t sys_getpid(void);
unsigned __fastcall__ sys_sleep(unsigned seconds);
int sys_exec(const char *filename, char *argv[]);
int sys_fstat(int fd, struct xv65_stat *buf);
int sys_open(const char *filename, int flags);
int sys_read(int fd, void *buf, int n);
int sys_write(int fd, void *buf, int n);
int sys_close(int fd);
int sys_pipe(int *p);
int sys_dup(int fd);
int __fastcall__ sys_chdir(const char *filename);
int __fastcall__ sys_mkdir(const char *filename);
int __fastcall__ sys_unlink(const char *filename);

unsigned long sys_time();
int __fastcall__ sys_rmdir(const char *filename);

#ifdef USE_SAMPLE_SYSCALLS

#include <_xv65.h>

#define fork sys_fork
#define _exit sys_exit
#define wait sys_wait
#define kill sys_kill
#define getpid sys_getpid
#define sleep sys_sleep
#define chdir sys_chdir
#define xv65_mkdir sys_mkdir
#define unlink sys_unlink
#define rmdir sys_rmdir

#else

#include <unistd.h>
#include <xv65.h>

#endif
