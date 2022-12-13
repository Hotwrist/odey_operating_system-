//#####################################
/*keyboard.c ==> contains the keyboard
*                drivers!!
*/
//####################################


#include <lib/isr.h>
#include <drivers/keyboard/keyboard.h>

// #defines for the keyboard encoder and controller
#define     KYBRD_ENCODER_PORT      0x60
#define     KYBRD_CTRL_PORT         0x64

#define     KEY_RELEASED_CODE       0x80



// keyboard encoder details
enum KYBRD_ENCODER_IO
{
        KYBRD_ENCODER_INPUT_BUF = KYBRD_ENCODER_PORT,
        KYBRD_ENCODER_CMD_REG =  KYBRD_ENCODER_PORT
};

enum KYBRD_ENC_CMDS
{

    KYBRD_ENC_CMD_SET_LED               =    0xED,
    KYBRD_ENC_CMD_ECHO                  =    0xEE,
    KYBRD_ENC_CMD_SCAN_CODE_SET         =    0xF0,
    KYBRD_ENC_CMD_ID                    =    0xF2,
    KYBRD_ENC_CMD_AUTODELAY             =    0xF3,
    KYBRD_ENC_CMD_ENABLE                =    0xF4,
    KYBRD_ENC_CMD_RESETWAIT             =    0xF5,
    KYBRD_ENC_CMD_RESETSCAN             =    0xF6,
    KYBRD_ENC_CMD_ALL_AUTO              =    0xF7,
    KYBRD_ENC_CMD_ALL_MAKEBREAK         =    0xF8,
    KYBRD_ENC_CMD_ALL_MAKEONLY          =    0xF9,
    KYBRD_ENC_CMD_ALL_MAKEBREAK_AUTO    =    0xFA,
    KYBRD_ENC_CMD_SINGLE_AUTOREPEAT     =    0xFB,
    KYBRD_ENC_CMD_SINGLE_MAKEBREAK      =    0xFC,
    KYBRD_ENC_CMD_SINGLE_BREAKONLY      =    0xFD,
    KYBRD_ENC_CMD_RESEND                =    0xFE,
    KYBRD_ENC_CMD_RESET                 =    0xFF
};

// Onboard keyboard controller details

enum KYBRD_CTRL_IO
{
        KYBRD_CTRL_STATS_REG = KYBRD_CTRL_PORT,
        KYBRD_CTRL_CMD_REG = KYBRD_CTRL_PORT
};

enum KYBRD_CTRL_STATS_MASK {
 
    KYBRD_CTRL_STATS_MASK_OUT_BUF   =   1,           //00000001
    KYBRD_CTRL_STATS_MASK_IN_BUF    =   2,           //00000010
    KYBRD_CTRL_STATS_MASK_SYSTEM    =   4,           //00000100
    KYBRD_CTRL_STATS_MASK_CMD_DATA  =   8,           //00001000
    KYBRD_CTRL_STATS_MASK_LOCKED    =   0x10,       //00010000
    KYBRD_CTRL_STATS_MASK_AUX_BUF   =   0x20,       //00100000
    KYBRD_CTRL_STATS_MASK_TIMEOUT   =   0x40,       //01000000
    KYBRD_CTRL_STATS_MASK_PARITY    =   0x80        //10000000
};

enum KYBRD_CTRL_CMDS 
{

    KYBRD_CTRL_CMD_READ             =    0x20,
    KYBRD_CTRL_CMD_WRITE            =    0x60,
    KYBRD_CTRL_CMD_SELF_TEST        =    0xAA,
    KYBRD_CTRL_CMD_INTERFACE_TEST   =    0xAB,
    KYBRD_CTRL_CMD_DISABLE          =    0xAD,
    KYBRD_CTRL_CMD_ENABLE           =    0xAE,
    KYBRD_CTRL_CMD_READ_IN_PORT     =    0xC0,
    KYBRD_CTRL_CMD_READ_OUT_PORT    =    0xD0,
    KYBRD_CTRL_CMD_WRITE_OUT_PORT   =    0xD1,
    KYBRD_CTRL_CMD_READ_TEST_INPUTS =    0xE0,
    KYBRD_CTRL_CMD_SYSTEM_RESET     =    0xFE,
    KYBRD_CTRL_CMD_MOUSE_DISABLE    =    0xA7,
    KYBRD_CTRL_CMD_MOUSE_ENABLE     =    0xA8,
    KYBRD_CTRL_CMD_MOUSE_PORT_TEST  =    0xA9,
    KYBRD_CTRL_CMD_MOUSE_WRITE      =    0xD4
};

// scan error codes
enum KYBRD_ERROR {

