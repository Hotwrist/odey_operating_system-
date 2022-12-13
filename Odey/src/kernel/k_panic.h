//...............................................
//...............................................
//Initiated on Sunday, the 28th of April, 2019
//      @ 07:46AM
//by the OS creator, Odey john Ebinyi.
//...............................................
//...............................................

#ifndef __K_PANIC_H
#define __K_PANIC_H

#include <drivers/screen/console.h>
#include <stdarg.h>
#include <lib/string.h>


//===========EXTERN FUNCTIONS==========
extern int kernel_panic(const char *, ...);
//================END==================

#endif
