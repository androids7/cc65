// pcd8544

// based on http://playground.arduino.cc/Code/PCD8544

#ifndef ARDUINO
#define ARDUINO_MAIN
#include <primo.h>
#endif

#define PIN_RESET 2
#define PIN_SCE   3
#define PIN_DC    4
#define PIN_SDIN  5
#define PIN_SCLK  6

#define LCD_C     LOW
#define LCD_D     HIGH

#define LCD_X     84
#define LCD_Y     48

static const uint8_t msg[] = {
	0x00,
	0x00,
	0x38, 0x44, 0x44, 0x44, 0x20, // c
	0x00,
	0x38, 0x44, 0x44, 0x44, 0x20, // c
	0x00,
	0x3c, 0x4a, 0x49, 0x49, 0x30, // 6
	0x00,
	0x27, 0x45, 0x45, 0x45, 0x39, // 5
	0x00,
	0x00,
};

void __fastcall__ lcd_write(uint8_t dc, uint8_t data) {
	digitalWrite(PIN_DC, dc);
	digitalWrite(PIN_SCE, LOW);
	shiftOut(PIN_SDIN, PIN_SCLK, MSBFIRST, data);
	digitalWrite(PIN_SCE, HIGH);
}

void lcd_clear() {
	int i;

	for (i = 0; i < LCD_X * LCD_Y / 8; i++)
		lcd_write(LCD_D, 0);
}

// LCD Vop, Temp coefficent and bias mode might need to be changed

void lcd_init() {
	pinMode(PIN_SCE, OUTPUT);
	pinMode(PIN_RESET, OUTPUT);
	pinMode(PIN_DC, OUTPUT);
	pinMode(PIN_SDIN, OUTPUT);
	pinMode(PIN_SCLK, OUTPUT);
	digitalWrite(PIN_RESET, LOW);
	delay(2);
	digitalWrite(PIN_RESET, HIGH);
	lcd_write(LCD_C, 0x21);  // LCD Extended Commands.
	lcd_write(LCD_C, 0xB1);  // Set LCD Vop (Contrast). 
	lcd_write(LCD_C, 0x04);  // Set Temp coefficent. //0x04
	// lcd_write(LCD_C, 0x14);  // LCD bias mode 1:48. //0x13
	lcd_write(LCD_C, 0x11);
	lcd_write(LCD_C, 0x0C);  // LCD in normal mode.
	lcd_write(LCD_C, 0x20);
	lcd_write(LCD_C, 0x0C);
}

void show_msg(char col) {
	char i;

	lcd_write(LCD_C, 0x80 | col);
	lcd_write(LCD_C, 0x40 | 2);
	for (i = 0; i < sizeof(msg); i++)
		lcd_write(LCD_D, msg[i]);
}

void setup() {
	lcd_init();
	lcd_clear();
}

void loop() {
	char col = 0;

	for (; col < LCD_X - sizeof(msg); col++)
		show_msg(col);
	for (; col > 0; col--)
		show_msg(col);
}
