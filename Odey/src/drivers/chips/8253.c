/*8253.c ==> This file is the implementation of the PIT
 */

//=======INCLUDED FILES=============
#include <lib/isr.h>
#include <lib/system.h>
#include <drivers/chips/8253.h>
#include <lib/print_string.h>
//============END===================

//==============VARIABLES========================
//Global Tick count
PRIVATE _volatile uint32_t tick_count = 0;

//Test if pit is initialized
PRIVATE _bool is_pit_initalized = false;
//==================END==========================



//=================PUBLIC FUNCIONS PROTOTYPES===================
_void i86_pit_send_command(uint8_t);

_void i86_pit_send_data(uint16_t, uint8_t);

uint8_t i86_pit_read_data(uint16_t);

uint32_t i86_pit_set_tick_count(uint32_t);

uint32_t i86_pit_get_tick_count();

_void i86_pit_start_counter(uint32_t, uint8_t, uint8_t);

_void i86_pit_initialize();

_bool i86_pit_is_initialized();

_void timer_wait(int);

//===========================END================================

//==============PRIVATE FUNCTION(S) PROTOTYPE(S)================

//pit timer interrupt handler
PRIVATE _void i86_pit_irq ();

//=========================END==================================


//=======================PUBLIC/PRIVATE FUNCIONS DEFINITIONS======================================

//Sets new pit tick count and returns prev. value
uint32_t i86_pit_set_tick_count(uint32_t new_pit_count)
{

	uint32_t ret = tick_count;
	tick_count = new_pit_count;
	return ret;
}

//returns current tick count
uint32_t i86_pit_get_tick_count() 
{
	return tick_count;
}

//send command to pit
_void i86_pit_send_command(uint8_t cmd)
{
	outport_byte(I86_PIT_REG_COMMAND, cmd);
}

//send data to a counter
_void i86_pit_send_data(uint16_t data, uint8_t counter)
{
	uint8_t	port = (counter == I86_PIT_OCW_SELECT_COUNTER_COUNTER0) ? I86_PIT_REG_COUNTER0 :
		((counter == I86_PIT_OCW_SELECT_COUNTER_COUNTER1) ? I86_PIT_REG_COUNTER1 : I86_PIT_REG_COUNTER2);

	outport_byte(port, (uint8_t)data);
}

//read data from counter
uint8_t i86_pit_read_data(uint16_t counter) 
{
	uint8_t	port= (counter == I86_PIT_OCW_SELECT_COUNTER_COUNTER0) ? I86_PIT_REG_COUNTER0 :
		((counter == I86_PIT_OCW_SELECT_COUNTER_COUNTER1) ? I86_PIT_REG_COUNTER1 : I86_PIT_REG_COUNTER2);

	return inport_byte(port);
}

//starts a counter
_void i86_pit_start_counter(uint32_t freq, uint8_t counter, uint8_t mode)
{
	if (freq == 0) return;

	uint16_t divisor = (uint16_t)(1193181 / (uint16_t)freq);

	//send operational command
	uint8_t ocw=0;
	ocw = ((ocw & ~I86_PIT_OCW_MASK_OPERATING_MODE) | mode);
	ocw = ((ocw & ~I86_PIT_OCW_MASK_READ_LOAD_MODE) | I86_PIT_OCW_READ_LOAD_MODE_LSB_MSB);
	ocw = ((ocw & ~I86_PIT_OCW_MASK_SELECT_COUNTER) | counter);
    
	i86_pit_send_command(ocw);

	//set frequency rate
	i86_pit_send_data((divisor & 0xff), 0);
	i86_pit_send_data(((divisor >> 8) & 0xff), 0);

	//reset tick count
    tick_count = 0;
}

PRIVATE _void i86_pit_irq(/*registers_t *regs*/)
{
   tick_count++;
   //print_fmt_string("Tick: %d\n", tick_count);
}

_void i86_pit_initialize()
{
    register_interrupt_handlers(IRQ0, &i86_pit_irq);
    
    is_pit_initalized = true;
}

//test if pit interface is initialized
_bool i86_pit_is_initialized ()
{
	return is_pit_initalized;
}

_void timer_wait(int ticks)
{
    unsigned long t_ticks;
    t_ticks = tick_count + ticks;

    while(tick_count < t_ticks);
}

//===============================END=============================================
