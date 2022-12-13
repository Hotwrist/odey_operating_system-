//...............................................
//...............................................
//Initiated on Saturday, the 15th of June, 2019
//      @ 01:00PM
//by the creator, Odey john Ebinyi.
//...............................................
//Modified last: Saturday 15th of June, 2019 @ 01:00PM
//...............................................
//...............................................

//Paging.c ==> This C file contains the system paging functions
 

#ifndef __PAGING_H__
#define __PAGING_H__

#include <stdint.h>
#include <lib/const.h>
#include "phys_mmngr.h"


/*----------------PAGE TABLE ENTRY STRUCT-------------------*/
typedef struct  page_table_entry
{
    uint32_t present        : 1;
    uint32_t read_write     : 1;
    uint32_t user           : 1;
    uint32_t intel_resvd    : 2;
    uint32_t access         : 1;
    uint32_t dirty          : 1;
    uint32_t resvd          : 2;
    uint32_t available      : 3;
    uint32_t frame          : 20;
} page_table_entry_t;

/*---------------PAGE TABLE STRUCT---------------------------*/
typedef struct page_table
{
    page_table_entry_t pages[PAGES_PER_TABLE];
};


/*---------------PAGE DIRECTORY ENTRY STRUCT-----------------------*/
typedef struct page_dir_entry
{
    uint32_t present        : 1;
    uint32_t read_write     : 1;
    uint32_t user           : 1;
    uint32_t write_through  : 1;
    uint32_t cached         : 1;
    uint32_t access         : 1;
    uint32_t intel_resvd    : 1;
    uint32_t page_size      : 1;
    uint32_t global_page    : 1;
    uint32_t available      : 3;
    uint32_t frame          : 20;
}page_dir_entry_t;

/*----------------PAGE DIRECTORY STRUCT------------------------------*/
typedef struct _page_dir
{
    page_dir_entry_t tables[PAGES_PER_DIR];
} _page_dir_t;

#endif
