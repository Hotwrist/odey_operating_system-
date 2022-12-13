//...............................................
//...............................................
//Initiated on Monday, the 22nd of April, 2019
//      @ 01:41PM
//by the  creator, Odey john Ebinyi.
//...............................................
//...............................................

#ifndef __ISR_H
#define __ISR_H


//================INCLUDED FILES==================
#include "stdint.h"
#include "system.h"
#include "lib/glo.h"
//=====================END========================

//=========-----------IRQs NUMBERS-------------================
#define     IRQ0    32
#define     IRQ1    33
#define     IRQ2    34
#define     IRQ3    35
#define     IRQ4    36
#define     IRQ5    37
#define     IRQ6    38
#define     IRQ7    39

#define     IRQ8    40
#define     IRQ9    41
#define     IRQ10   42
#define     IRQ11   43
#define     IRQ12   44
#define     IRQ13   45
#define     IRQ14   46
#define     IRQ15   47
//=======================================================

//Register structs for interrupt/exception
/*this struct declaration contains registers, error codes,
 * interrupt numbers pushed onto the stack during an 
 * interrupt handling process by the processor
 */
typedef struct registers
{
   uint32_t gs, fs, es, ds;                  // Data segment selector
   uint32_t edi, esi, ebp, useless_esp, ebx, edx, ecx, eax; // Pushed by pusha.
   uint32_t interrupt_number, err_code;    // Interrupt number and error code (if applicable)
   uint32_t eip, cs, eflags, /*useresp*/esp, ss; // Pushed by the processor automatically.
}registers_t;
//=====================================================================================================


typedef void (*exception_t)(registers_t *);

extern void register_interrupt_handlers(uint16_t, exception_t);
extern void uninstall_handler(uint16_t);

#endif
