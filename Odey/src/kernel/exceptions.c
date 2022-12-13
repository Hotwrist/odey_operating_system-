#include "exceptions.h"
#include "k_panic.h"
#include <lib/error.h>

_extern int print_fmt_string(const _char*,...);
_extern _void print_string(const _char*);

//===============PUBLIC FUNCTIONS PROTOTYPES================================
_void divide_by_zero_fault_handler(registers_t *);
_void single_step_trap_handler(registers_t *);
_void nmi_trap_handler(registers_t *);
_void breakpoint_trap_handler(registers_t *);
_void overflow_trap_handler(registers_t *);
_void bounds_check_fault_handler(registers_t *);
_void invalid_opcode_fault_handler(registers_t *);
_void no_device_fault_handler(registers_t *);
_void double_fault_abort_handler(registers_t *);

_void coprocessor_segment_overrun_fault_handler(registers_t *);
_void invalid_tss_fault_handler(registers_t *);
_void no_segment_fault_handler(registers_t *);
_void stack_fault_handler(registers_t *);
_void general_protection_fault_handler(registers_t *);
//_void page_fault_handler(registers_t *);
//_void unassigned(registers_t *);
_void fpu_fault_handler(registers_t *);

_void alignment_check_fault_handler(registers_t *);
_void machine_check_abort_handler(registers_t *);
_void simd_fpu_fault_handler(registers_t *);
//===========================END============================================



//exception messages.
PRIVATE _char *exception_messages[] = 
{
    "Division By Zero",
    "Debug",
    "Non Maskable Interrupt",
    "Breakpoint",
    "Into Detected Overflow",
    "Out of Bounds",
    "Invalid Opcode",
    "No Coprocessor",
    
    "Double Fault",
    "Coprocessor Segment Overrun",
    "Bad TSS",
    "Segment Not Present",
    "Stack Fault",
    "General Protection Fault",
    "Page Fault",
    "Unknown Interrupt",
    
    "Coprocessor Fault",
    "Alignment Check",
    "Machine Check",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    
    "Timer",
    "Keyboard",
    "Cascade of Master\'s PIC with Slave\'s PIC",
    "Serial Port 2",
    "Serial Port 1",
    "AT: Parallel Port 2",
    "Diskette Drive",
    "Parallel Port 1",
    
    "CMOS Timer",
    "CGA Vertical Retrace",
    "Reserved",
    "Reserved",
    "PS/2: Auxiliary Device",
    "FPU",
    "Hard Disk Contoller",
    "Reserved"
};


//=================PUBLIC FUNCTIONS DEFINITIONS====================================================
_void divide_by_zero_fault_handler(registers_t *regs)
{
    kernel_panic(exception_messages[regs->interrupt_number]);
    
    print_fmt_string("\nInt Num: %d\naddress: [0x%x:0x%x]\nEFLAGS: [0x%x]\n", regs->interrupt_number, regs->cs, regs->eip, regs->eflags);
    
    for(;;);
}

_void single_step_trap_handler(registers_t *regs)
{
    kernel_panic(exception_messages[regs->interrupt_number]);
    
    print_fmt_string("\nInt Num: %d\naddress: [0x%x:0x%x]\nEFLAGS: [0x%x]\n",regs->interrupt_number, regs->cs, regs->eip, regs->eflags);
     
     for(;;);
}

_void nmi_trap_handler(registers_t *regs)
{
    kernel_panic(exception_messages[regs->interrupt_number]);
    
    print_fmt_string("\nInt Num: %d\naddress: [0x%x:0x%x]\nEFLAGS: [0x%x]\n", regs->interrupt_number, regs->cs, regs->eip, regs->eflags);
     
     for(;;);
}

_void breakpoint_trap_handler(registers_t *regs)
{
   kernel_panic(exception_messages[regs->interrupt_number]);
    
   print_fmt_string("\nInt Num: %d\naddress: [0x%x:0x%x]\nEFLAGS: [0x%x]\n", regs->interrupt_number, regs->cs, regs->eip, regs->eflags);
     
   for(;;);
}

_void overflow_trap_handler(registers_t *regs)
{
    kernel_panic(exception_messages[regs->interrupt_number]);
    
    print_fmt_string("\nInt Num: %d\naddress: [0x%x:0x%x]\nEFLAGS: [0x%x]\n", regs->interrupt_number, regs->cs, regs->eip, regs->eflags);
     
    for(;;);
}

_void bounds_check_fault_handler(registers_t *regs)
{
    kernel_panic(exception_messages[regs->interrupt_number]);
    
    print_fmt_string("\nInt Num: %d\naddress: [0x%x:0x%x]\nEFLAGS: [0x%x]\n", regs->interrupt_number, regs->cs, regs->eip, regs->eflags);
     
     for(;;);
}

_void invalid_opcode_fault_handler(registers_t *regs)
{
    kernel_panic(exception_messages[regs->interrupt_number]);
    
    print_fmt_string("\nInt Num: %d\naddress: [0x%x:0x%x]\nEFLAGS: [0x%x]\n", regs->interrupt_number, regs->cs, regs->eip, regs->eflags);
     
     for(;;);
}

_void no_device_fault_handler(registers_t *regs)
{
   kernel_panic(exception_messages[regs->interrupt_number]);
    
    print_fmt_string("\nInt Num: %d\naddress: [0x%x:0x%x]\nEFLAGS: [0x%x]\n", regs->interrupt_number, regs->cs, regs->eip, regs->eflags);
     
     for(;;);
}

