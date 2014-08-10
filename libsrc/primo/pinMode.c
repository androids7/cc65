// pinMode.c
// Written by Emanuele Fornara

#include <primo.h>

void __fastcall__ pinMode(uint8_t pin, uint8_t mode) {
	*(uint8_t *)DIGID = pin;
	*(uint8_t *)DIGWCFG = mode;
}
