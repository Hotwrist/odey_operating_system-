//...............................................
//...............................................
//Initiated on Sunday, the 21st of April, 2019
//      @ 11:15AM
//by the creator, Odey john Ebinyi.
//...............................................
//Modified last: Tuesday 2ND of July, 2019 @ 05:58PM
//...............................................
//...............................................


#include <lib/isr.h>
#include <lib/const.h>
#include <lib/config.h>
#include <lib/multiboot.h>
#include <lib/print_string.h>
#include <descriptor_tables/gdt.h>
#include <descriptor_tables/idt.h>
#include <drivers/chips/8253.h>
#include <drivers/screen/terminal.h>
#include <data_structures/stack.h>
#include "mem/phys_mmngr.h"
#include "mem/virt_memmngr.h"
#include "mem/paging.h"
#include "k_panic.h"


/*****************************************************************************************/
/*****************************************************************************************/

/*Check if the compiler thinks you are targeting the wrong operating system.*/ 
#if defined(__linux__)
    #error "You are not using a cross-compiler, odey will certainly run into trouble!!"
#endif
 
/*This will only work for the 32-bit ix86 targets.*/ 
#if !defined(__i386__)
    #error "Odey needs to be compiled with an ix86-elf compiler!!"
#endif

/*****************************************************************************************/
/*****************************************************************************************/

_extern _void __lock_int();
_extern _void __unlock_int();

//===============PRIVATE FUNCTIONS PROTOTYPES=================
//PRIVATE _void system_init(multiboot_info_t *);
PRIVATE _void startup_image(); 
//=====================END===================================
//----------------------VARIABLE SECTION---------------------------

//===============================================================

//***************************************************************
//---------------------THE GATEWAY---------------------------------

// entry point
_void __odey(uint32_t magic, multiboot_info_t *boot_info)
{        
    init_terminal();
    set_color(BLACK, WHITE);
    clear_screen(0,0,true);
    set_color(BLACK, GREEN);
    print_string("Making Changes");
    //system_init(boot_info);
    //__unlock_int();

    //set_fg(RED);
    //print_string("Welcome Boss!!");

    //kybrd_install();
    
    //startup_image();
}

//****************************************************************
//================================================================


//==============PUBLIC FUNCTIONS DEFINITIONS=================
_void system_init(multiboot_info_t *boot_info)
{
    __lock_int();
    init_gdt(); 
    init_idt();

    set_fg(GREEN);
    print_string("\nInitializing physical memory manager...\n");
    //phys_mem_init(boot_info->mem_upper);
    

    set_fg(WHITE);
    //print_string("\nInitializing PIT...\n");
    i86_pit_initialize ();
    i86_pit_start_counter (100,I86_PIT_OCW_SELECT_COUNTER_COUNTER0, I86_PIT_OCW_OPERATING_MODE_SQUARE_WAVE_GENERATOR);
    
    //enables system interrupts
    __unlock_int();
    
    //timer_wait(100);

    //print_string("Initializing system\'s Keyboard...\n");
    //kybrd_install(); 

    //timer_wait(200);
}

_void startup_image()
{
    run();
}

//========================END================================s
