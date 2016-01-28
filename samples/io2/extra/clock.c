// Test C Runtime: clock()

#include <stdio.h>
#include <time.h>
#include <conio.h>

int main(void)
{
	unsigned char cols, rows;
	clock_t t;
	char s[16];
	int n;

	screensize(&cols, &rows);
	clrscr();
	cputsxy(0, 0, "T");
	while (!kbhit()) {
		t = clock();
		n = sprintf(s, "%ld", t);
		cputsxy(cols - n, 0, s);
		io2_vsync();
	}
	return 0;
}
