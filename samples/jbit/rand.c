// Test C Runtime: rand()

#include <stdlib.h>
#include <conio.h>

int main()
{
	unsigned char x, y;

	_randomize();
	screensize(&x, &y);
	clrscr();
	while (wherey() < y)
		cputc(rand());
	cgetc();
}
