// sys.h

#include <stdint.h>

void __fastcall__ sys_pinMode(uint8_t pin, uint8_t mode);
void __fastcall__ sys_digitalWrite(uint8_t pin, uint8_t value);
int __fastcall__ sys_digitalRead(uint8_t pin);
int __fastcall__ sys_analogRead(uint8_t pin);
void __fastcall__ sys_analogWrite(uint8_t pin, uint8_t value);
void __fastcall__ sys_delay(uint16_t pin);
uint32_t sys_millis();

#ifdef USE_SAMPLE_SYSCALLS

#include <primo.h>

#define pinMode sys_pinMode
#define digitalWrite sys_digitalWrite
#define digitalRead sys_digitalRead
#define analogRead sys_analogRead
#define analogWrite sys_analogWrite
#define delay sys_delay
#define millis sys_millis

#else

#include <primo.h>

#endif

