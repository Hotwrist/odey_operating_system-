//...............................................
//...............................................
//Initiated on Monday, the 22nd of April, 2019
//      @ 12:28PM
//by the OS creator, Odey john Ebinyi.
//...............................................
//...............................................


/*The Interrupt Descriptor Table tells the processor where to find handlers for each interrupt. 
 * It is very similar to the GDT. It is just an array of entries, each one corresponding to an interrupt number.
 * There are 256 possible interrupt numbers(i.e 256 8 bytes descriptors), so 256 must be defined. 
 * If an interrupt occurs and there is no entry for it (even a NULL entry is fine), the processor will panic and reset.
 */ 

#ifndef __IDT_H
#define __IDT_H

//=======================INCLUDED FILES==================
#include <stdint.h>
#include <lib/config.h>
#include <drivers/chips/8259A.h>
//======================END==============================

//i86 defines a maximum of 256 interrupt handlers(0-255)
#define     I86_MAX_INTERRUPTS          256

//============-IDT ACCESS BIT FLAGS=======================
//! must be in the format 0D110, where D is descriptor type

//set if this is a 16 bit descriptor
#define     I86_IDT_DESC_BIT16		    0x06	//00000110

//set if this is a 32 bit descriptor
#define     I86_IDT_DESC_BIT32		    0x0E	//00001110

//descriptor privilege level(DPL) ; RING 1
#define     I86_IDT_DESC_RING1		    0x40	//01000000

//descriptor privilege level(DPL); RING 2
#define     I86_IDT_DESC_RING2		    0x20	//00100000

//descriptor privilege level(DPL); RING 3
#define     I86_IDT_DESC_RING3		    0x60	//01100000

//set if segment is present
#define     I86_IDT_DESC_PRESENT		0x80	//10000000

//========================END==============================


//==================C STRUCTURES : IDT table =====================

// A struct describing an interrupt gate.
struct idt_entry_struct
{
   uint16_t base_low;             // The lower 16 bits of the address to jump to when this interrupt fires.
   uint16_t segment_selector;     // Kernel segment selector -- code.
   uint8_t  reserved;             // This must always be zero.
   uint8_t  flags;              
   uint16_t base_high;             // The upper 16 bits of the address to jump to.
} __attribute__((packed));

typedef struct idt_entry_struct idt_entry_t;

// A struct describing a pointer to an array of interrupt handlers.
// This is in a format suitable for giving to 'lidt'.
struct idt_ptr_struct
{
   uint16_t limit;
   uint32_t base;                // The address of the first element in our idt_entry_t array.
} __attribute__((packed));

typedef struct idt_ptr_struct idt_ptr_t;

//=================EXTERN FUNCTIONS==========================
_extern _void init_idt();
_extern struct idt_entry_struct *i86_get_idt_descriptor(int);
//=========================END===============================

//==========================I86 EXCEPTIONS=====================================
// These extern directives let us access the addresses of our ASM ISR handlers.
_extern _void divide_by_zero_fault();
_extern _void single_step_trap();
_extern _void nmi_trap();
_extern _void breakpoint_trap();
_extern _void overflow_trap();
_extern _void bounds_check_fault();
_extern _void invalid_opcode_fault();
_extern _void no_device_fault();
_extern _void double_fault_abort();

_extern _void coprocessor_segment_overrun_fault();
_extern _void invalid_tss_fault();
_extern _void no_segment_fault();
_extern _void stack_fault();
_extern _void general_protection_fault();
_extern _void page_fault();
_extern _void unassigned();
_extern _void fpu_fault();

_extern _void alignment_check_fault();
_extern _void machine_check_abort();
_extern _void simd_fpu_fault();
_extern _void reserved20();
_extern _void reserved21();
_extern _void reserved22();
_extern _void reserved23();
_extern _void reserved24();
_extern _void reserved25();

_extern _void reserved26();
_extern _void reserved27();
_extern _void reserved28();
_extern _void reserved29();
_extern _void reserved30();
_extern _void reserved31();

//============================I86 IRQs==============================================
_extern _void irq_timer();
_extern _void irq_keyboard();
_extern _void irq_cascade();
_extern _void irq_serial_port2();
_extern _void irq_serial_port1();
_extern _void irq_AT_parallel_port2();
_extern _void irq_diskette_drive();
_extern _void irq_parallel_port1();

_extern _void irq_cmos_timer();
_extern _void irq_cga_vertical_retrace();
_extern _void irq_reserved10();
_extern _void irq_reserved11();
_extern _void irq_auxiliary();
_extern _void irq_fpu();
_extern _void irq_hdc();
_extern _void irq_reserved15();
//============================END====================================================

#endif
