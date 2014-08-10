// digitalWrite.c
// Written by Emanuele Fornara

#include <primo.h>

void __fastcall__ digitalWrite(uint8_t pin, uint8_t value) {
	*(uint8_t *)DIGID = pin;
	*(uint8_t *)DIGVAL = value;
}
