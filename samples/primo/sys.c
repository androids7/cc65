// sys.c

#include "sys.h"

/*

These are just quick tests. A proper implementation should be written
in assembly, hence the non-standard sys_ prefix.

*/

void __fastcall__ sys_pinMode(uint8_t pin, uint8_t mode) {
	*(uint8_t *)DIGID = pin;
	*(uint8_t *)DIGWCFG = mode;
}

void __fastcall__ sys_digitalWrite(uint8_t pin, uint8_t value) {
	*(uint8_t *)DIGID = pin;
	*(uint8_t *)DIGVAL = value;
}

int __fastcall__ sys_digitalRead(uint8_t pin) {
	*(uint8_t *)DIGID = pin;
	return *(uint8_t *)DIGVAL;
}

int __fastcall__ sys_analogRead(uint8_t pin) {
	*(uint8_t *)ANLGLO = pin;
	return ((*(uint8_t *)ANLGHI) << 8) | *(uint8_t *)ANLGLO;
}

void __fastcall__ sys_analogWrite(uint8_t pin, uint8_t value) {
	*(uint8_t *)DIGID = pin;
	*(uint8_t *)DIGPWM = value;
}

void __fastcall__ sys_delay(uint16_t ms) {
	*(uint8_t *)REQPUT = REQ_DELAY;
	*(uint8_t *)REQPUT = (uint8_t)ms;
	*(uint8_t *)REQPUT = (uint8_t)(ms >> 8);
	*(uint8_t *)REQEND = 0;
}

uint32_t sys_millis() {
	*(uint8_t *)REQPUT = REQ_MILLIS;
	*(uint8_t *)REQEND = 0;
	return *(uint32_t *)REQDAT;
}
