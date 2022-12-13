/*#include "virt_memmngr.h"
#include <lib/const.h>


void vmm_switch_page_directory ( page_dir_t* pd )
{
    vmm_current_directory = pd;
    __asm volatile ( "mov %0, %%cr3" : : "r" ( pd ) );
}

void vmm_enable_paging ( void )
{
    uint32_t cr0;
    __asm volatile ( "mov %%cr0, %0" : "=r" ( cr0 ) );
    cr0 |= 0x80000000;
    __asm volatile ( "mov %0, %%cr0" : : "r" ( cr0 ) );
}

void vmm_disable_paging ( void )
{
    uint32_t cr0;
    __asm volatile ( "mov %%cr0, %0" : "=r" ( cr0 ) );
    cr0 &= ~0x80000000;
    __asm volatile ( "mov %0, %%cr0" : : "r" ( cr0 ) );
}

void vmm_enable_4mb_pages ( void )
{
    uint32_t cr4;
    __asm volatile ( "mov %%cr4, %0" : "=r" ( cr4 ) );
    cr4 |= 0x00000010;
    __asm volatile ( "mov %0, %%cr4" : : "r" ( cr4 ) );
}

void vmm_disable_4mb_pages ( void )
{
    uint32_t cr4;
    __asm volatile ( "mov %%cr4, %0" : "=r" ( cr4 ) );
    cr4 &= ~0x00000010;
    __asm volatile ( "mov %0, %%cr4" : : "r" ( cr4 ) );
}

page_dir_t* vmm_get_current_directory ( void )
{
    return vmm_current_directory;
}

void vmm_flush_tlb_entry ( uint32_t addr )
{
    /* FIXME: Do a cli and then a sti here? *
    __asm volatile ( "invlpg (%0)" : : "a" ( addr ) );
}*/
