// delay.c
// Written by Emanuele Fornara

#include <primo.h>

void __fastcall__ delay(uint16_t ms) {
	*(uint8_t *)REQPUT = REQ_DELAY;
	*(uint8_t *)REQPUT = (uint8_t)ms;
	*(uint8_t *)REQPUT = (uint8_t)(ms >> 8);
	*(uint8_t *)REQEND = 0;
}
