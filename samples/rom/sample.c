#pragma code-name ("TSTCODE")
#pragma data-name ("TSTDATA")
#pragma rodata-name ("TSTRODAT")

struct s1_t {
	int a;
	char c;
};

extern void *tstsyms;
struct s1_t *s1 = (struct s1_t *)100;
int a, b, c;

int f(char *s, int a, char b) {
	s[0] = b;
	return a + b;
}

void main(void) {
	int i;

	a = 5;
	b = 6;
	c = 7000;
	for (i = 1; i < 300; i++) {
		a += f("", b, 1);
		b *= i;
		b -= i;
		c /= i; 
		s1[i].a = a;
		s1[i].c = (char)c;
	}
}