    KYBRD_ERR_BUF_OVERRUN           =   0,
    KYBRD_ERR_ID_RET                =   0x83AB,
    KYBRD_ERR_BAT                   =   0xAA,   //note: can also be L. shift key make code
    KYBRD_ERR_ECHO_RET              =   0xEE,
    KYBRD_ERR_ACK                   =   0xFA,
    KYBRD_ERR_BAT_FAILED            =   0xFC,
    KYBRD_ERR_DIAG_FAILED           =   0xFD,
    KYBRD_ERR_RESEND_CMD            =   0xFE,
    KYBRD_ERR_KEY                   =   0xFF
};


//sets a key to invalid after its use
#define     INVALID_KEY     0

/* KEYBOARD STRUCTURE */
typedef struct _kkybrd_data
{
    uint8_t __scan_code;
    uint32_t __kybrd_error;
    _bool __ctrl_key, __shift_key, __alt_key;
    _bool __num_lock, __scroll_lock, __caps_lock;
    _bool __kybrd_bat_res;
    _bool __kybrd_diag_res;
    _bool __kybrd_resend_res;
    _bool __kybrd_disable;

}_kybrd_data_t;

//--------------------------------------------------------
_kybrd_data_t _kybrd_data;
_kybrd_data_t *_kybrd_data_ptr = &_kybrd_data;
//--------------------------------------------------------


//============PRIVATE FUNCTIONS PROTOTYPES=======================
uint8_t kybrd_ctrl_read_status();
_void kybrd_ctrl_send_cmd(uint8_t);
uint8_t kybrd_enc_read_buf();
_void kybrd_enc_send_cmd(uint8_t);
PRIVATE _void kybrd_irq_handler(); 
//======================END======================================

//===========PUBLIC FUNCTIONS PROTOTYPES=========================
_void kybrd_disable();
_void kybrd_enable();
_void kybrd_install();
_bool kybrd_self_test ();
_void discard_last_key();
_bool kybrd_get_bat_res();
_bool kybrd_is_disabled();
_bool kybrd_check_resend();
_bool kybrd_get_bat_res ();
_void kybrd_reset_system();
_void kybrd_ignore_resend();
uint8_t kybrd_get_last_scan();
_bool kybrd_get_alt_key_status();
_bool kybrd_get_diagnostic_res ();
_bool kybrd_get_ctrl_key_status();
_bool kybrd_get_shift_key_status();
enum KEY_CODE kybrd_get_last_key();
_char kybrd_key_to_ascii(enum KEY_CODE);
_void kybrd_set_leds (_bool num, _bool caps, _bool scroll);

//----------------------------------------------------------------------------------------

//reads the data in the keyboard controller port(0x64)
uint8_t kybrd_ctrl_read_status()
{
    return inport_byte(KYBRD_CTRL_STATS_REG);
}

_void kybrd_ctrl_send_cmd(uint8_t cmd)
{
    //wait for the keyboard controller to be ready
    while(1)
    {
        if((kybrd_ctrl_read_status() & KYBRD_CTRL_STATS_MASK_IN_BUF) == 0) break;
    }
    
    outport_byte(KYBRD_CTRL_CMD_REG, cmd);
}

//reads the keyboard encoder input buffer
uint8_t kybrd_enc_read_buf()
{
    return inport_byte(KYBRD_ENCODER_INPUT_BUF);
}

//sends command to the keyboard encoder 
_void kybrd_enc_send_cmd(uint8_t cmd)
{
    //wait for the keyboard controller to be ready
    while(1)
    {
        if((kybrd_ctrl_read_status() & KYBRD_CTRL_STATS_MASK_IN_BUF) == 0) break;
    }
    
    outport_byte(KYBRD_ENCODER_CMD_REG, cmd);
}

PRIVATE _void kybrd_irq_handler()
{
    uint8_t _key_scan_code = 0;

    if(kybrd_ctrl_read_status() & KYBRD_CTRL_STATS_MASK_OUT_BUF)
    {
        _key_scan_code = kybrd_enc_read_buf();

        //_kybrd_data_ptr->__scan_code = _key_scan_code;

        if(_key_scan_code & KEY_RELEASED_CODE)   // key released
        {
            _key_scan_code -= KEY_RELEASED_CODE; // grab the key(real scan code key)

            uint32_t key = _kybrd_scancode_std[_key_scan_code];

            // only set special keys
            switch(key)
            {
                case KEY_LSHIFT:
                case KEY_RSHIFT:
                    _kybrd_data_ptr->__shift_key = false;
                    break;
                case KEY_LALT:
                case KEY_RALT:
                    _kybrd_data_ptr->__alt_key = false;
                    break;
                case KEY_LCTRL:
                case KEY_RCTRL:
                    _kybrd_data_ptr->__ctrl_key = false;
                    break;
            }
        }

        else
        {
            _kybrd_data_ptr->__scan_code = _key_scan_code;

            uint32_t key = _kybrd_scancode_std[_key_scan_code];

            switch(key)
            {
                case KEY_LSHIFT:
                case KEY_RSHIFT:
                    _kybrd_data_ptr->__shift_key = true;
                    break;
                case KEY_LALT:
                case KEY_RALT:
                    _kybrd_data_ptr->__alt_key = true;
                    break;
                case KEY_LCTRL:
                case KEY_RCTRL:
                    _kybrd_data_ptr->__ctrl_key = true;
                    break;
            }
        }
    }

}


