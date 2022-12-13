//...............................................
//...............................................
//Initiated on Monday, the 22nd of April, 2019
//      @ 11:49AM
//by the OS creator, Odey john Ebinyi.
//...............................................
//...............................................

#ifndef __SYSTEM_H
#define __SYSTEM_H

#include <stdint.h>
#include "config.h"

// Register structs for bios service
typedef struct register16
{
    uint16_t di;
    uint16_t si;
    uint16_t bp;
    uint16_t sp;
    uint16_t bx;
    uint16_t dx;
    uint16_t cx;
    uint16_t ax;

    uint16_t ds;
    uint16_t es;
    uint16_t fs;
    uint16_t gs;
    uint16_t ss;
    uint16_t eflags;
}register16_t;

_extern uint8_t inport_byte(uint16_t);
_extern _void outport_byte(uint16_t, uint8_t);

#endif
