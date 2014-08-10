// digitalRead.c
// Written by Emanuele Fornara

#include <primo.h>

int __fastcall__ digitalRead(uint8_t pin) {
	*(uint8_t *)DIGID = pin;
	return *(uint8_t *)DIGVAL;
}
