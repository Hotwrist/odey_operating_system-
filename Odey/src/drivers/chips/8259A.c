//************************************
//  8259A IMPLEMENTATION FILE
//************************************

//=============WORKING=============================
//*************************************************
// send ICW1 to PIC1(0x20) and PIC2(0xA0)
// send ICW2 to PIC1 Command reg(0x21) and PIC2 Command reg(0xA1)
// send ICW3 to PIC1 Command reg(0x21) and PIC2 Command reg(0xA1)
// finally, send ICW4 to PIC1 Command reg(0x21) and PIC2 Command reg(0xA1)
//*************************************************
//===============END================================


//=============NECESSARY HEADERS INCLUSION=========
#include <drivers/chips/8259A.h>
//====================END==========================



//==============PUBLIC FUNCTIONS PROTOTYPES========
//Initialize pic
_void i86_pic_initialize(uint8_t , uint8_t );

//Read data byte from pic
uint8_t i86_pic_read_data(uint8_t);

//Send a data byte to pic
_void i86_pic_send_data(uint8_t, uint8_t);

//Send operational command to pic
_void i86_pic_send_command(uint8_t , uint8_t);

//disables PIC to use the system local PIC
_void disable_pic();

//Enables and disables interrupts
//void i86_pic_mask_irq (uint8_t irqmask, uint8_t picNum);


//=====================END=========================

//=============PUBLIC FUNCTIONS IMPLEMENTATIONS====

_void i86_pic_send_data(uint8_t data, uint8_t pic_num)
{
    if(pic_num > 1) return;
    
    uint8_t reg = ((pic_num == 1) ? I86_PIC2_REG_DATA : I86_PIC1_REG_DATA);
    
    outport_byte(reg, data);
}

_void i86_pic_send_command(uint8_t cmd, uint8_t pic_num)
{
    if(pic_num > 1) return;
    
    uint8_t reg = ((pic_num == 1) ? I86_PIC2_REG_COMMAND : I86_PIC1_REG_COMMAND);
    
    outport_byte(reg, cmd);
}

uint8_t i86_pic_read_data(uint8_t pic_num)
{
    if(pic_num > 1) return 0;
    
    uint8_t reg = ((pic_num == 1) ? I86_PIC2_REG_DATA : I86_PIC1_REG_DATA);
    
    return inport_byte(reg);
}

_void disable_pic()
{
    i86_pic_send_data(0xFF, 0);
    i86_pic_send_data(0xFF, 1);
}

_void i86_pic_initialize(uint8_t base_address0, uint8_t base_address1)
{
    uint8_t icw_1 = (I86_PIC_ICW1_MASK_IC4 | I86_PIC_ICW1_MASK_INIT) ;   //0x11 ==> 0001 0001
    
    //send ICW1 to both PICs
    i86_pic_send_command(icw_1, 0);
    i86_pic_send_command(icw_1, 1);
    
    //Send initialization control word 2. This is the base addresses of the irq's
    i86_pic_send_data(base_address0, 0);
    i86_pic_send_data(base_address1, 1);
    
    //Send initialization control word 3. This is the connection between master and slave.
	//ICW3 for master PIC is the IR that connects to secondary pic in binary format
	//ICW3 for secondary PIC is the IR that connects to master pic in decimal format
    i86_pic_send_data(0x04, 0);
    i86_pic_send_data(0x02, 1);
    
    uint8_t icw_4 =  I86_PIC_ICW4_UPM_86MODE;
    
    i86_pic_send_data(icw_4, 0);
    i86_pic_send_data(icw_4, 1);
    
    i86_pic_send_data(0x0, 0);
    i86_pic_send_data(0x0, 1);
    
    //disables PIC
    //disable_pic();

}
