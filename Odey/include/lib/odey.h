//...............................................
//...............................................
//Initiated on Tuesday, the 18th of June, 2019
//      @ 10:58AM
//by the creator, Odey john Ebinyi.
//...............................................
//Modified last: Tuesday 18th of June, 2019 @ 10:58AM
//...............................................

#ifndef __ODEY_H__
#define __ODEY_H__

#include <lib/config.h>
#include <lib/print_string.h>
#include <drivers/screen/console.h>

//========================================
extern void os(); //displays OS details
extern void os_version(); //displays OS version
//========================================

//==========PUBLIC FUNCTIONS IMPLEMENTATION==========
void os()
{
    set_fg(MAGENTA);
    print_fmt_string("              ODEY OS Version               \n");
    set_fg(DARK_GREY);
    print_string("\n++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
    print_string("Hi, i am ODEY...you are welcome to my world!\n");
    print_string("I have quite a few command on the console, type 'help' \n");
    print_string("to see the available commands...wishing u a good tour\n");
    print_string("++++++++++++++++++++++++++++++++++++++++++++++++++++++\n\n");
}

void os_version()
{
    set_fg(GREEN);
    print_fmt_string("%s %d\n", "Odey Version", _VERSION);
}
//===================================================

#endif
