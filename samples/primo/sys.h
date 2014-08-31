// sys.h

#include <stdint.h>

#include <primo.h>

void __fastcall__ sys_pinMode(uint8_t pin, uint8_t mode);
void __fastcall__ sys_digitalWrite(uint8_t pin, uint8_t value);
int __fastcall__ sys_digitalRead(uint8_t pin);
int __fastcall__ sys_analogRead(uint8_t pin);
void __fastcall__ sys_analogWrite(uint8_t pin, uint8_t value);
void __fastcall__ sys_delay(uint16_t pin);
uint32_t sys_millis();
uint8_t __fastcall__ sys_shiftIn(uint8_t dataPin, uint8_t clockPin, uint8_t bitOrder);
void __fastcall__ sys_shiftOut(uint8_t dataPin, uint8_t clockPin, uint8_t bitOrder, uint8_t value);

#ifdef USE_SAMPLE_SYSCALLS

#define pinMode sys_pinMode
#define digitalWrite sys_digitalWrite
#define digitalRead sys_digitalRead
#define analogRead sys_analogRead
#define analogWrite sys_analogWrite
#define delay sys_delay
#define millis sys_millis
#define shiftIn sys_shiftIn
#define shiftOut sys_shiftOut

#else

#endif
