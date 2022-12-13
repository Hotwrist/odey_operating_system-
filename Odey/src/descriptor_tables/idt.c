#include <descriptor_tables/idt.h>
#include <lib/string.h>

//=======TYPEDEFS=================
#define PIC_BASE_ADDRESS_0  0x20
#define PIC_BASE_ADDRESS_1  0x28
//=================================

//external file defined in an assembly file(descriptor_tables.asm)
_extern _void idt_install(uint32_t);

//=======================Variables and arrays=================================
idt_entry_t idt_entries[I86_MAX_INTERRUPTS];
idt_ptr_t idt_ptr;
//==========================END===============================================

//==============PRIVATE FUNCTIONS DECLARATION PROTOTYPES======================
PRIVATE _void idt_set_gate(uint8_t, uint32_t, uint16_t, uint8_t);
//==================================END========================================

//============PUBLIC FUNCTIONS DECLARATION PROTOTYPES==========================
_void init_idt();
struct idt_entry_struct *i86_get_idt_descriptor(int);
//==================================END========================================

//===========PRIVATE FUNCTIONS DEFINITIONS=====================================
PRIVATE _void idt_set_gate(uint8_t index, uint32_t base, uint16_t sel, uint8_t flags)
{
    idt_entries[index].base_low = (base & 0xFFFF);
    idt_entries[index].base_high = ((base >> 16) & 0xFFFF);
    
    idt_entries[index].segment_selector = sel;
    idt_entries[index].reserved = 0;
    idt_entries[index].flags = flags;
}
//=============================END==============================================

