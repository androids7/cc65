// analogWrite.c
// Written by Emanuele Fornara

#include <primo.h>

void __fastcall__ analogWrite(uint8_t pin, uint8_t value) {
	*(uint8_t *)DIGID = pin;
	*(uint8_t *)DIGPWM = value;
}
