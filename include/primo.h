/*                                                                         */
/*  Copyright (C) 2014 Emanuele Fornara                                    */
/*  All rights reserved.                                                   */
/*                                                                         */
/*  Redistribution and use in source and binary forms, with or without     */
/*  modification, are permitted provided that the following conditions     */
/*  are met:                                                               */
/*   * Redistributions of source code must retain the above copyright      */
/*     notice, this list of conditions and the following disclaimer.       */
/*   * Redistributions in binary form must reproduce the above copyright   */
/*     notice, this list of conditions and the following disclaimer in     */
/*     the documentation and/or other materials provided with the          */
/*     distribution.                                                       */
/*                                                                         */
/*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS    */
/*  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT      */
/*  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS      */
/*  FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE         */
/*  COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,    */
/*  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,   */
/*  BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS  */
/*  OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED     */
/*  AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, */
/*  OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT     */
/*  OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF     */
/*  SUCH DAMAGE.                                                           */
/*                                                                         */

/*  primo.h                                                                */

#ifndef _PRIMO_H
#define _PRIMO_H

#include <stdint.h>

#include <_primo.h>
#include <_jbvm.h>

#define INPUT DIGWCFG_INPUT
#define OUTPUT DIGWCFG_OUTPUT
#define INPUT_PULLUP DIGWCFG_INPULLUP

#define HIGH DIGVAL_HIGH
#define LOW DIGVAL_LOW

#define LSBFIRST SHIFT_LSBFIRST
#define MSBFIRST SHIFT_MSBFIRST

void __fastcall__ pinMode(uint8_t pin, uint8_t mode);
void __fastcall__ digitalWrite(uint8_t pin, uint8_t value);
int __fastcall__ digitalRead(uint8_t pin);
int __fastcall__ analogRead(uint8_t pin);
void __fastcall__ analogWrite(uint8_t pin, uint8_t value);
void __fastcall__ delay(uint16_t pin);
uint32_t millis(void);
uint8_t __fastcall__ shiftIn(uint8_t dataPin, uint8_t clockPin, uint8_t bitOrder);
void __fastcall__ shiftOut(uint8_t dataPin, uint8_t clockPin, uint8_t bitOrder, uint8_t value);

#ifdef ARDUINO_MAIN
void setup(void);
void loop(void);
void main(void) {
	setup();
	while (1) {
		loop();
	}
}
#endif

#endif
