// shiftOut.c
// Written by Emanuele Fornara

#include <primo.h>

void __fastcall__ shiftOut(uint8_t dataPin, uint8_t clockPin, uint8_t bitOrder, uint8_t value) {
	*(uint8_t *)REQPUT = REQ_SHIFTOUT;
	*(uint8_t *)REQPUT = dataPin;
	*(uint8_t *)REQPUT = clockPin;
	*(uint8_t *)REQPUT = bitOrder;
	*(uint8_t *)REQPUT = value;
	*(uint8_t *)REQEND = 0;
}
