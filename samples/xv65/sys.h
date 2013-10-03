// sys.h

/*
The size of pid is assumed to be 4 bytes, so long is fine. To be
compatible with systems with pid == 8, you could treat pids as opaque
data buffers and always reserve 8 bytes for each of them. The actual
size used by xv65 (the amount you need to copy, check, etc... is
available in PIDSIZE).
*/
typedef long sys_pid_t;

struct sys_stat {
	unsigned char type;
	unsigned long size;
	unsigned long size_hi;
};

typedef unsigned char byte;

sys_pid_t sys_fork(void);
int __fastcall__ sys_exit(int status);
sys_pid_t sys_wait(void);
int __fastcall__ sys_kill(sys_pid_t pid, byte sig);
sys_pid_t sys_getpid(void);
unsigned __fastcall__ sys_sleep(unsigned seconds);
int sys_execvp(const char *filename, char *argv[]);
int __fastcall__ sys_fstat(int fd, struct sys_stat *buf);
int sys_open(const char *filename, int flags, ...);
int __fastcall__ sys_read(int fd, void *buf, int n);
int __fastcall__ sys_write(int fd, void *buf, int n);
int __fastcall__ sys_close(int fd);
int __fastcall__ sys_pipe(int *p);
int __fastcall__ sys_dup(int fd);
int __fastcall__ sys_chdir(const char *filename);
int __fastcall__ sys_mkdir(const char *filename);
int __fastcall__ sys_unlink(const char *filename);

unsigned long __fastcall__ sys_time(unsigned long *t);
int __fastcall__ sys_rmdir(const char *filename);

unsigned int sys_argc(void);
int __fastcall__ sys_argv(unsigned int i, char *buf, unsigned int *size);
int __fastcall__ sys_env(const char *name, char *buf, unsigned int *size);

#ifdef USE_SAMPLE_SYSCALLS

#include <_xv65.h>

#define stat sys_stat

#define fork sys_fork
#define _exit sys_exit
#define wait sys_wait
#define kill sys_kill
#define getpid sys_getpid
#define sleep sys_sleep
#define execvp sys_execvp
#define fstat sys_fstat
#define open sys_open
#define read sys_read
#define write sys_write
#define close sys_close
#define pipe sys_pipe
#define dup sys_dup
#define chdir sys_chdir
#define xv65_mkdir sys_mkdir
#define unlink sys_unlink
#define time sys_time
#define rmdir sys_rmdir
#define xv65_argc sys_argc
#define xv65_argv sys_argv
#define xv65_env sys_env

#else

#include <time.h>
#include <unistd.h>
#include <fcntl.h>
#include <xv65.h>

#endif
