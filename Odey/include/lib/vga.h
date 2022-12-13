#ifndef __VGA_H__
#define __VGA_H__

#include "stdint.h"


//==============the VGA frame buffer properties======
#define      I86_VGA_MEM_ADDRESS        0x000B8000
#define      SCREEN_WIDTH               80
#define      SCREEN_HEIGHT              25
//================END================================
//===================================================

//==================================================================
//an enumeration constant for colors supported in text mode or VGA
enum VGA_COLORS
{
    BLACK           =       0,
    BLUE            =       1,
    GREEN           =       2,
    CYAN            =       3,
    RED             =       4,
    MAGENTA         =       5,
    BROWN           =       6,
    LIGHT_GREY      =       7,
    DARK_GREY       =       8,
    LIGHT_BLUE      =       9,
    LIGHT_GREEN     =       0xA,
    LIGHT_CYAN      =       0xB,
    LIGHT_RED       =       0xC,
    LIGHT_MAGENTA   =       0xD,
    YELLOW          =       0xE,
    WHITE           =       0xF,
    MAX
};

typedef struct vga
{
    uint16_t *vga_mem_address;      //pointer to VGA memory address: 0xB8000
    uint8_t screen_width;           //screen width: 80
    uint8_t screen_height;          //screen height: 25
    enum VGA_COLORS vga_bg_color;   //background color 
    enum VGA_COLORS vga_fg_color;   //foreground color
}vga_t;


#endif