// Show display info.

#include <stdio.h>
#include <conio.h>

int main(void)
{
	char s[16];
	int n;
	unsigned char flags;
	unsigned char alpha;

	req_put(REQ_DPYINFO);
	req_end();
	sprintf(s, "%dx%d",
		*(unsigned*)&IODAT(DPYINFO_WIDTH),
		*(unsigned*)&IODAT(DPYINFO_HEIGHT));
	cputsxy(0, 0, s);
	flags = IODAT(DPYINFO_FLAGS);
	n = sprintf(s, "%s %u+",
		flags & DPYINFO_FLAGS_ISCOLOR ? "COL" : "B/W",
		IODAT(DPYINFO_COLORDEPTH));
	cputsxy(0, 1, s);
	alpha = IODAT(DPYINFO_ALPHADEPTH);
	if (alpha > 0)
		sprintf(s, "%u", alpha);
	else
		sprintf(s, "?");
	cputsxy(n, 1, s);
	if (flags & DPYINFO_FLAGS_ISMIDP2)
		cputsxy(0, 2, "MIDP2");
	else
		cputsxy(0, 2, "MIDP1");
	cgetc();
	return 0;
}
