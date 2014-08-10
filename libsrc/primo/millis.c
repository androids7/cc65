// millis.c
// Written by Emanuele Fornara

#include <primo.h>

uint32_t millis() {
	*(uint8_t *)REQPUT = REQ_MILLIS;
	*(uint8_t *)REQEND = 0;
	return *(uint32_t *)REQDAT;
}
