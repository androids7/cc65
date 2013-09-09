// Ciao in C.

#include <conio.h>

int main()
{
	unsigned char cols, rows;

	screensize(&cols, &rows);
	clrscr();
	cputsxy((cols - 4) >> 1, (rows - 1) >> 1, "CIAO");
	cgetc();
}
