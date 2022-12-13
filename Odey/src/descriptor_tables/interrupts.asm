;...............................................
;...............................................
;Initiated on Monday, the 22nd of April, 2019
;      @ 03:30PM
;by the OS creator, Odey john Ebinyi.
;...............................................
;...............................................

bits 32

;interrupt 8, 10 - 14 pushes error code on the stack by default
;=================================================
;Interrupt Service Routines
global divide_by_zero_fault
global single_step_trap
global nmi_trap
global breakpoint_trap
global overflow_trap
global bounds_check_fault
global invalid_opcode_fault
global no_device_fault
global double_fault_abort
global coprocessor_segment_overrun_fault
global invalid_tss_fault
global no_segment_fault
global stack_fault
global general_protection_fault
global page_fault
global unassigned
global fpu_fault
global alignment_check_fault
global machine_check_abort
global simd_fpu_fault
global reserved20
global reserved21
global reserved22
global reserved23
global reserved24
global reserved25
global reserved26
global reserved27
global reserved28
global reserved29
global reserved30
global reserved31
;=====================================================
 
     
divide_by_zero_fault:
                        cli
                        push byte 0
                        push byte 0
                        jmp ISR_COMMON_STUB
    
single_step_trap:
                        cli
                        push byte 0
                        push byte 1
                        jmp ISR_COMMON_STUB
    
    
    
nmi_trap:
                        cli
                        push byte 0
                        push byte 2
                        jmp ISR_COMMON_STUB
    
    
breakpoint_trap:
                        cli
                        push byte 0
                        push byte 3
                        jmp ISR_COMMON_STUB
    
    
overflow_trap:
                        cli
                        push byte 0
                        push byte 4
                        jmp ISR_COMMON_STUB
    
    
bounds_check_fault:
                        cli
                        push byte 0
                        push byte 5
                        jmp ISR_COMMON_STUB
    
    
invalid_opcode_fault:
                        cli
                        push byte 0
                        push byte 6
                        jmp ISR_COMMON_STUB
    
    
no_device_fault:
                        cli
                        push byte 0
                        push byte 7
                        jmp ISR_COMMON_STUB
    
double_fault_abort:
                        cli
                        ;push byte 0
                        push byte 8
                        jmp ISR_COMMON_STUB
    
    
coprocessor_segment_overrun_fault:
                        cli
                        push byte 0
                        push byte 9
                        jmp ISR_COMMON_STUB
    
    
invalid_tss_fault:
                        cli
                        ;push byte 0
                        push byte 10
                        jmp ISR_COMMON_STUB
    
    
no_segment_fault:
                        cli
                        ;push byte 0
                        push byte 11
                        jmp ISR_COMMON_STUB
    
    
stack_fault:
                        cli
                        ;push byte 0
                        push byte 12
                        jmp ISR_COMMON_STUB
        
    
general_protection_fault:
                        cli
                        ;push byte 0
                        push byte 13
                        jmp ISR_COMMON_STUB
    
    
page_fault:
                        cli
                        ;push byte 0
                        push byte 14
                        jmp ISR_COMMON_STUB
    
    
unassigned:
                        cli
                        push byte 0
                        push byte 15
                        jmp ISR_COMMON_STUB
    
    
fpu_fault:
                        cli
                        push byte 0
                        push byte 16
                        jmp ISR_COMMON_STUB
    
    
alignment_check_fault:
                        cli
                        push byte 0
                        push byte 17
                        jmp ISR_COMMON_STUB
    
    
machine_check_abort:
                        cli
                        push byte 0
                        push byte 18
                        jmp ISR_COMMON_STUB
    
    
simd_fpu_fault:
                        cli
                        push byte 0
                        push byte 19
                        jmp ISR_COMMON_STUB
    
    
reserved20:
                        cli
                        push byte 0
                        push byte 20
                        jmp ISR_COMMON_STUB
    
    
reserved21:
                        cli
                        push byte 0
                        push byte 21
                        jmp ISR_COMMON_STUB
    
    
reserved22:
                        cli
                        push byte 0
                        push byte 22
                        jmp ISR_COMMON_STUB
    
    
reserved23:
                        cli
                        push byte 0
                        push byte 23
                        jmp ISR_COMMON_STUB
    
    
