#GCCPARAMS = -Wall -O -fstrength-reduce -fomit-frame-pointer -finline-functions -nostdinc -fno-builtin -I./include -c 
#GCC_PARAMS = -m32 -c -ffreestanding -I./include -Werror
#GCC_PARAMS = -m32 -nostdlib -nostdinc -fno-builtin -fno-stack-protector \
             -Wall -Wextra -c -I./include


# -nostdinc ==> Do not search the standard system directories for header files. 
# Only the directories explicitly specified with ‘-I’

 
GCC_PARAMS = -m32 -nostdlib -ffreestanding -fno-builtin -fno-stack-protector -nostartfiles -nodefaultlibs -Wall -Wextra\
	     -c -I./include
	     
NASM_PARAMS =  -f elf32
AS_PARAMS = --32

LD_PARAMS = -melf_i386

QEMU = qemu-system-i386

#missing files: single_llist.o

objects = \
	  obj/odey_entry.o \
	  obj/gdt.o\
	  obj/idt.o\
	  obj/isr.o\
	  obj/ctype.o\
	  obj/console.o\
	  obj/terminal.o\
	  obj/bios_syscall.o\
	  obj/interrupts.o\
	  obj/exceptions.o\
	  obj/descriptor_tables.o\
	  obj/system.o\
	  obj/string.o\
	  obj/print_string.o\
	  obj/k_panic.o\
	  obj/keyboard.o\
	  obj/phys_mmngr.o\
	  obj/paging.o\
	  obj/stack.o\
	  obj/virt_memmngr.o\
	  obj/8259A.o\
	  obj/8253.o\
	  obj/k_main.o

	
obj/odey_entry.o: src/kernel/odey_loader/odey_entry.asm
	mkdir -p $(@D)
	nasm $(NASM_PARAMS) -o $@ $<
	
#obj/%.o: src/data_structs/single_llist.c
#	mkdir -p $(@D)
#	i686-elf-gcc $(GCC_PARAMS) -o $@ $<

obj/bios_syscall.o: src/bios/bios_syscall.asm
	mkdir -p $(@D)
	nasm $(NASM_PARAMS) -o $@ $<  
	    
obj/descriptor_tables.o: src/descriptor_tables/descriptor_tables.asm
	mkdir -p $(@D)
	nasm $(NASM_PARAMS) -o $@ $<
	
obj/interrupts.o: src/descriptor_tables/interrupts.asm
	mkdir -p $(@D)
	nasm $(NASM_PARAMS) -o $@ $<
	
obj/%.o: src/lib/%.c
	mkdir -p $(@D)
	i686-elf-gcc $(GCC_PARAMS) -o $@ $<
	  	  
obj/%.o: src/data_structures/%.c
	mkdir -p $(@D)
	i686-elf-gcc $(GCC_PARAMS) -o $@ $<
	  	 

obj/%.o: src/descriptor_tables/%.c
	mkdir -p $(@D)
	i686-elf-gcc $(GCC_PARAMS) -o $@ $<
	
obj/%.o: src/drivers/chips/%.c
	mkdir -p $(@D)
	i686-elf-gcc $(GCC_PARAMS) -o $@ $<
	
obj/keyboard.o: src/drivers/keyboard/keyboard.c
	mkdir -p $(@D)
	i686-elf-gcc $(GCC_PARAMS) -o $@ $<
	
obj/print_string.o: src/kernel/debug_utils/print_string.c
	mkdir -p $(@D)
	i686-elf-gcc $(GCC_PARAMS) -o $@ $<
	
obj/%.o: src/drivers/screen/%.c
	mkdir -p $(@D)
	i686-elf-gcc $(GCC_PARAMS) -o $@ $<
	
obj/%.o: src/kernel/mem/%.c
	mkdir -p $(@D)
	i686-elf-gcc $(GCC_PARAMS) -o $@ $<
	
obj/%.o: src/kernel/%.c
	mkdir -p $(@D)
	i686-elf-gcc $(GCC_PARAMS) -o $@ $<
	
	
mykernel.bin: linker.ld $(objects)
	mkdir -p $(@D)
	ld $(LD_PARAMS) -T $< -o $@ $(objects)
	#$(QEMU) -kernel mykernel.bin

install: mykernel.bin
	sudo cp $< /boot/mykernel.bin

mykernel.iso: mykernel.bin
	mkdir iso
	mkdir iso/boot
	mkdir iso/boot/grub
	cp $< iso/boot/
	echo 'set timeout=0' >> iso/boot/grub/grub.cfg
	echo 'set default=0' >> iso/boot/grub/grub.cfg
	echo '' >> iso/boot/grub/grub.cfg
	echo 'menuentry "odey" {' >> iso/boot/grub/grub.cfg
	echo '	multiboot /boot/mykernel.bin' >> iso/boot/grub/grub.cfg
	#echo '  set root (hd0,0)' >> iso/boot/grub/grub.cfg
	echo '  module  /boot/mykernel.bin' >> iso/boot/grub/grub.cfg
	echo '}' >> iso/boot/grub/grub.cfg
	grub-mkrescue --output=$@ iso
	rm -rf iso
	

run: mykernel.iso
	(killall VirtualBox && sleep 1) || true
	VirtualBox --startvm "ODEY" &
	
#run: mykernel.iso
#	$(QEMU) -cdrom mykernel.iso
	
.PHONY: clean
clean:
	rm -f $(objects) mykernel.bin mykernel.iso
