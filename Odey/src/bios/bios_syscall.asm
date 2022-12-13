;..............................................
;..............................................
;Initiated on Thursday, the 16th of May, 2019
;      @ 03:41PM
;by the  creator, Odey john Ebinyi.
;...............................................
;...............................................

;bios_syscall.asm ==> this assembly file helps handle every process
;                     related to system calls to the BIOS from pmode!

;==================================================
;--------------- PUBLIC FUNCTIONS -----------------
global __lock_int
global __unlock_int
global __switch_page_dir
global __enable_paging
;---------------------------------------------------
;==================================================


;==================================================
;------------------ VARIABLES ---------------------
PG_BIT   equ 		0x80000000
;--------------------------------------------------
;==================================================

;==================================================
;-------------FUNCTION IMPLEMENTATION--------------

;disables interrupts
__lock_int:
							cli
		 					ret

;enables interrupts
__unlock_int:
						    sti
		 					ret

__switch_page_dir:
							push ebp
					
							mov ebp, esp
							mov eax, [ebp+8]
							mov cr3, eax
				
							pop ebp
							ret
								
	;enables paging
__enable_paging:
							mov eax, cr0
							or eax, PG_BIT
							mov cr0, eax

							ret 

;---------------------------------------------------
;===================================================
