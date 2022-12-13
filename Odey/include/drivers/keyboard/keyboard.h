//...............................................
//...............................................
//Initiated on Sunday, the 05th of May, 2019
//      @ 07:03PM
//by the OS creator, Odey john Ebinyi.
//...............................................
//...............................................
//Modified: 


#ifndef __KEYBOARD_H
#define __KEYBOARD_H

//===========INCLUDED FILES=============
#include <lib/system.h>
#include <stdint.h>
#include <lib/config.h>
#include <lib/ctype.h>
#include <lib/print_string.h>
//================END===================

//this C's enum contains the keys available 
//on the system's keyboard

enum KEY_CODE 
{

    KEY_SPACE             = ' ',        KEY_0                 = '0',        KEY_1                 = '1',
    KEY_2                 = '2',        KEY_3                 = '3',        KEY_4                 = '4',
    KEY_5                 = '5',        KEY_6                 = '6',        KEY_7                 = '7',
    KEY_8                 = '8',        KEY_9                 = '9',        KEY_A                 = 'a',
    KEY_B                 = 'b',        KEY_C                 = 'c',        KEY_D                 = 'd',
    KEY_E                 = 'e',        KEY_F                 = 'f',        KEY_G                 = 'g',
    KEY_H                 = 'h',        KEY_I                 = 'i',        KEY_J                 = 'j',
    KEY_K                 = 'k',        KEY_L                 = 'l',        KEY_M                 = 'm',
    KEY_N                 = 'n',        KEY_O                 = 'o',        KEY_P                 = 'p',
    KEY_Q                 = 'q',        KEY_R                 = 'r',        KEY_S                 = 's',
    KEY_T                 = 't',        KEY_U                 = 'u',        KEY_V                 = 'v',
    KEY_W                 = 'w',        KEY_X                 = 'x',        KEY_Y                 = 'y',
    KEY_Z                 = 'z',        KEY_RETURN            = '\r',       KEY_ESCAPE            = 0x1001,
    KEY_BACKSPACE         = '\b',

/*========================================= ARROW KEYS =======================================================*/

    KEY_UP                = 0x1100,
    KEY_DOWN              = 0x1101,
    KEY_LEFT              = 0x1102,
    KEY_RIGHT             = 0x1103,
/*=============================================================================================================*/

/*======================================== FUNCTION KEYS ======================================================*/
    KEY_F1                = 0x1201,     KEY_F2                = 0x1202,     KEY_F3                = 0x1203,
    KEY_F4                = 0x1204,     KEY_F5                = 0x1205,     KEY_F6                = 0x1206,
    KEY_F7                = 0x1207,     KEY_F8                = 0x1208,     KEY_F9                = 0x1209,
    KEY_F10               = 0x120a,     KEY_F11               = 0x120b,     KEY_F12               = 0x120b,     
    KEY_F13               = 0x120c,     KEY_F14               = 0x120d,     KEY_F15               = 0x120e,

    
    KEY_DOT               = '.',        KEY_COMMA             = ',',        KEY_COLON             = ':',
    KEY_SEMICOLON         = ';',        KEY_SLASH             = '/',        KEY_BACKSLASH         = '\\',
    KEY_PLUS              = '+',        KEY_MINUS             = '-',        KEY_ASTERISK          = '*',
    KEY_EXCLAMATION       = '!',        KEY_QUESTION          = '?',        KEY_QUOTEDOUBLE       = '\"',
    KEY_QUOTE             = '\'',       KEY_EQUAL             = '=',        KEY_HASH              = '#',
    KEY_PERCENT           = '%',        KEY_AMPERSAND         = '&',        KEY_UNDERSCORE        = '_',
    KEY_LEFTPARENTHESIS   = '(',        KEY_RIGHTPARENTHESIS  = ')',        KEY_LEFTBRACKET       = '[',
    KEY_RIGHTBRACKET      = ']',        KEY_LEFTCURL          = '{',        KEY_RIGHTCURL         = '}',
    KEY_DOLLAR            = '$',
    /*KEY_POUND             = '',*/     KEY_EURO              = '$',        KEY_LESS              = '<',
    KEY_GREATER           = '>',        KEY_BAR               = '|',        KEY_GRAVE             = '`',
    KEY_TILDE             = '~',        KEY_AT                = '@',        KEY_CARRET            = '^',
/*===========================================================================================================*/

