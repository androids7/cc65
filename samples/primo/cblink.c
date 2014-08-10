// cblink

#ifdef __PRIMO__
#define ARDUINO_MAIN
#define USE_SAMPLE_SYSCALLS
#include "sys.h"
#endif

#define led 13

void setup() {
	pinMode(led, OUTPUT);
}

void loop() {
	digitalWrite(led, HIGH);
	delay(1000);
	digitalWrite(led, LOW);
	delay(1000);
}
