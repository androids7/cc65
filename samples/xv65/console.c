// console

#include <stdio.h>
#include <_xv65.h>

#define putchar(x)	(*(unsigned char*)PUTCHAR = (x))
#define esc(x)		(*(unsigned char*)CONESC = (x))
#define fps(x)		(*(unsigned char*)FRMFPS = (x) * 10)

typedef unsigned char byte;

int __fastcall__ write (int, const void* buf, unsigned count) {
	const char *s = (const char *)buf;
	unsigned i;
	for (i = 0; i < count; i++)
		putchar(s[i]);
	return count;
}

const char *count_msg = "count down to exit -> ";
const char *hello_msg = "Console Test";
const char *resize_msg = "resize me -> ";

int cols = -1, rows = -1;
char buf[128];

void skip(int n) {
	int i;

	for (i = 0; i < n; i++)
		putchar(' ');
}

int main(void) {
	int new_cols, new_rows;
	int i, n, tick = 0, counter = 50;

	fps(25); // max is around 25 fps
	esc(ESC_CLEAR);
	esc(ESC_HOME);
	while (counter > 0) {
		esc(ESC_HOME);
		new_cols = *(unsigned char *)CONCOLS;
		new_rows = *(unsigned char *)CONROWS;
		if (new_cols != cols || new_rows != rows) {
			cols = new_cols;
			rows = new_rows;
			esc(ESC_CLEAR);
			esc(ESC_HOME);
		}
		n = sprintf(buf, "%s%d", count_msg, counter);
		skip(cols - n);
		printf("%s", count_msg);
		esc(ESC_BG_RED);
		esc(ESC_FG_WHITE);
		printf("%d", counter);
		esc(ESC_NORMAL);
		tick++;
		if (tick == 10) {
			if (counter-- == 10)
				fps(10);
			tick = 0;
		}
		printf("\n\n");
		n = sprintf(buf, "%s", hello_msg);
		n = (cols - n) / 2;
		if (n < 0)
			n = 0;
		skip(n);
		esc(ESC_BG_BLUE);
		esc(ESC_FG_RED);
		printf("%s", hello_msg);
		esc(ESC_NORMAL);
		for (i = 3; i < rows; i++)
			putchar('\n');
		n = sprintf(buf, "%s", resize_msg);
		skip(cols - n - 1);
		printf("%s", resize_msg);
		*(char *)FRMDRAW = 0;
	}
	esc(ESC_CLEAR);
	esc(ESC_HOME);
	*(char *)FRMDRAW = 0;
	return 0;
}