    KEY_KP_0              = '0',        KEY_KP_1              = '1',        KEY_KP_2              = '2',
    KEY_KP_3              = '3',        KEY_KP_4              = '4',        KEY_KP_5              = '5',
    KEY_KP_6              = '6',        KEY_KP_7              = '7',        KEY_KP_8              = '8',
    KEY_KP_9              = '9',        KEY_KP_PLUS           = '+',        KEY_KP_MINUS          = '-',
    KEY_KP_DECIMAL        = '.',        KEY_KP_DIVIDE         = '/',        KEY_KP_ASTERISK       = '*',
    KEY_KP_NUMLOCK        = 0x300f,     KEY_KP_ENTER          = 0x3010,     KEY_TAB               = 0x4000,
    KEY_CAPSLOCK          = 0x4001,



    KEY_LSHIFT            = 0x4002,     KEY_LCTRL             = 0x4003,     KEY_LALT              = 0x4004,
    KEY_LWIN              = 0x4005,     KEY_RSHIFT            = 0x4006,     KEY_RCTRL             = 0x4007,
    KEY_RALT              = 0x4008,     KEY_RWIN              = 0x4009,

    KEY_INSERT            = 0x400a,     KEY_DELETE            = 0x400b,     KEY_HOME              = 0x400c,
    KEY_END               = 0x400d,

    KEY_PAGEUP            = 0x400e,     KEY_PAGEDOWN          = 0x400f,     KEY_SCROLLLOCK        = 0x4010,
    KEY_PAUSE             = 0x4011,

    KEY_UNKNOWN,
    KEY_NUMKEYCODES
};



//! original xt scan code set. Array index==make code
//! change what keys the scan code corrospond to if your scan code set is different
PRIVATE int _kybrd_scancode_std[] = 
{
    KEY_UNKNOWN,       KEY_ESCAPE,         KEY_1,             KEY_2,              KEY_3,   
    KEY_4,             KEY_5,              KEY_6,             KEY_7,              KEY_8,              
    KEY_9,             KEY_0,              KEY_MINUS,         KEY_EQUAL,          KEY_BACKSPACE,      
    KEY_TAB,           KEY_Q,              KEY_W,             KEY_E,              KEY_R,              
    KEY_T,             KEY_Y,              KEY_U,             KEY_I,              KEY_O,            
    KEY_P,             KEY_LEFTBRACKET,    KEY_RIGHTBRACKET,  KEY_RETURN,         KEY_LCTRL,          
    KEY_A,             KEY_S,              KEY_D,             KEY_F,              KEY_G,      
    KEY_H,             KEY_J,              KEY_K,             KEY_L,              KEY_SEMICOLON,     
    KEY_QUOTE,         KEY_GRAVE,          KEY_LSHIFT,        KEY_BACKSLASH,      KEY_Z,    
    KEY_X,             KEY_C,              KEY_V,             KEY_B,              KEY_N,     
    KEY_M,             KEY_COMMA,          KEY_DOT,           KEY_SLASH,          KEY_RSHIFT,  
    KEY_KP_ASTERISK,   KEY_RALT,           KEY_SPACE,         KEY_CAPSLOCK,       KEY_F1,    
    KEY_F2,            KEY_F3,             KEY_F4,            KEY_F5,             KEY_F6, 
    KEY_F7,            KEY_F8,             KEY_F9,            KEY_F10,            KEY_KP_NUMLOCK, 
    KEY_SCROLLLOCK,    KEY_HOME,           KEY_KP_8,          KEY_PAGEUP,         KEY_KP_2,  
    KEY_KP_3,          KEY_KP_0,           KEY_KP_DECIMAL,    KEY_UNKNOWN,        KEY_UNKNOWN,     
    KEY_UNKNOWN,       KEY_F11,            KEY_F12           
};



//===================EXTERN FUNCTIONS================
_extern _void kybrd_ignore_resend();

_extern _bool kybrd_check_resend();

_extern _bool kybrd_get_diagnostic_res ();

_extern _bool kybrd_get_bat_res ();

_extern _bool kybrd_self_test ();

_extern _bool kybrd_get_bat_res();

_extern uint8_t kybrd_get_last_scan();

//disables the keyboard
_extern _void kybrd_disable();

//enables the keyboard
_extern _void kybrd_enable();

//returns true if keyboard is disabled
_extern _bool kybrd_is_disabled();

_extern _void kybrd_reset_system();

_extern _bool kybrd_get_ctrl_key_status();

_extern _bool kybrd_get_shift_key_status();

_extern _bool kybrd_get_alt_key_status();

_extern enum KEY_CODE kybrd_get_last_key();

_extern _void discard_last_key();

_extern _char kybrd_key_to_ascii(enum KEY_CODE);

//updates LED's
_extern _void kybrd_set_leds (_bool, _bool, _bool);

_extern _void kybrd_install();
//=========================END=======================

#endif
