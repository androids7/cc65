// analogRead.c
// Written by Emanuele Fornara

#include <primo.h>

int __fastcall__ analogRead(uint8_t pin) {
	*(uint8_t *)ANLGLO = pin;
	return ((*(uint8_t *)ANLGHI) << 8) | *(uint8_t *)ANLGLO;
}
