//...............................................
//...............................................
//Initiated on Sunday, the 21st of April, 2019
//      @ 09:42AM
//by the OS creator, Odey john Ebinyi.
//...............................................
//...............................................

/*The Global Descriptor Table (GDT) defines the global memory map. 
 * It defines what memory can be executed (The Code Descriptor),
 * and what area contains data (Data Descriptor). 
 */

/* A descriptor defines properties--i.e., it describes something. 
 * In the case of the GDT, it describes starting and base addresses, 
 * segment limits, and even virtual memory. 
 * The GDT usually has three descriptors--a Null descriptor (Contains all zeros),
 * a Code Descriptor, and a Data Descriptor.
 */ 

#ifndef __GDT_H
#define __GDT_H

//==================INCLUDED FILES=============================
#include <stdint.h>
#include <lib/config.h>


//................TYPEDEFS..........................
#define GDT_MAX_DESCRIPTORS  5

//===============GDT ACCESS BIT FLAGS===========================

// set access bit; used with virtual memory
#define I86_GDT_DESC_ACCESS			0x0001			//00000001

// descriptor is readable and writable. default: read only
#define I86_GDT_DESC_READWRITE			0x0002			//00000010

//set expansion direction bit
#define I86_GDT_DESC_EXPANSION			0x0004			//00000100

//executable code segment. Default: data segment
#define I86_GDT_DESC_EXEC_CODE			0x0008			//00001000

//set code or data descriptor. defult: system defined descriptor
#define I86_GDT_DESC_CODEDATA			0x0010			//00010000

//set dpl(descriptor privilege level) bits
//0 - for ring 0 (kernel space)
//11 - for ring 3 (user space)
#define I86_GDT_DESC_DPL			0x0060			//01100000

/*set "in memory" bit i.e it is used to indicate segment is
 *in memory.
 */
#define I86_GDT_DESC_MEMORY			0x0080			//10000000


//========================END====================================


//===============GDT DESCRIPTOR GRANULARITY BIT FLAGS=============

//masks out limitHi (High 4 bits of limit)
#define I86_GDT_GRAND_LIMITHI_MASK		0x0f			//00001111

// set os defined bit
#define I86_GDT_GRAND_OS			0x10			//00010000

// set if 32bit. default: 16 bit
#define I86_GDT_GRAND_32BIT			0x40			//01000000

// 4k granularity. default: none
#define I86_GDT_GRAND_4K			0x80			//10000000

//================================END==============================

//=================== C STRUCTURES --- GDT TABLE ===================
// This structure contains the value of one GDT entry.
// We use the attribute 'packed' to tell GCC not to change
// any of the alignment in the structure.
struct gdt_entry_struct
{
   uint16_t limit_low;           // The lower 16 bits of the limit.
   uint16_t base_low;            // The lower 16 bits of the base.
   uint8_t  base_middle;         // The next 8 bits of the base.
   uint8_t  access;              // Access flags, determine what ring this segment can be used in.
   uint8_t  granularity;
   uint8_t  base_high;           // The last 8 bits of the base.
} __attribute__((packed));

typedef struct gdt_entry_struct gdt_entry_t;

/*To tell the processor where to find our GDT, 
 * we have to give it the address of a special pointer structure
 */
struct gdt_ptr_struct
{
   uint16_t limit;               // size of the table
   uint32_t base_address;                // The address of the first gdt_entry_t struct.
}
 __attribute__((packed));
 
typedef struct gdt_ptr_struct gdt_ptr_t;

//========================END==========================================

//======================EXTERN FUNCTIONS===============================
_extern struct gdt_entry_struct *i86_get_gdt_descriptor(int);
_extern _void init_gdt();
//========================END==========================================
#endif
