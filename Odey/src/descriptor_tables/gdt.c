// gdt.c - Initialises the GDT

/*FUNCTION:   This function sets and Initialises the GDT, it then
 *           passes a parametre of type 'gdt_ptr_t' 
 *           to the assembly function 'gdt_install'; lgdt register
 *           uses this parametre to install or load the GDT into
 *           memory
*/

#include <descriptor_tables/gdt.h>


//external file defined in an assembly file(descriptor_tables.asm)
_extern _void gdt_install(uint32_t);

//=======================Variables and arrays=================================
gdt_entry_t gdt_entries[GDT_MAX_DESCRIPTORS];
gdt_ptr_t gdt_ptr;
//==========================END===============================================

//===========PRIVATE FUNCTIONS DECLARATION PROTOTYPES=========================
PRIVATE _void gdt_set_gate(uint32_t, uint32_t, uint32_t, uint8_t, uint8_t);
//==================================END========================================

//============PUBLIC FUNCTIONS DECLARATION PROTOTYPES==========================
_void init_gdt();
//==================================END========================================

//===========PRIVATE FUNCTIONS DEFINITIONS=====================================

PRIVATE _void gdt_set_gate(uint32_t index, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran)
{
    //this sets the base low, middle and high bits
    gdt_entries[index].base_low    =   (base & 0xFFFF);
    gdt_entries[index].base_middle =   ((base >> 16) & 0xFF);
    gdt_entries[index].base_high   =   ((base >> 24) & 0xFF);
    
    //this sets the limit and granularity
    gdt_entries[index].limit_low   =   (limit & 0xFFFF);
    gdt_entries[index].granularity =   ((limit >> 16) & 0x0F);
    
    gdt_entries[index].granularity |=  (gran & 0xF0);
    gdt_entries[index].access = access;
}

//==============================END=============================================

//=====================PUBLIC FUNCTIONS DEFINITIONS==============================
_void init_gdt()
{
    gdt_ptr.limit = ((sizeof(gdt_entry_t) * GDT_MAX_DESCRIPTORS) - 1);
    gdt_ptr.base_address  = (uint32_t)(&gdt_entries);
    
    //NULL SEGMENT DESCRIPTOR
    gdt_set_gate(0, 0, 0, 0, 0);
    
    //CODE SEGMENT DESCRIPTOR
    gdt_set_gate(1, 0, 0xFFFFFFFF, 
                 I86_GDT_DESC_READWRITE|I86_GDT_DESC_EXEC_CODE|I86_GDT_DESC_CODEDATA|I86_GDT_DESC_MEMORY/*0x9A*/, I86_GDT_GRAND_4K | I86_GDT_GRAND_32BIT | I86_GDT_GRAND_LIMITHI_MASK/*0xCF*/
                );
    
    //DATA SEGMENT DESCRIPTOR
    gdt_set_gate(2, 0, 0xFFFFFFFF, 
                I86_GDT_DESC_READWRITE|I86_GDT_DESC_CODEDATA|I86_GDT_DESC_MEMORY/*0x92*/,
                I86_GDT_GRAND_4K | I86_GDT_GRAND_32BIT | I86_GDT_GRAND_LIMITHI_MASK/*0xCF*/
                );
    
    //USER MODE CODE SEGMENT
    gdt_set_gate(3, 0, 0xFFFFFFFF, 
                 I86_GDT_DESC_READWRITE|I86_GDT_DESC_EXEC_CODE|I86_GDT_DESC_CODEDATA|I86_GDT_DESC_DPL|I86_GDT_DESC_MEMORY/*0xFA*/, 
                 I86_GDT_GRAND_4K | I86_GDT_GRAND_32BIT | I86_GDT_GRAND_LIMITHI_MASK
                );
    
    //USER MODE DATA SEGMENT
    gdt_set_gate(4, 0, 0xFFFFFFFF, 
                 I86_GDT_DESC_READWRITE|I86_GDT_DESC_CODEDATA|I86_GDT_DESC_DPL|I86_GDT_DESC_MEMORY/*0xF2*/, 
                 I86_GDT_GRAND_4K | I86_GDT_GRAND_32BIT | I86_GDT_GRAND_LIMITHI_MASK
                );
    
    gdt_install((uint32_t)&gdt_ptr);
}

//================================FUNCTIONS DECLARED EXTERN=========================================
struct gdt_entry_struct *i86_get_gdt_descriptor(int index)
{
    if(index > GDT_MAX_DESCRIPTORS)
        return (struct gdt_entry_struct*)0;
    return  &gdt_entries[index]; 
}
//===================================END=============================================================
