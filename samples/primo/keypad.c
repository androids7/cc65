// keypad

/*

Prototyped on primo and tested on the Arduino IDE. To run on Arduino, create an
empty sketch and copy and paste this file as it is.

Needs a 3x4 matrix keypad (see defines below see/change the pinout)

 COL0  COL1  COL2 |
 -----------------+--------
   1     2     3  |  ROW0
   4     5     6  |  ROW1
   7     8     9  |  ROW2
   *     0     #  |  ROW3

 */

#ifdef ARDUINO

char buf[64];
#define TRACE_SETUP Serial.begin(9600);
#define TRACE_PRINT Serial.println(buf);

#else

#define ARDUINO_MAIN
#include <primo.h>

#define BUF_PTR 100
char *buf = (char *)BUF_PTR;
#define TRACE_SETUP
#define TRACE_PRINT *(char *)VMTRCLO = BUF_PTR;

#endif

#define PIN_ROW0_IN 2
#define PIN_ROW1_IN 3
#define PIN_ROW2_IN 4
#define PIN_ROW3_IN 5

#define PIN_COL0_OUT 6
#define PIN_COL1_OUT 7
#define PIN_COL2_OUT 8

const char *keys = "123456789*0#";

#define N_OF_COLS 3
#define N_OF_ROWS 4

uint8_t rows[] = {
	PIN_ROW0_IN,
	PIN_ROW1_IN,
	PIN_ROW2_IN,
	PIN_ROW3_IN,
};

uint8_t cols[] = {
	PIN_COL0_OUT,
	PIN_COL1_OUT,
	PIN_COL2_OUT,
};

uint16_t keypad_state;

void setup() {
	pinMode(PIN_ROW0_IN, INPUT_PULLUP);
	pinMode(PIN_ROW1_IN, INPUT_PULLUP);
	pinMode(PIN_ROW2_IN, INPUT_PULLUP);
	pinMode(PIN_ROW3_IN, INPUT_PULLUP);
	TRACE_SETUP
}

void scan() {
	uint8_t c, r, n;

	keypad_state = 0;
	for (c = 0; c < N_OF_COLS; c++) {
		pinMode(cols[c], OUTPUT);
		digitalWrite(cols[c], LOW);
		for (r = 0, n = 0; r < N_OF_ROWS; r++, n += 3) {
			if (digitalRead(rows[r]) == LOW)
				keypad_state |= (1 << (c + n));
		}
		digitalWrite(cols[c], HIGH);
		pinMode(cols[c], INPUT);
	}
}

void trace_state() {
	uint16_t mask = 1;
	uint8_t i;

	for (i = 0; i < 12; i++) {
		buf[i] = (keypad_state & mask) ? keys[i] : '-';
		mask <<= 1;
	}
	buf[i] = '\0';
	TRACE_PRINT
}

void loop() {
	scan();
	trace_state();
	delay(100);
}
