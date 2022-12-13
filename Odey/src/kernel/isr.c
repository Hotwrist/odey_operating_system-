#include <descriptor_tables/idt.h>
#include <lib/print_string.h>
#include <lib/isr.h>

_extern _void print_string(const char*);

//this is found in exception.c
//===================EXTERN EXCEPTION HANDLERS=================
_extern _void divide_by_zero_fault_handler(registers_t *);
_extern _void single_step_trap_handler(registers_t *);
_extern _void nmi_trap_handler(registers_t *);
_extern _void breakpoint_trap_handler(registers_t *);
_extern _void overflow_trap_handler(registers_t *);
_extern _void bounds_check_fault_handler(registers_t *);
_extern _void invalid_opcode_fault_handler(registers_t *);
_extern _void no_device_fault_handler(registers_t *);
_extern _void double_fault_abort_handler(registers_t *);

_extern _void coprocessor_segment_overrun_fault_handler(registers_t *);
_extern _void invalid_tss_fault_handler(registers_t *);
_extern _void no_segment_fault_handler(registers_t *);
_extern _void stack_fault_handler(registers_t *);
_extern _void general_protection_fault_handler(registers_t *);
_extern _void page_fault_handler(registers_t *);
//_extern void unassigned_handler(registers_t *);
_extern _void fpu_fault_handler(registers_t *);

_extern _void alignment_check_fault_handler(registers_t *);
_extern _void machine_check_abort_handler(registers_t *);
_extern _void simd_fpu_fault_handler(registers_t *);

//========================END=================================

//==============PRIVATE FUNCTIONS PROTOTYPES============
_void exception_handler(registers_t*);
_void irq_handler(registers_t*);
//========================END==========================

//=============PUBLIC FUNCTIONS PROTOTYPES============
_void register_interrupt_handlers(uint16_t, exception_t);
_void uninstall_handler(uint16_t);
//=====================END=============================


//arrays of function pointers
exception_t interrupt_handlers[I86_MAX_INTERRUPTS];


//=====================PUBLIC UNCTIONS DEFINITIONS================
_void register_interrupt_handlers(uint16_t num, exception_t handler)
{
    if(num > I86_MAX_INTERRUPTS) return;
    
    interrupt_handlers[num] = handler;
}
//====================END=========================================

_void exception_handler(registers_t *regs)
{
     exception_t handler;

       switch(regs->interrupt_number)
        {
            case 0:
                register_interrupt_handlers((regs->interrupt_number), &divide_by_zero_fault_handler);
                
                handler = interrupt_handlers[regs->interrupt_number];
                handler(regs);
                break;
                
            case 1:
                register_interrupt_handlers((regs->interrupt_number), &single_step_trap_handler);
                
                handler = interrupt_handlers[regs->interrupt_number];
                handler(regs);
                break;
                
            case 2:
                register_interrupt_handlers((regs->interrupt_number), &nmi_trap_handler);
                
                handler = interrupt_handlers[regs->interrupt_number];
                handler(regs);
                break;
                
            case 3:
                register_interrupt_handlers((regs->interrupt_number), &breakpoint_trap_handler);
                
                handler = interrupt_handlers[regs->interrupt_number];
                handler(regs);
                break;
                
            case 4:
                register_interrupt_handlers((regs->interrupt_number), &overflow_trap_handler);
                
                handler = interrupt_handlers[regs->interrupt_number];
                handler(regs);
                break;
                
            case 5:
                register_interrupt_handlers((regs->interrupt_number), &bounds_check_fault_handler);
                
                handler = interrupt_handlers[regs->interrupt_number];
                handler(regs);
                break;
                
            case 6:
                register_interrupt_handlers((regs->interrupt_number), &invalid_opcode_fault_handler);
                
                handler = interrupt_handlers[regs->interrupt_number];
                handler(regs);
                break;
                
            case 7:
                register_interrupt_handlers((regs->interrupt_number), &no_device_fault_handler);
                
                handler = interrupt_handlers[regs->interrupt_number];
                handler(regs);
                break;
                
            case 8:
                register_interrupt_handlers((regs->interrupt_number), &double_fault_abort_handler);
                
                handler = interrupt_handlers[regs->interrupt_number];
                handler(regs);
                break;
                
            case 9:
                register_interrupt_handlers((regs->interrupt_number), &coprocessor_segment_overrun_fault_handler);
                
                handler = interrupt_handlers[regs->interrupt_number];
                handler(regs);
                break;
                
            case 10:
                register_interrupt_handlers((regs->interrupt_number), &invalid_tss_fault_handler);
                
                handler = interrupt_handlers[regs->interrupt_number];
                handler(regs);
                break;
                
            case 11:
                register_interrupt_handlers((regs->interrupt_number), &no_segment_fault_handler);
                
                handler = interrupt_handlers[regs->interrupt_number];
                handler(regs);
                break;
                
            case 12:
                register_interrupt_handlers((regs->interrupt_number), &stack_fault_handler);
                
                handler = interrupt_handlers[regs->interrupt_number];
                handler(regs);
                break;
                
            case 13:
                register_interrupt_handlers((regs->interrupt_number), &general_protection_fault_handler);
                
                handler = interrupt_handlers[regs->interrupt_number];
                handler(regs);
                break;
                
            case 14:
                register_interrupt_handlers((regs->interrupt_number), &page_fault_handler);
                
                handler = interrupt_handlers[regs->interrupt_number];
                handler(regs);
                break;
                
            case 16:
                register_interrupt_handlers((regs->interrupt_number), &fpu_fault_handler);
                
                handler = interrupt_handlers[regs->interrupt_number];
                handler(regs);
                break;
                
            case 17:
                register_interrupt_handlers((regs->interrupt_number), &alignment_check_fault_handler);
                
                handler = interrupt_handlers[regs->interrupt_number];
                handler(regs);
                break;
                
            case 18:
                register_interrupt_handlers((regs->interrupt_number), &machine_check_abort_handler);
                
                handler = interrupt_handlers[regs->interrupt_number];
                handler(regs);
                break;
                
            case 19:
                register_interrupt_handlers((regs->interrupt_number), &simd_fpu_fault_handler);
                
                handler = interrupt_handlers[regs->interrupt_number];
                handler(regs);
                break;
                
            default:
                print_string("WARNING: NO HANDLER FOR THE RAISED INTERRUPT ");
                break;
       }
}

_void irq_handler(registers_t *regs)
{
    exception_t handler;
    handler = interrupt_handlers[regs->interrupt_number];
    
    if(handler) handler(regs);
    
    
    //test if we need to send end-of-interrupt to second pic
    if(regs->interrupt_number >= 40)  i86_pic_send_command(I86_PIC_OCW2_MASK_EOI, 1);
    
    //always send end-of-interrupt to first pic
    i86_pic_send_command(I86_PIC_OCW2_MASK_EOI, 0);
}

_void uninstall_handler(uint16_t num)
{
    if(num > I86_MAX_INTERRUPTS) return;
    interrupt_handlers[num] = 0;
}
