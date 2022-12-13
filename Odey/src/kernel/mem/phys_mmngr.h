//...............................................
//...............................................
//Initiated on Sunday, the 28th of April, 2019
//      @ 08:43PM
//by the creator, Odey john Ebinyi.
//...............................................
//...............................................

//=====================================================
/*phys_mmngr.h ==> This files helps deal with managing 
 * the computer's physical memory. It is ODEY physical
 * memory manager file
 */
//======================================================


#ifndef __PHYS_MMNGR_H
#define __PHYS_MMNGR_H

//==============INCLUDED FILES==========================
#include <stdint.h>
#include <lib/multiboot.h>
#include <lib/config.h>
//===================END================================

//=================TYPEDEFS=============================
//physical address
typedef uint32_t physical_addr;
//virtual address
typedef uint32_t virtual_addr;

//defined in linker.ld: indicates start and end of kernel code 
_extern uint32_t _kernel_phys_start;
_extern uint32_t _kernel_phys_end;
//======================================================

//===============================EXTERN FUNCTIONS===============================

//initialize the physical memory manager
_extern _void phys_mem_init(uint64_t);
//==========================================================================


#endif
