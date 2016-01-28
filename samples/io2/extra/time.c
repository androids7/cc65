// Test C Runtime: time() - On a real device the formatting is really slow.

#include <stdio.h>
#include <time.h>
#include <conio.h>

unsigned char cols, rows;
time_t t;
struct tm *tm;
char s[16];

void print_time()
{
	int n, i = 0;

	n = sprintf(s, "%ld", t);
	cputsxy(cols - n, i++, s);
	strftime(s, sizeof(s), "%F", tm);
	cputsxy(0, i++, s);
	strftime(s, sizeof(s), "%H:%M:%S", tm);
	cputsxy(0, i++, s);
	strftime(s, sizeof(s), "%A", tm);
	cputsxy(0, i++, s);
	strftime(s, sizeof(s), "%B", tm);
	cputsxy(0, i++, s);
}

int main(void)
{
	screensize(&cols, &rows);
	clrscr();
	cputsxy(0, 0, "T");
	while (!kbhit()) {
		// time(&t); doesn't work!
		t = time(0);
		tm = gmtime(&t); // UTC
		print_time();
		io2_vsync();
	}
	return 0;
}
