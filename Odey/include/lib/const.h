//...............................................
//...............................................
//Initiated on Friday, the 31st of May, 2019
//      @ 07:35PM
//by the creator, Odey john Ebinyi.
//...............................................
//...............................................

#ifndef __CONST_H
#define __CONST_H

//===============================================
#define 	FALSE               0
#define     TRUE                1
#define     EXE_SUCCESS         0
#define     EXE_FAILURE         1
#define     K_RET_CODE          EXE_SUCCESS       //indicates kernel return code
//===============================================

//==========================================
#define     DECIMAL_BASE            10
#define     HEXADECIMAL_BASE        16
#define     STACK_SIZE				4
#define     EMPTY_STACK				-1
//==========================================

//============CRTC(Cathode Ray Tube Computer) PROPERTIES============
#define     CRTC_INDEX_REGISTER      0x3D4
#define     CRTC_DATA_REGISTER       0x3D5
//======================END=========================================


//===================================MEMORY MANAGEMENT UNIT CONSTANTS========================================
#define 	KERNEL_MEMORY_ADDRESS		0xC0000000		//this is where the kernel is loaded to (virtual address)
#define		PAGES_PER_TABLE				1024
#define     PAGES_PER_DIR               1024
#define 	KILOBYTE_SIZE				1024
#define     MEGABYTE_SIZE				(1024 * KILOBYTE_SIZE)
#define     KHEAP_INITIAL_SIZE			(50 * MEGABYTE_SIZE)
#define     PAGE_SIZE                   4096
#define     FREE                        0
#define     NOT_FREE                    1
#define     PAGE_ALLOC_UNIT				32
#define     ADDRESS_SPACE_SIZE          4294967296ULL
#define     FULL_ADDRESS_SPACE			0xFFFFFFFF
/*
//Page table and page directory entry share similar constants except some minor differences
//===================================PAGE TABLE SESSION===================================================
#define     I86_PTE_PRESENT             1               //0000000000000000000000000000001
#define     I86_PTE_WRITABLE            2               //0000000000000000000000000000010
#define     I86_PTE_USER                4               //0000000000000000000000000000100
#define     I86_PTE_INTEL_RESVD         0x18            //0000000000000000000000000011000   
#define     I86_PTE_ACCESSED            0x20            //0000000000000000000000000100000
#define     I86_PTE_DIRTY               0x40            //0000000000000000000000001000000
#define     I86_PTE_RESVD               0x80            //0000000000000000000000110000000   
#define     I86_PTE_AVAILBL             0x200           //0000000000000000000111000000000     
#define     I86_PTE_FRAME               0x7FFFF000      //1111111111111111111000000000000   
//=========================================================================================================

//==================================PAGE DIRECTORY TABLE SESSION===========================================
#define     I86_PDE_PRESENT             1               //0000000000000000000000000000001
#define     I86_PDE_WRITABLE            2               //0000000000000000000000000000010
#define     I86_PDE_USER                4               //0000000000000000000000000000100
#define     I86_PDE_PWT                 8               //0000000000000000000000000001000
#define     I86_PDE_PCD                 0x10            //0000000000000000000000000010000
#define     I86_PDE_ACCESSED            0x20            //0000000000000000000000000100000
#define     I86_PDE_DIRTY               0x40            //0000000000000000000000001000000
#define     I86_PDE_4MB                 0x80            //0000000000000000000000010000000
#define     I86_PDE_GLOBAL              0x100           //0000000000000000000000100000000
#define     I86_PDE_AVAILABL            0x200           //0000000000000000000001000000000
#define     I86_PDE_FRAME               0x7FFFF000      //1111111111111111111000000000000
//==========================================================================================================
*/
//====================================================================================================================
#endif
