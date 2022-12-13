#...............................................
#...............................................
#Initiated on Saturday, the 20th of April, 2019
#      @ 02:19PM
#by the creator, Odey john Ebinyi.

#modified : Wednesday, the 19th of June, 2019 @ 07:33AM
#...............................................
#...............................................


# Some constants used for multiboot header
# No need to understand, they are just a bunch of flags and magic values for the bootloader to find and recognize it as a multibootkernel
.set ALIGN, 1<<0
.set MEMINFO, 1<<1
.set FLAGS, ALIGN | MEMINFO
.set MAGIC, 0x1BADB002
.set CHECKSUM, - (MAGIC + FLAGS)

.section .multiboot
.align 4
.long MAGIC
.long FLAGS
.long CHECKSUM

# Our initial stack
.section .initial_stack, "aw", @nobits
stack_bottom:
    # 1mb of uninitialized data(1024*1024=104856)
.skip 104856
stack_top:

.section .bss, "aw", @nobits
    .align 4096

.global boot_page_directory

boot_page_directory:
    .skip 4096
boot_page_table1:
    .skip 4096


# Kernel entry
.section .text
.global __odey_entry
.type __odey_entry, @function
__odey_entry:
    movl $(boot_page_table1 - 0xC0000000), %edi
    movl $0, %esi
    movl $1023, %ecx 

1:
  cmpl $(_kernel_start - 0xC0000000), %esi
  jl 2f
  cmpl $(_kernel_end - 0xC0000000), %esi
  jge 3f

  movl %esi, %edx
  orl $0x003, %edx
  movl %edx, (%edi)

2:
 addl $4096, %esi
 addl $4, %edi
 loop 1b

3:
  movl $(0x000B8000 | 0x003), boot_page_table1 - 0xC0000000 + 1023 *4
  movl $(boot_page_table1 - 0xC0000000 + 0x003), boot_page_directory - 0xC0000000 + 0
  movl $(boot_page_table1 - 0xC0000000 + 0x003), boot_page_directory - 0xC0000000 + 768 * 4

  movl $(boot_page_directory - 0xC0000000), %ecx
  movl %ecx, %cr3

  movl %cr0, %ecx
  orl $0x80010000, %ecx
  movl %ecx, %cr0

  lea 4f, %ecx
  jmp *%ecx

4:
  movl $0, boot_page_directory + 0

  movl %cr3, %ecx
  movl %ecx, %cr3

  movl $stack_top, %esp

  #addl $0xC0000000, %ebx
  pushl %ebx
  pushl %eax
  
  call __odey

  cli
1:hlt
  jmp 1b
