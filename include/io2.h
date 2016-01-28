/*                                                                         */
/*  Copyright (C) 2016  Emanuele Fornara                              */
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

/*  io2.h                                                                 */

#ifndef _IO2_H
#define _IO2_H

#include <_io2.h>

#define IO(x) (*(unsigned char *)x)
#define IODAT(x) (*(((unsigned char *)REQDAT) + (x)))
#define IO_HI 0x02

void io2_vsync(void);

#define io2_req_put(x) (*(unsigned char*)REQPUT = (x))
#define io2_req_end() (*(unsigned char*)REQEND = 0)
#define io2_req_res() (*(unsigned char*)REQRES)

void __fastcall__ io2_req_put_word(unsigned int value);
void __fastcall__ io2_req_put_string(const char *s);

#ifndef IO2_NO_REQ_ALIASES

#define req_put(x) io2_req_put(x)
#define req_end() io2_req_end()
#define req_res() io2_req_res()
#define req_put_word io2_req_put_word
#define req_put_string io2_req_put_string

#endif

#endif
