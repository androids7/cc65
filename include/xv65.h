/*                                                                         */
/*  Copyright (C) 2012-2013  Emanuele Fornara                              */
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

/*  xv65.h                                                                 */

#ifndef _XV65_H
#define _XV65_H

#include <_xv65.h>

/*
 * The size of pid is assumed to be 4 bytes, so long is fine. To be
 * compatible with systems with pid == 8, you could treat pids as opaque
 * data buffers and always reserve 8 bytes for each of them. The actual
 * size used by xv65 (the amount you need to copy, check, etc... is
 * available in PIDSIZE).
*/
typedef long pid_t;

pid_t fork(void);
int __fastcall__ _exit(int status);
pid_t wait(void);
int __fastcall__ kill(pid_t pid, unsigned char sig);
pid_t getpid(void);

int __fastcall__ xv65_mkdir(const char *filename);

#define xv65_req_put(x) (*(unsigned char*)REQPUT = (x))
#define xv65_req_end() (*(unsigned char*)REQEND = 0)
#define xv65_req_res() (*(unsigned char*)REQRES)

void __fastcall__ xv65_req_put_word(unsigned int value);
void __fastcall__ xv65_req_put_string(const char *s);

#ifndef XV65_NO_REQ_ALIASES

#define req_put(x) xv65_req_put(x)
#define req_end() xv65_req_end()
#define req_res() xv65_req_res()
#define req_put_word xv65_req_put_word
#define req_put_string xv65_req_put_string

#endif

#endif