_void kybrd_ignore_resend()
{
    _kybrd_data_ptr->__kybrd_resend_res = false;
}

_bool kybrd_check_resend()
{
    return _kybrd_data_ptr->__kybrd_resend_res;
}

_bool kybrd_get_diagnostic_res()
{
    return _kybrd_data_ptr->__kybrd_diag_res;
}

_bool kybrd_get_bat_res()
{
    return _kybrd_data_ptr->__kybrd_bat_res;
}

_bool kybrd_self_test()
{
    kybrd_ctrl_send_cmd(KYBRD_CTRL_CMD_SELF_TEST);

    //wait for output buffer to be full
    while (1)
        if (kybrd_ctrl_read_status () & KYBRD_CTRL_STATS_MASK_OUT_BUF)
            break;

    //if output buffer == 0x55, test passed
    return (kybrd_enc_read_buf () == 0x55) ? true : false;

}

uint8_t kybrd_get_last_scan() 
{
    return _kybrd_data_ptr->__scan_code;
}

//disables the keyboard
_void kybrd_disable() 
{
     kybrd_ctrl_send_cmd (KYBRD_CTRL_CMD_DISABLE);
     _kybrd_data_ptr->__kybrd_disable = true;
}

//enables the keyboard
_void kybrd_enable() 
{
    kybrd_ctrl_send_cmd(KYBRD_CTRL_CMD_ENABLE);
    _kybrd_data_ptr->__kybrd_disable = false;
}

//returns true if keyboard is disabled
_bool kybrd_is_disabled() 
{
    return _kybrd_data_ptr->__kybrd_disable;
}

//reset the system
_void kybrd_reset_system() 
{
    //writes 11111110 to the output port (sets reset system line low)
    kybrd_ctrl_send_cmd (KYBRD_CTRL_CMD_WRITE_OUT_PORT);
    kybrd_enc_send_cmd (0xfe);
}

_bool kybrd_get_ctrl_key_status(){ return _kybrd_data_ptr->__ctrl_key; }

_bool kybrd_get_shift_key_status(){ return _kybrd_data_ptr->__shift_key; }

bool kybrd_get_alt_key_status(){ return _kybrd_data_ptr->__alt_key; }

enum KEY_CODE kybrd_get_last_key()
{
    return (_kybrd_data_ptr->__scan_code != INVALID_KEY) ? ((enum KEY_CODE)_kybrd_scancode_std[_kybrd_data_ptr->__scan_code]) : KEY_UNKNOWN; 
}

_void discard_last_key()
{
    _kybrd_data_ptr->__scan_code = INVALID_KEY;
}

_char kybrd_key_to_ascii(enum KEY_CODE key_code)
{
}

/*  set/reset mode indicators consists of 2bytes: first is the command byte
 *  and second is the data byte consisting of led to set on.
 *  bit 0 ==> scroll lock(0:off, 1:on)
 *  bit 1 ==> num lock(0:off, 1:on)
 *  bit 2 ==> caps lock(0:off, 1:on)
 */
_void kybrd_set_leds(_bool num, _bool caps, _bool scroll)
{
    uint8_t data = 0;
    
    data |= ((scroll == true) ? 1 : 0);
    data |= ((num == true) ? 0x2 : 0);
    data |= ((caps == true) ? 0x4 : 0);
    
    kybrd_enc_send_cmd(KYBRD_ENC_CMD_SET_LED);
    kybrd_enc_send_cmd(data);
}

//prepares the keyboard driver!!
_void kybrd_install()
{
    _kybrd_data_ptr->__scan_code = 0;
    _kybrd_data_ptr->__kybrd_error = 0;
    _kybrd_data_ptr->__ctrl_key = false;
    _kybrd_data_ptr->__shift_key = false;
    _kybrd_data_ptr->__alt_key = false;
    _kybrd_data_ptr->__num_lock = false;
    _kybrd_data_ptr->__scroll_lock = false;
    _kybrd_data_ptr->__caps_lock = false;
    _kybrd_data_ptr->__kybrd_bat_res = true;
    _kybrd_data_ptr->__kybrd_diag_res = false;
    _kybrd_data_ptr->__kybrd_resend_res = false;
    _kybrd_data_ptr->__kybrd_disable = false;

    //installs the keyboard to IRQ1(33)
    register_interrupt_handlers(IRQ1, kybrd_irq_handler);

    kybrd_set_leds(false, false, false);

}
//======================END===========================================
