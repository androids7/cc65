// JBit-specific functions on the C64.

#include <c64.h>

void vsync(void)
{
	while (VIC.rasterline != 252)
		;
	while (VIC.rasterline == 252)
		;
}
