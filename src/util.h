/*
 * Copyright (c) 2010, Joshua Lackey
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *     *  Redistributions of source code must retain the above copyright
 *        notice, this list of conditions and the following disclaimer.
 *
 *     *  Redistributions in binary form must reproduce the above copyright
 *        notice, this list of conditions and the following disclaimer in the
 *        documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */
#ifndef _UTIL_H
#define _UTIL_H

// #undef	NPRINTF
#define	NPRINTF

// #undef	NFPRINTF
#define	NFPRINTF



// __func__ (C99) : The function where the printf is called
// __LINE__ : The line where the printf is called
// __FILE__ : The file where the printf is called

// Standard printf
#ifdef NPRINTF
    #define PRINTF(fmt, ...)
#else
    #define PRINTF(fmt, ...) printf(fmt, __VA_ARGS__)
#endif

#ifdef NFPRINTF
    #define FPRINTF(fd, fmt, ...)
#else
    #define FPRINTF(fd, fmt, ...) fprintf(fd, fmt, __VA_ARGS__)
#endif

extern void display_freq(float f);
extern void sort(float *b, unsigned int len);
extern double avg(float *b, unsigned int len, float *stddev);

#endif
