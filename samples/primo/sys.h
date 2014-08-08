// sys.h

#include <stdint.h>

void __fastcall__ sys_pinMode(uint8_t pin, uint8_t mode);
void __fastcall__ sys_digitalWrite(uint8_t pin, uint8_t value);
int __fastcall__ sys_digitalRead(uint8_t pin);
int __fastcall__ sys_analogRead(uint8_t pin);
void __fastcall__ sys_analogReference(uint8_t mode);
void __fastcall__ sys_analogWrite(uint8_t pin, uint8_t value);

#ifdef USE_SAMPLE_SYSCALLS

#include <primo.h>

#define pinMode sys_pinMode
#define digitalWrite sys_digitalWrite
#define digitalRead sys_digitalRead
#define analogRead sys_analogRead
#define analogReference sys_analogReference
#define analogWrite sys_analogWrite

#else

#include <primo.h>

#endif

