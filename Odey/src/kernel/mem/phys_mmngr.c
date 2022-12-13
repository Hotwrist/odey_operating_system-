//****************************************************************************
//**
//**    phys_mmngr.c
//**		-Physical Memory Manager
//**
//****************************************************************************

//=================================================
//Description: A bit in memory represents a block
// and a group of bits represent blocks of memory!
//==================================================


//===============HEADER FILES=======================
#include "phys_mmngr.h"
#include <lib/multiboot.h>
#include <lib/error.h>
#include <lib/string.h>
#include <lib/const.h>
#include <lib/print_string.h>

//==================================================
struct mem_vars
{
    uint32_t max_blocks;
    uint32_t used_blocks;
    uint32_t free_blocks;
    uint32_t system_ram_size;
    uint32_t free_page_bitmap[PAGE_SIZE];
};

//===================================================

//--------------------------------------------------
struct mem_vars mem_vars_t;
struct mem_vars *mem_vars_ptr = &mem_vars_t;

uint32_t base = 0, max_size = 0;
typedef uint32_t physical_addr;
//--------------------------------------------------

//==================================================

//===================================================================================================
_void set_block(uint32_t);
_bool test_block_set(uint32_t);


uint32_t first_free_frame();
uint32_t first_free_frames(uint32_t);
uint32_t get_max_blocks();
_void phys_mem_init(uint64_t);
_void *alloc_block();
_void* alloc_blocks(uint32_t); 
//====================================================================================================

//==================================PUBLIC FUNCTIONS DEFINITIONS=======================================
_void set_block(uint32_t page_index)
{
    mem_vars_ptr->free_page_bitmap[page_index / PAGE_ALLOC_UNIT] |= (1 << (page_index % PAGE_ALLOC_UNIT));
}

_bool test_block_set(uint32_t bit) 
{
    return mem_vars_ptr->free_page_bitmap[bit / PAGE_ALLOC_UNIT] &  (1 << (bit % PAGE_ALLOC_UNIT));
}

uint32_t first_free_frame()
{
    for(size_t block = 0; block < (get_max_blocks() / PAGE_ALLOC_UNIT); block++)
    {
        if(mem_vars_ptr->free_page_bitmap[block] != FULL_ADDRESS_SPACE)
        {
            for(size_t free_bit = 0; free_bit < PAGE_ALLOC_UNIT; free_bit++)
            {
                uint32_t bit = (1 << free_bit);

                if(!(mem_vars_ptr->free_page_bitmap[block] & bit))
                {
                    return ((block * PAGE_ALLOC_UNIT) + bit);
                }
            }   // end of inner for-loop
        }
    }   // end of outer for-loop

    return -1;
}

uint32_t first_free_frames(uint32_t size)
{

}


uint32_t get_max_blocks()
{
    return (mem_vars_ptr->max_blocks);
}

_void phys_mem_init(uint64_t ram_size)
{
    //mem_vars_ptr->free_page_bitmap = (uint32_t*)&_kernel_phys_end;

    mem_vars_ptr->max_blocks = (ram_size * KILOBYTE_SIZE) / PAGE_SIZE;
    mem_vars_ptr->used_blocks = 0;
    mem_vars_ptr->system_ram_size = ((ram_size - PAGE_SIZE) / KILOBYTE_SIZE);
    
    mem_set(mem_vars_ptr->free_page_bitmap,0x0, PAGE_SIZE);
    
    print_fmt_string("RAM SIZE: %d\n", ram_size);
    print_fmt_string("USABLE RAM: %dMB\n", mem_vars_ptr->system_ram_size);
    print_fmt_string("MAX BLOCKS: %d\n\n", get_max_blocks());
}

_void *alloc_block()
{
    uint32_t frame_addr = first_free_frame();

    if(frame_addr == -1) return 0;

    set_block(frame_addr);

    physical_addr addr = (frame_addr * PAGE_SIZE);

    return (void*)addr;
}

_void *alloc_blocks(uint32_t size)
{
    
}











