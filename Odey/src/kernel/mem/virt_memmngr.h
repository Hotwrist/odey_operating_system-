#ifndef __VIRTUAL_MEMORY_MANAGER_H
#define __VIRTUAL_MEMORY_MANAGER_H


#include "paging.h"
#include <lib/string.h>
#include <lib/print_string.h>
#include "phys_mmngr.h"

//============================================================================================
#define      PAGE_DIR_INDEX(vaddr)        (((uint32_t)vaddr) >> 22)
#define      PAGE_TABLE_INDEX(vaddr)      ((((uint32_t)vaddr) >>12) & 0x3ff)
#define      PAGE_FRAME_INDEX(vaddr)      (((uint32_t)vaddr) & 0xfff)

// Alignment related macro
#define      IS_ALIGN(addr)                ((((uint32_t)(addr)) | 0xFFFFF000) == 0)
#define      PAGE_ALIGN(addr)              ((((uint32_t)(addr)) & 0xFFFFF000) + 0x1000)

// Paging register manipulation macro
#define      SET_PGBIT(cr0)              (cr0 = cr0 | 0x80000000)
#define      CLEAR_PSEBIT(cr4)           (cr4 = cr4 & 0xffffffef)

#define      PAGE_OFFSET_BITS        12
#define      KERNEL_PAGE_TABLE_NUMBER   768
//==============================================================================================



#endif
