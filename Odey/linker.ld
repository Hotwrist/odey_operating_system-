ENTRY(_odey_entry_)
OUTPUT_FORMAT(elf32-i386)
OUTPUT_ARCH(i386:i386)

physical_address_start = 0x00100000;

SECTIONS
{
    . = physical_address_start;

    .text :
    {
        *(.grub_multiboot)
        *(.text)
    }

   .data :
    {
        *(.data)
    }

    .bss  :
    {
        *(.bss)
    }

}