_void double_fault_abort_handler(registers_t *regs)
{
    kernel_panic(exception_messages[regs->interrupt_number]);
    
    print_fmt_string("\nInt Num: %d\naddress: [0x%x:0x%x]\nEFLAGS: [0x%x]\n", regs->interrupt_number, regs->cs, regs->eip, regs->eflags);
     
     for(;;);
}

_void coprocessor_segment_overrun_fault_handler(registers_t *regs)
{
     kernel_panic(exception_messages[regs->interrupt_number]);
    
    print_fmt_string("\nInt Num: %d\naddress: [0x%x:0x%x]\nEFLAGS: [0x%x]\n", regs->interrupt_number, regs->cs, regs->eip, regs->eflags);
     
     for(;;);
}

_void invalid_tss_fault_handler(registers_t *regs)
{
    kernel_panic(exception_messages[regs->interrupt_number]);
    
    print_fmt_string("\nInt Num: %d\naddress: [0x%x:0x%x]\nEFLAGS: [0x%x]\n", regs->interrupt_number, regs->cs, regs->eip, regs->eflags);
     
     for(;;);
}

_void no_segment_fault_handler(registers_t *regs)
{
     kernel_panic(exception_messages[regs->interrupt_number]);
    
    print_fmt_string("\nInt Num: %d\naddress: [0x%x:0x%x]\nEFLAGS: [0x%x]\n", regs->interrupt_number, regs->cs, regs->eip, regs->eflags);
     
     for(;;);
}

_void stack_fault_handler(registers_t *regs)
{
     kernel_panic(exception_messages[regs->interrupt_number]);
    
    print_fmt_string("\nInt Num: %d\naddress: [0x%x:0x%x]\nEFLAGS: [0x%x]\n", regs->interrupt_number, regs->cs, regs->eip, regs->eflags);
     
     for(;;);
}

_void general_protection_fault_handler(registers_t *regs)
{
     kernel_panic(exception_messages[regs->interrupt_number]);
    
    print_fmt_string("\nInt Num: %d\naddress: [0x%x:0x%x]\nEFLAGS: [0x%x]\n", regs->interrupt_number, regs->cs, regs->eip, regs->eflags);
     
     for(;;);
}

_void page_fault_handler(registers_t *regs)
{
   //kernel_panic(exception_messages[regs->interrupt_number]);
    
   // print_fmt_string("\nInt Num: %d\naddress: [0x%x:0x%x]\nEFLAGS: [0x%x]\n", regs->interrupt_number, regs->cs, regs->eip, regs->eflags);
     
      // A page fault has occurred.
    // The faulting address is stored in the CR2 register.
    uint32_t faulting_address ;
    __asm__ __volatile__("mov %%cr2, %%eax" : "=a"(faulting_address));
    
    // The error code gives us details of what happened.
    int present   = !(regs->err_code & ERR_PRESENT); // Page not present
    int rw = (regs->err_code & ERR_READ_WRITE);           // Write operation?
    int user = (regs->err_code & ERR_USER);           // Processor was in user-mode?
    int reserved = (regs->err_code & ERR_RESERVED);     // Overwritten CPU-reserved bits of page entry?
    //int id = (regs->err_code & ERR_INST_FETCH);          // Caused by an instruction fetch?

    // Output an error message.
    print_string("Page fault! ( ");
    
    if (present) {print_string("present ");}
    if (rw) {print_string("read-only ");}
    if (user) {print_string("user-mode ");}
    if (reserved) {print_string("reserved ");}
    
    print_string(") at 0x");
    print_fmt_string("%x", faulting_address);
    print_string("\n");
    kernel_panic("Page fault");
   
     for(;;);
}

_void fpu_fault_handler(registers_t *regs)
{
     kernel_panic(exception_messages[regs->interrupt_number]);
    
    print_fmt_string("\nInt Num: %d\naddress: [0x%x:0x%x]\nEFLAGS: [0x%x]\n", regs->interrupt_number, regs->cs, regs->eip, regs->eflags);
     
     for(;;);
}

_void alignment_check_fault_handler(registers_t *regs)
{
     kernel_panic(exception_messages[regs->interrupt_number]);
    
    print_fmt_string("\nInt Num: %d\naddress: [0x%x:0x%x]\nEFLAGS: [0x%x]\n", regs->interrupt_number, regs->cs, regs->eip, regs->eflags);
     
     for(;;);
}

_void machine_check_abort_handler(registers_t *regs)
{
    kernel_panic(exception_messages[regs->interrupt_number]);
    
    print_fmt_string("\nInt Num: %d\naddress: [0x%x:0x%x]\nEFLAGS: [0x%x]\n", regs->interrupt_number, regs->cs, regs->eip, regs->eflags);
     
     for(;;);
}

_void simd_fpu_fault_handler(registers_t *regs)
{
    kernel_panic(exception_messages[regs->interrupt_number]);
    
    print_fmt_string("\nInt Num: %d\naddress: [0x%x:0x%x]\nEFLAGS: [0x%x]\n", regs->interrupt_number, regs->cs, regs->eip, regs->eflags);
     
     for(;;);
}
//=====================================END=============================================================
