// cblink

#ifndef ARDUINO
#define ARDUINO_MAIN
#include <primo.h>
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
