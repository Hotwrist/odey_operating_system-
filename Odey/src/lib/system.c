#include <lib/system.h>

//====================PUBLIC EXTERN FUNCTIONS PROTOTYPES=====================
uint8_t inport_byte(uint16_t);
_void outport_byte(uint16_t, uint8_t);
//================================END========================================

//===================PUBLIC EXTERN FUNCTIONS DEFINITIONS=====================       

uint8_t inport_byte(uint16_t port_number)                                         
{
    uint8_t data;
    //__asm__ __volatile__("inb %1, %0" : "=a"(data) : "dN"(port_number));
    __asm__ __volatile__("inb %%dx, %%al" : "=a"(data) : "d"(port_number));
    
    return data;
}

_void outport_byte(uint16_t port_number, uint8_t data)
{
    //__asm__ __volatile__("outb %0, %1" : : "a"(data), "dN"(port_number));
    __asm__ __volatile__("outb %%al, %%dx" ::"a"(data), "d"(port_number));
}

//=================================END========================================
