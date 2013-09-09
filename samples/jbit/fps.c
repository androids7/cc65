// Test FPS. 1-9: Custom FPS, 0: Default FPS, */#: Exit

/*
  The default FPS in JBit is 10.
  It might seem low, but on some low-end phones 10 it's actually too high
  and ghosting artifacts are clearly noticeable.
 */	

#include <conio.h>
#include <jbit.h>

unsigned char cols, rows;

void updatefps(int fps)
{
	gotoxy(0, 0);
	cprintf("%d FPS ", fps);
	IO[FRMFPS] = fps << 2;
}

unsigned char x = 0;
unsigned char right = 1;

void updateanim()
{
	cputcxy(x, 1, ' '); 
	if (right) {
		++x;
		if (x == cols) {
			x = cols - 2;
			right = 0;
		}
	} else {
		--x;
		if (x == 255) {
			x = 1;
			right = 1;
		}
	}
	cputcxy(x, 1, 'O'); 
	vsync();
}

int main()
{
	screensize(&cols, &rows);
	clrscr();
	updatefps(10);
	while (1) {
		if (kbhit()) {
			unsigned char c = cgetc();
			if (c == '0')
				updatefps(10);
			else if (c >= '1' && c <= '9')
				updatefps((c - '0') * 4);
			else
				return 0;
		}
		updateanim();
	}
}
