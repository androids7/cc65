/*

  cpubm.c

  CPU Benchmark.

  This benchmark is in 3 steps:
    1) 32-bit arithmetics
    2) Filling and sorting
    3) Date formatting

  It takes about 6 seconds (2 seconds per step) on a C64 (PAL)
  emulated by Vice.

 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>

#ifdef __C64__

extern void vsync(void);
static void resize(char, char) {}

#else

#include <jbit.h>
#define CLK_TCK 100

static void resize(char cols, char rows)
{
	IO[CONCOLS] = cols;
	IO[CONROWS] = rows;
}

#endif

#define DATA_SIZE	72

static signed int *data;

static void setup(void)
{
	resize(10, 4);
	clrscr();
	cputsxy(0, 0, "Running");
	cputsxy(0, 1, "0/3");
	vsync();
	data = (signed int *)malloc(sizeof(signed int) * DATA_SIZE);
}

static void update(unsigned char c)
{
	cputcxy(0, 1, c);
	vsync();
}

static unsigned long dt_a, dt_b, dt_c;

static void result(unsigned long dt)
{
	static unsigned long sec;
	static unsigned int sec100;

	sec = (dt * 100) / CLK_TCK;
	sec100 = sec % 100;
	sec /= 100;
	if (sec >= 100)
		cprintf("%lus", sec);
	else if (sec >= 10)
		cprintf("%lu.%us", sec, sec100 / 10);
	else
		cprintf("%lu.%02us", sec, sec100);
}

static void results()
{
	clrscr();
#if 1 /* easier to report */
	gotoxy(0, 0);
	cprintf("Elapsed:");
	gotoxy(0, 1);
	result(dt_a + dt_b + dt_c);
	gotoxy(0, 2);
	cprintf("Press '0'");
	gotoxy(0, 3);
	cprintf("to exit.");
#else
	gotoxy(0, 0);
	cprintf("1) ");
	result(dt_a);
	gotoxy(0, 1);
	cprintf("2) ");
	result(dt_b);
	gotoxy(0, 2);
	cprintf("3) ");
	result(dt_c);
	gotoxy(0, 3);
	cprintf("=) ");
	result(dt_a + dt_b + dt_c);
#endif
	cgetc();
}

static void test1(unsigned int n)
{
	static unsigned int i;
	static long a = 10, b;

	for (i = n; i != 0; i--)
		b = a * a + a;
}

static void test2a(void)
{
	static unsigned int i;

	for (i = 0; i < DATA_SIZE; i += 2) {
		data[i] = 30000 - i;
		data[i + 1] = i;
	}
}

static int test2f(const void *a, const void *b)
{
	return *(const signed int *)a - *(const signed int *)b;
}

static void test2(unsigned int n)
{
	static unsigned int i;

	for (i = n; i != 0; i--) {
		test2a();
		qsort(data, DATA_SIZE, sizeof(signed int), test2f);
	}
}

static void test3(unsigned int n)
{
	static unsigned int i;
	static time_t t = 1000000UL;
	static char s[32];
	static struct tm *tm;

	tm = gmtime(&t);
	for (i = n; i != 0; i--)
	        strftime(s, sizeof(s), "%F %H:%M:%S", tm);
}

int main(void)
{
	static clock_t t;

	setup();
	test1(10);
	test2(1);
	test3(1);

	update('1');
	t = clock();
	test1(870);
	dt_a = clock() - t;

	update('2');
	t = clock();
	test2(4);
	dt_b = clock() - t;

	update('3');
	t = clock();
	test3(50);
	dt_c = clock() - t;

	results();
}
