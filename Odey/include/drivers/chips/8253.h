//...............................................
//...............................................
//Initiated on Friday, the 26th of April, 2019
//      @ 04:36PM
//by the creator, Odey john Ebinyi.
//...............................................
//...............................................


#ifndef __PIT_H
#define __PIT_H

//=========INCLUDED FILES===========
#include <lib/glo.h>
#include <stdint.h>
#include <lib/config.h>
//=============END==================


#define		I86_PIT_REG_COUNTER0		0x40
#define		I86_PIT_REG_COUNTER1		0x41
#define		I86_PIT_REG_COUNTER2		0x42
#define		I86_PIT_REG_COMMAND			0x43


/*This file contains the interface for the 8253 x86 architecture
 * that signals interrupts on their programmed count!
 */

//============================================================
//PIT operational command bit masks
#define     I86_PIT_OCW_MASK_BINARY_COUNTER     1       //00000001
#define     I86_PIT_OCW_MASK_OPERATING_MODE     0xE     //00001110
#define     I86_PIT_OCW_MASK_READ_LOAD_MODE     0x30    //00110000
#define     I86_PIT_OCW_MASK_SELECT_COUNTER     0xC0    //11000000
//=============================================================

//=============================================================
//-----------------------------------------------
//	Operational Command control bits
//-----------------------------------------------

//Use when setting binary count mode : uses only bit 0
#define     I86_PIT_OCW_BINARY_COUNTER_BINARY                        0       //00000000
#define     I86_PIT_OCW_BINARY_COUNTER_BCD                           0x1     //00000001

//Use when setting counter mode : uses bits 1 -> 3
#define     I86_PIT_OCW_OPERATING_MODE_TERMINAL_COUNT               0       //00000000
#define     I86_PIT_OCW_OPERATING_MODE_ONE_SHOT                     0x2     //00000010
#define     I86_PIT_OCW_OPERATING_MODE_RATE_GENERATOR               0x4     //00000100
#define     I86_PIT_OCW_OPERATING_MODE_SQUARE_WAVE_GENERATOR        0x6     //00000110
#define     I86_PIT_OCW_OPERATING_MODE_SOFTWARE_TRIGGERED           0x8     //00001000
#define     I86_PIT_OCW_OPERATING_MODE_HARDWARE_TRIGGERED           0xA     //00001010

//Use when setting data transfer : uses bits 4 -> 5
#define     I86_PIT_OCW_READ_LOAD_MODE_LATCH                        0       //00000000
#define     I86_PIT_OCW_READ_LOAD_MODE_LSB_ONLY                     0x10    //00010000
#define     I86_PIT_OCW_READ_LOAD_MODE_MSB_ONLY                     0x20    //00100000 
#define     I86_PIT_OCW_READ_LOAD_MODE_LSB_MSB                      0x30    //00110000

//Use when setting counter we want to work with : uses bits 6 -> 7
#define    I86_PIT_OCW_SELECT_COUNTER_COUNTER0                      0       //00000000
#define    I86_PIT_OCW_SELECT_COUNTER_COUNTER1                      0x40    //01000000
#define    I86_PIT_OCW_SELECT_COUNTER_COUNTER2                      0x80    //10000000


//====================EXTERN FUNCTIONS=========================================

//send operational command to pit. Set up command by using the operational

//command bit masks and setting them with the control bits. Shouldn't need to use

//this outside the interface
extern void i86_pit_send_command(uint8_t);

//write data byte to a counter
extern void i86_pit_send_data(uint16_t, uint8_t);

//reads data from a counter
extern uint8_t i86_pit_read_data(uint16_t);

//Sets new pit tick count and returns prev. value
extern uint32_t i86_pit_set_tick_count(uint32_t);

//returns current tick count
extern uint32_t i86_pit_get_tick_count();

//starts a counter. Counter continues until another call to this routine
extern void i86_pit_start_counter(uint32_t, uint8_t, uint8_t);

//Initialize minidriver
extern void i86_pit_initialize();

//Test if interface is initialized
extern bool i86_pit_is_initialized();

/* This will continuously loop until the given time has
*  been reached */
extern void timer_wait(int);
//===============================END==============================================

#endif
