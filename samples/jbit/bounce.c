// Bouncing ball.

#include <conio.h>

#ifdef __C64__

extern void vsync(void);

void setup_console()
{
}

#else

void setup_console()
{
	/*
	  In JBit the border is very thin or even non-existent
	  to maximize the amount of screen available.
	  Here we need it to stand out.
	*/
	if (IO[CONROWS] > 5) {
		IO[CONCOLS] -= 4;
		IO[CONROWS] -= 2;
	}
}

#endif

int main(void)
{
	unsigned char cols, rows;
	signed char x = 4, y = 0, dx = 1, dy = 1;

	setup_console();
	bordercolor(COLOR_RED);
	textcolor(COLOR_BLACK);
	bgcolor(COLOR_WHITE);
	screensize(&cols, &rows);
	clrscr();
	while (!kbhit()) {
		cputcxy(x, y, ' ');
		x += dx;
		if (x < 0 || x >= cols) {
			dx = -dx;
			x += dx;
			x += dx;
		}
		y += dy;
		if (y < 0 || y >= rows) {
			dy = -dy;
			y += dy;
			y += dy;
		}
		cputcxy(x, y, 'O');
		vsync();
	}
	return 0;
}
