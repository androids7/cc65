// shiftIn.c
// Written by Emanuele Fornara

#include <primo.h>

uint8_t __fastcall__ shiftIn(uint8_t dataPin, uint8_t clockPin, uint8_t bitOrder) {
	*(uint8_t *)REQPUT = REQ_SHIFTIN;
	*(uint8_t *)REQPUT = dataPin;
	*(uint8_t *)REQPUT = clockPin;
	*(uint8_t *)REQPUT = bitOrder;
	*(uint8_t *)REQEND = 0;
	return *(uint8_t *)REQDAT;
}
