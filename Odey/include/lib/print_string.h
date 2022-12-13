//...............................................
//...............................................
//Initiated on Tuesday, the 18th of June, 2019
//      @ 08:53AM
//by the creator, Odey john Ebinyi.
//...............................................
//Modified last: Tuesday 18th of June, 2019 @ 08:53AM
//...............................................
//...............................................

#ifndef __PRINT_STRING_H__
#define __PRINT_STRING_H__

#include <lib/vga.h>
#include <lib/const.h>
#include <lib/string.h>
#include <stdarg.h>
#include <lib/config.h>

//================DIRECTIVE CONSTANTS==================
#define		 print_err(str) 		print_string(str);
//=====================================================

//=================EXTERN FUNCTIONS====================
//prints a single character
_extern void print_char(const _char);

//prints a null terminated string
_extern void print_string(const _char*);

//prints formatted strings
_extern int print_fmt_string(const _char *, ...);
//=====================================================


#endif