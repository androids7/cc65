// Test C Runtime: cputc('\n')

#include <conio.h>

int main()
{
	unsigned char i, start, end, x, y;

	screensize(&x, &y);
	clrscr();
	start = 33;
	end = start + x + 1;
	while (wherey() < y) {
		for (i = start; i < end; i++)
			cputc(i);
		cputc('\n');
	}
	cgetc();
}
