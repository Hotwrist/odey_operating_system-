//...............................................
//...............................................
//Initiated on Wednesday, the 10th of July, 2019
//      @ 04:06PM
//by the creator, Odey john Ebinyi.
//...............................................
//...............................................

/*------------------------------------------------------------------
 * This Stack data structure uses only the integer and char type for
 * now! 
 *
 *------------------------------------------------------------------
 */



#ifndef __STACK_H__
#define __STACK_H__


#include <stdint.h>
#include <lib/const.h>
#include <lib/config.h>


//================================================

// stack type, using C structures

struct _stack
{
    _void_star stack_arr[STACK_SIZE];
    uint32_t top;
};

_extern _void init_stack_struct();

_extern _void push(_void_star data);

_extern uint32_t peek();

_extern uint32_t pop();

_extern _void prepr_defines(_char);

_extern _bool is_stack_empty();

_extern _bool is_stack_full();

_extern _void show_stack_contents();

//===================================================

#endif