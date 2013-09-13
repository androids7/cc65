// scratchpad

#include <stdio.h>
#include <xv65.h>

#define putchar(x)	(*(unsigned char*)PUTCHAR = (x))
#define req_put(x)	(*(unsigned char*)REQPUT = (x))
#define req_end()	(*(unsigned char*)REQEND = 0)
#define req_res()	(*(unsigned char*)REQRES)

typedef unsigned char byte;

int __fastcall__ write (int, const void* buf, unsigned count) {
	const char *s = (const char *)buf;
	unsigned i;
	for (i = 0; i < count; i++)
		putchar(s[i]);
	return count;
}

void req_put_value(int size, long value) {
	int i;
	char *buf = (char *)&value;
	for (i = 0; i < size; i++)
		req_put(buf[i]);
}

void req_put_string(const char *s) {
	char c;
	while (c = *s++)
		req_put(c);
	req_put(0);
}

void dump_mem(byte *p, unsigned int size) {
	int i;

	for (i = 0; i < size; i++)
		printf("%03d%s", p[i], (i & 0xf) == 0xf ? "\n" : " ");
	if (i & 0xf)
		printf("\n");
}

void main(void) {
}