//================PUBLIC FUNCTIONS DEFINITIONS===================================
_void init_idt()
{
    idt_ptr.limit = ((sizeof(idt_entry_t) * I86_MAX_INTERRUPTS) - 1);
    idt_ptr.base = (uint32_t)(&idt_entries);
    
    mem_set(&idt_entries, 0, (sizeof(idt_entry_t) * I86_MAX_INTERRUPTS));
    
    //i86_pic_initialize(PIC_BASE_ADDRESS_0, PIC_BASE_ADDRESS_1); //initialize the PIC
    
    //registers the interrupt handlers
    idt_set_gate( 0, (uint32_t)divide_by_zero_fault, 0x08, (I86_IDT_DESC_PRESENT | I86_IDT_DESC_BIT32));
    idt_set_gate( 1, (uint32_t)single_step_trap, 0x08, (I86_IDT_DESC_PRESENT | I86_IDT_DESC_BIT32));
    idt_set_gate( 2, (uint32_t)nmi_trap, 0x08, (I86_IDT_DESC_PRESENT | I86_IDT_DESC_BIT32));
    idt_set_gate( 3, (uint32_t)breakpoint_trap, 0x08, (I86_IDT_DESC_PRESENT | I86_IDT_DESC_BIT32));
    idt_set_gate( 4, (uint32_t)overflow_trap, 0x08, (I86_IDT_DESC_PRESENT | I86_IDT_DESC_BIT32));
    idt_set_gate( 5, (uint32_t)bounds_check_fault, 0x08, (I86_IDT_DESC_PRESENT | I86_IDT_DESC_BIT32));
    idt_set_gate( 6, (uint32_t)invalid_opcode_fault, 0x08, (I86_IDT_DESC_PRESENT | I86_IDT_DESC_BIT32));
    idt_set_gate( 7, (uint32_t)no_device_fault, 0x08, (I86_IDT_DESC_PRESENT | I86_IDT_DESC_BIT32));
    idt_set_gate( 8, (uint32_t)double_fault_abort, 0x08, (I86_IDT_DESC_PRESENT | I86_IDT_DESC_BIT32));
    idt_set_gate( 9, (uint32_t)coprocessor_segment_overrun_fault, 0x08, (I86_IDT_DESC_PRESENT | I86_IDT_DESC_BIT32));
    idt_set_gate(10, (uint32_t)invalid_tss_fault, 0x08, (I86_IDT_DESC_PRESENT | I86_IDT_DESC_BIT32));
    idt_set_gate(11, (uint32_t)no_segment_fault, 0x08, (I86_IDT_DESC_PRESENT | I86_IDT_DESC_BIT32));
    idt_set_gate(12, (uint32_t)stack_fault, 0x08, (I86_IDT_DESC_PRESENT | I86_IDT_DESC_BIT32));
    idt_set_gate(13, (uint32_t)general_protection_fault, 0x08, (I86_IDT_DESC_PRESENT | I86_IDT_DESC_BIT32));
    idt_set_gate(14, (uint32_t)page_fault, 0x08, (I86_IDT_DESC_PRESENT | I86_IDT_DESC_BIT32));
    idt_set_gate(15, (uint32_t)unassigned, 0x08, (I86_IDT_DESC_PRESENT | I86_IDT_DESC_BIT32));
    idt_set_gate(16, (uint32_t)fpu_fault, 0x08, (I86_IDT_DESC_PRESENT | I86_IDT_DESC_BIT32));
    idt_set_gate(17, (uint32_t)alignment_check_fault, 0x08, (I86_IDT_DESC_PRESENT | I86_IDT_DESC_BIT32));
    idt_set_gate(18, (uint32_t)machine_check_abort, 0x08, (I86_IDT_DESC_PRESENT | I86_IDT_DESC_BIT32));
    idt_set_gate(19, (uint32_t)simd_fpu_fault, 0x08, (I86_IDT_DESC_PRESENT | I86_IDT_DESC_BIT32));
    idt_set_gate(20, (uint32_t)reserved20, 0x08, (I86_IDT_DESC_PRESENT | I86_IDT_DESC_BIT32));
    idt_set_gate(21, (uint32_t)reserved21, 0x08, (I86_IDT_DESC_PRESENT | I86_IDT_DESC_BIT32));
    idt_set_gate(22, (uint32_t)reserved22, 0x08, (I86_IDT_DESC_PRESENT | I86_IDT_DESC_BIT32));
    idt_set_gate(23, (uint32_t)reserved23, 0x08, (I86_IDT_DESC_PRESENT | I86_IDT_DESC_BIT32));
    idt_set_gate(24, (uint32_t)reserved24, 0x08, (I86_IDT_DESC_PRESENT | I86_IDT_DESC_BIT32));
    idt_set_gate(25, (uint32_t)reserved25, 0x08, (I86_IDT_DESC_PRESENT | I86_IDT_DESC_BIT32));
    idt_set_gate(26, (uint32_t)reserved26, 0x08, (I86_IDT_DESC_PRESENT | I86_IDT_DESC_BIT32));
    idt_set_gate(27, (uint32_t)reserved27, 0x08, (I86_IDT_DESC_PRESENT | I86_IDT_DESC_BIT32));
    idt_set_gate(28, (uint32_t)reserved28, 0x08, (I86_IDT_DESC_PRESENT | I86_IDT_DESC_BIT32));
    idt_set_gate(29, (uint32_t)reserved29, 0x08, (I86_IDT_DESC_PRESENT | I86_IDT_DESC_BIT32));
    idt_set_gate(30, (uint32_t)reserved30, 0x08, (I86_IDT_DESC_PRESENT | I86_IDT_DESC_BIT32));
    idt_set_gate(31, (uint32_t)reserved31, 0x08, (I86_IDT_DESC_PRESENT | I86_IDT_DESC_BIT32));
    
    i86_pic_initialize(PIC_BASE_ADDRESS_0, PIC_BASE_ADDRESS_1); //initialize the PIC
    
    idt_set_gate(32, (uint32_t)irq_timer, 0x08, (I86_IDT_DESC_PRESENT | I86_IDT_DESC_BIT32));
    idt_set_gate(33, (uint32_t)irq_keyboard, 0x08, (I86_IDT_DESC_PRESENT | I86_IDT_DESC_BIT32));
    idt_set_gate(34, (uint32_t)irq_cascade, 0x08, (I86_IDT_DESC_PRESENT | I86_IDT_DESC_BIT32));
    idt_set_gate(35, (uint32_t)irq_serial_port2, 0x08, (I86_IDT_DESC_PRESENT | I86_IDT_DESC_BIT32));
    idt_set_gate(36, (uint32_t)irq_serial_port1, 0x08, (I86_IDT_DESC_PRESENT | I86_IDT_DESC_BIT32));
    idt_set_gate(37, (uint32_t)irq_AT_parallel_port2, 0x08, (I86_IDT_DESC_PRESENT | I86_IDT_DESC_BIT32));
    idt_set_gate(38, (uint32_t)irq_diskette_drive, 0x08, (I86_IDT_DESC_PRESENT | I86_IDT_DESC_BIT32));
    idt_set_gate(39, (uint32_t)irq_parallel_port1, 0x08, (I86_IDT_DESC_PRESENT | I86_IDT_DESC_BIT32));
    
    idt_set_gate(40, (uint32_t)irq_cmos_timer, 0x08, (I86_IDT_DESC_PRESENT | I86_IDT_DESC_BIT32));
    idt_set_gate(41, (uint32_t)irq_cga_vertical_retrace, 0x08, (I86_IDT_DESC_PRESENT | I86_IDT_DESC_BIT32));
    idt_set_gate(42, (uint32_t)irq_reserved10, 0x08, (I86_IDT_DESC_PRESENT | I86_IDT_DESC_BIT32));
    idt_set_gate(43, (uint32_t)irq_reserved11, 0x08, (I86_IDT_DESC_PRESENT | I86_IDT_DESC_BIT32));
    idt_set_gate(44, (uint32_t)irq_auxiliary, 0x08, (I86_IDT_DESC_PRESENT | I86_IDT_DESC_BIT32));
    idt_set_gate(45, (uint32_t)irq_fpu, 0x08, (I86_IDT_DESC_PRESENT | I86_IDT_DESC_BIT32));
    idt_set_gate(46, (uint32_t)irq_hdc, 0x08, (I86_IDT_DESC_PRESENT | I86_IDT_DESC_BIT32));
    idt_set_gate(47, (uint32_t)irq_reserved15, 0x08, (I86_IDT_DESC_PRESENT | I86_IDT_DESC_BIT32));
    
    idt_install((uint32_t)&idt_ptr);
}

struct idt_entry_struct *i86_get_idt_descriptor(int index)
{
    if(index > I86_MAX_INTERRUPTS) return (struct idt_entry_struct*)0;
    
    return &idt_entries[index];
}

//================================END=============================================
