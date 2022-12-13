;this file is the odey's entry point responsible for the initialization of the kernel

[BITS 32]

;Below are flags and magic values for use by GRUB
MULTIBOOT_PAGE_ALIGN     equ         1 << 0
MULTIBOOT_MEM_INFO       equ         1 << 1
MULTIBOOT_MAGIC_VAL      equ         0x1BADB002

MULTIBOOT_FLAGS          equ         (MULTIBOOT_PAGE_ALIGN | MULTIBOOT_MEM_INFO)
MULTIBOOT_CHECK_SUM      equ        -(MULTIBOOT_MAGIC_VAL + MULTIBOOT_FLAGS)

section   .grub_multiboot
    dd MULTIBOOT_MAGIC_VAL
    dd MULTIBOOT_FLAGS
    dd MULTIBOOT_CHECK_SUM


section    .text
global   _odey_entry_
extern   __odey
_odey_entry_:
    cli

    mov     esp, stack;
    mov     ebp, 0

    push    ebx
    push    eax

    call __odey
    jmp $

section    .bss
    stack:
    resb    0x4000  ;16K stack