reserved24:
                        cli
                        push byte 0
                        push byte 24
                        jmp ISR_COMMON_STUB
    
    
reserved25:
                        cli
                        push byte 0
                        push byte 25
                        jmp ISR_COMMON_STUB
    
    
reserved26:
                        cli
                        push byte 0
                        push byte 26
                        jmp ISR_COMMON_STUB
    
    
reserved27:
                        cli
                        push byte 0
                        push byte 27
                        jmp ISR_COMMON_STUB
    
    
reserved28:
                        cli
                        push byte 0
                        push byte 28
                        jmp ISR_COMMON_STUB
    
    
reserved29:
                        cli
                        push byte 0
                        push byte 29
                        jmp ISR_COMMON_STUB
    
    
reserved30:
                        cli
                        push byte 0
                        push byte 30
                        jmp ISR_COMMON_STUB
    
    
reserved31:
                        cli
                        push byte 0
                        push byte 31
                        jmp ISR_COMMON_STUB
    
;handles an exception fault (it is an external C function)
extern exception_handler


;saves the current process state i.e registers, code segment, data segment etc

;onto the stack for recovery purposes

ISR_COMMON_STUB:
    pusha           ; Pushes edi,esi,ebp,esp,ebx,edx,ecx,eax in a sequential order
    push ds
    push es
    push fs
    push gs
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov eax, esp
    push eax
    mov eax, exception_handler
    call eax
    pop eax
    pop gs
    pop fs
    pop es
    pop ds
    popa
    add esp, 8
    iret
    

;================IRQs===================
global irq_timer
global irq_keyboard
global irq_cascade
global irq_serial_port2
global irq_serial_port1
global irq_AT_parallel_port2
global irq_diskette_drive
global irq_parallel_port1

global irq_cmos_timer
global irq_cga_vertical_retrace
global irq_reserved10
global irq_reserved11
global irq_auxiliary
global irq_fpu
global irq_hdc
global irq_reserved15
;=========================================

irq_timer:
    cli
    push byte 0
    push byte 32
    jmp IRQ_COMMON_STUB
    
irq_keyboard:
    cli 
    push byte 0
    push byte 33
    jmp IRQ_COMMON_STUB
    
irq_cascade:
    cli
    push byte 0
    push byte 34
    jmp IRQ_COMMON_STUB
    
irq_serial_port2:
      cli
    push byte 0
    push byte 35
    jmp IRQ_COMMON_STUB
    
irq_serial_port1:
      cli
    push byte 0
    push byte 36
    jmp IRQ_COMMON_STUB
    
irq_AT_parallel_port2:
      cli
    push byte 0
    push byte 37
    jmp IRQ_COMMON_STUB
    
irq_diskette_drive:
      cli
    push byte 0
    push byte 38
    jmp IRQ_COMMON_STUB
    
irq_parallel_port1:
      cli
    push byte 0
    push byte 39
    jmp IRQ_COMMON_STUB
    
irq_cmos_timer:
      cli
    push byte 0
    push byte 40
    jmp IRQ_COMMON_STUB
    
irq_cga_vertical_retrace:
      cli
    push byte 0
    push byte 41
    jmp IRQ_COMMON_STUB
    
irq_reserved10:
      cli
    push byte 0
    push byte 42
    jmp IRQ_COMMON_STUB
    
irq_reserved11:
      cli
    push byte 0
    push byte 43
    jmp IRQ_COMMON_STUB
    
irq_auxiliary:
      cli
    push byte 0
    push byte 44
    jmp IRQ_COMMON_STUB
    
irq_fpu:
      cli
    push byte 0
    push byte 45
    jmp IRQ_COMMON_STUB
    
irq_hdc:
      cli
    push byte 0
    push byte 46
    jmp IRQ_COMMON_STUB
    
irq_reserved15:
      cli
    push byte 0
    push byte 47
    jmp IRQ_COMMON_STUB

;========================================

extern irq_handler

IRQ_COMMON_STUB:
    pusha

    push ds

    push es

    push fs

    push gs

    

    mov ax, 0x10

    mov ds, ax

    mov es, ax

    mov fs, ax

    mov gs, ax

    

    mov eax, esp

    

    push eax

    mov eax, irq_handler

    call eax

    pop eax

    

    pop gs

    pop fs

    pop es

    pop ds

    popa

    add esp, 8

    iret

    
