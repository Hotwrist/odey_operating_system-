//...............................................
//...............................................
//Initiated on Monday, the 22nd of April, 2019
//      @ 01:53PM
//by the creator, Odey john Ebinyi.
//modified: Monday June 03rd 2019
//...............................................
//...............................................

#ifndef __STRING_H__
#define __STRING_H__

//==============INCLUDED FILES=====================
#include <stdint.h>
#include <stddef.h>
#include "ctype.h"
//=================END=============================

//============EXTERN FUNCTIONS=====================
extern void* mem_set(void *, int8_t, uint32_t);

extern uint32_t string_length(const char *);

extern char *str_cpy(char *, const char *);

extern char *stripper(char *);

extern int str_cmp(const char*, const char*);

extern void* mem_cpy(void *, const void *, uint32_t);

extern void itoa(unsigned, unsigned, char *);

extern void itoa_s(int, unsigned, char *);
//==================END============================

#endif
