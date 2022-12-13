//...............................................
//...............................................
//Initiated on Tuesday, the 07th of May, 2019
//      @ 09:09PM
//by the OS creator, Odey john Ebinyi.
//...............................................
//...............................................

/*terminal.h ==> This header file contains the interface of ODEY's
 * console/terminal operations for a user
 */

#ifndef __TERMINAL_H
#define __TERMINAL_H

#define TERMINAL_MODE

//=============INCLUDED FILES=============
#include <drivers/keyboard/keyboard.h>
#include <drivers/chips/8253.h>
#include <lib/string.h>
#include <lib/config.h>
#include "console.h"
//========================================

//sets max numer of acceptable command characters
#define     MAX_TTY_CMD_CHARS       150

//=========EXTERN FUNCTIONS=======================================
extern char get_ch(); //gets last keyboard key pressed.

extern void cmds(); //displays lists of terminal commands.

extern void run();  //run the terminal/console

extern void start();  //starts the boot up screen

extern bool clear_tty(); //clear the terminal?
//==============END=================================================
#endif
