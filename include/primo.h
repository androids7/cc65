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
