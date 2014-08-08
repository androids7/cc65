// vm

#include <primo.h>

const char *msg = "Trying to exaust virtual memory...";
uint8_t *p = (uint8_t *)0xC000;

void main(void) {
	int i;

	for (i = 0; i < 10; i++) {
		*(uint8_t *)VMTRCHI = (uint8_t)((uint16_t)msg >> 8);
		*(uint8_t *)VMTRCLO = (uint8_t)((uint16_t)msg & 0xff);
		*p = 0;
		p += 32;
	}
	*(uint8_t *)VMEXIT = 0;
}
