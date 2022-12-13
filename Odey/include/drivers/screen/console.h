//...............................................
//...............................................
//Initiated on Saturday, the 20th of April, 2019
//      @ 02:19PM
//by the creator, Odey john Ebinyi.
//...............................................
//...............................................

/*This file contains functions that will work on the screen
 * providing an interface to a user and much more!
 */

#ifndef __CONSOLE_H
#define __CONSOLE_H

//===================INCLUDED FILES================================
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <lib/vga.h>
#include <lib/config.h>
//=========================END=====================================

//=======================================================================
//initializes the terminal
extern void init_terminal();

//enables the terminal cursor
extern void enable_cursor(uint8_t, uint8_t);

//disables the terminal cursor
extern void disable_cursor();

//sets a character code attribute; background and foreground colors
extern void set_color(const enum VGA_COLORS, const enum VGA_COLORS);

//sets only the background color of a character code
extern void set_bg(const enum VGA_COLORS);

//sets only the foreground color of a character code
extern void set_fg(const enum VGA_COLORS);

//clears the whole screen
extern void clear_screen(uint8_t, uint8_t, bool);

//clears the boot up screen
extern void init_cls(uint8_t, uint8_t);

//updates screen cursor
extern void update_cursor(uint8_t, uint8_t);

//gets character position on the x-axis
extern int get_x();

//gets character position on the y-axis
extern int get_y();

extern void get_xy(unsigned*, unsigned*);

extern void goto_xy (unsigned, unsigned);

extern void bootup_squares();

extern void draw_console_borders();
//=========================================================================

#endif
