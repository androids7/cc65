// io2-specific functions on the C64.

#include <c64.h>

void io2_vsync(void)
{
	while (VIC.rasterline != 252)
		;
	while (VIC.rasterline == 252)
		;
}
