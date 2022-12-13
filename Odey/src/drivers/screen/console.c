#include <lib/string.h>
#include <lib/const.h>
#include <lib/system.h>
#include <lib/print_string.h>
#include <drivers/screen/console.h>
#include <drivers/keyboard/keyboard.h>

//functions defined external to this file
_extern _bool clear_tty();
_extern _void timer_wait(int);

//=======================================================
vga_t vga_buf_t;
vga_t *vga_buf = &vga_buf_t;

//this variable declarations holds the cursor's positions
//in the x and y axis.
uint8_t cursor_x_axis = 0;
uint8_t cursor_y_axis = 0;

PRIVATE _bool boot_up_screen = false;
//================================================

//============================PRIVATE FUNCTIONS PROTOTYPES=====================================
PRIVATE uint16_t set_disp(const enum VGA_COLORS, const enum VGA_COLORS, uint8_t, bool);
PRIVATE _void init_vga(vga_t **);
//======================================END=====================================================

//============================PUBLIC EXTERN FUNCTIONS PROTOTYPES=======================================
_void update_screen_cursor(uint8_t, uint8_t);
_void init_terminal();
_void enable_cursor(uint8_t, uint8_t);
_void disable_cursor();
_void set_color(const enum VGA_COLORS, const enum VGA_COLORS);
_void set_bg(const enum VGA_COLORS);
_void set_fg(const enum VGA_COLORS);
_void clear_screen(uint8_t, uint8_t, bool);
_void init_cls(uint8_t, uint8_t);
_void update_cursor(uint8_t, uint8_t);
_void scroll_screen();
int get_x();
int get_y();
_void bootup_squares();
_void get_xy(unsigned*, unsigned*);
_void goto_xy(unsigned, unsigned);
_void draw_console_borders();
//=====================================END=======================================================



//=========================PUBLIC FUNCTIONS DEFINITIONS=========================================
//this function moves the CRT cursor to a specified location through the 0x3D4(index register)
//and the 0x3D5(data register). 
//The data register(0x3D4) receives an argument (0xE) or 14 in decimal telling the VGA board
//we are setting the HIGH CURSOR byte and an argument of (0xF) or 15 in decimal telling the
//VGA board we are setting the LOW CURSOR byte.
//The index register(0x3D5) receives an argument based on the 0x3D4 argument, telling it to 
//either send the LOW_CURSOR or HIGH CURSOR byte.
_void update_screen_cursor(const uint8_t x_axis_position, const uint8_t y_axis_position)
{
    cursor_x_axis = x_axis_position;
    cursor_y_axis = y_axis_position;
    
    uint16_t cursor_location = ((SCREEN_WIDTH * cursor_y_axis) + cursor_x_axis);
    
    outport_byte(CRTC_INDEX_REGISTER, 14);                  // Tell the VGA board we are setting the high cursor byte.
    outport_byte(CRTC_DATA_REGISTER, cursor_location >> 8); // Send the high cursor byte.
    
    outport_byte(CRTC_INDEX_REGISTER, 15);                  // Tell the VGA board we are setting the low cursor byte.
    outport_byte(CRTC_DATA_REGISTER, cursor_location);      // Send the low cursor byte.
}

PRIVATE _void init_vga(vga_t **vga_b)
{
    (*vga_b)->vga_mem_address = (uint16_t*)I86_VGA_MEM_ADDRESS;
    (*vga_b)->screen_width = SCREEN_WIDTH;
    (*vga_b)->screen_height = SCREEN_HEIGHT;
    (*vga_b)->vga_bg_color = BLACK;
    (*vga_b)->vga_fg_color = WHITE;

    disable_cursor();
}

//use_vga_col_var: should it use "vga_buf->vga_bg_color & vga_buf->vga_fg_color"?
//or declare a normal local or automatic vga variable!
//REASONS: setting a display like the "terminal: odey", using the vga variables,
//         sets the whole screen to LIGHT_GREY background instead of BLACK background 
//         but a local vga variable does not!
PRIVATE uint16_t set_disp(const enum VGA_COLORS bg_col, const enum VGA_COLORS fg_col, uint8_t character, _bool use_vga_col_var)
{
    uint16_t attribute = 0;

    if(use_vga_col_var) 
    {
        vga_buf->vga_bg_color = bg_col;
        vga_buf->vga_fg_color = fg_col;

        uint8_t attribute_byte = ((vga_buf->vga_fg_color & 0x0F) | (vga_buf->vga_bg_color << 4));
        attribute = (character | (attribute_byte << 8));
    }

    else
    { 
        uint8_t attribute_byte = ((fg_col & 0x0F) | (bg_col << 4));
        attribute = (character | (attribute_byte << 8));   
    }

    return attribute;
}
//====================================END============================================================

//==========================PUBLIC EXTERN FUNCTIONS DEFINITIONS======================================
_void init_terminal()
{
    init_vga(&vga_buf);
}

//enables the cursor
_void enable_cursor(uint8_t cursor_start, uint8_t cursor_end)
{
    outport_byte(CRTC_INDEX_REGISTER, 0x0A);
    outport_byte(CRTC_DATA_REGISTER, (inport_byte(CRTC_DATA_REGISTER) & 0xC0) | cursor_start);
 
    outport_byte(CRTC_INDEX_REGISTER, 0x0B);
    outport_byte(CRTC_DATA_REGISTER, (inport_byte(CRTC_DATA_REGISTER) & 0xE0) | cursor_end);
}

//disables the cursor
_void disable_cursor()
{
    outport_byte(CRTC_INDEX_REGISTER, 0x0A);
    outport_byte(CRTC_DATA_REGISTER, 0x20);
}

_void set_color(const enum VGA_COLORS bg_color, const enum VGA_COLORS fg_color)
{
    vga_buf->vga_bg_color = bg_color; 
    vga_buf->vga_fg_color = fg_color;
}

_void set_bg(const enum VGA_COLORS bg_color)
{
    vga_buf->vga_bg_color = bg_color;
}

_void set_fg(const enum VGA_COLORS fg_color)
{
    vga_buf->vga_fg_color = fg_color;
}

_void init_cls(uint8_t x, uint8_t y)
{
    clear_screen(x,y, false);
}

_void clear_screen(uint8_t x_axis_position, uint8_t y_axis_position, _bool show_terminal)
{
    int index = 0; 
    boot_up_screen = show_terminal;
//------------------------------------------------------------------------------------
//TERMINAL MODE SECTION
    //are we in boot-up screen? and is the exit command sent, to kill the terminal?
    if(boot_up_screen != true && !(clear_tty()))
    {
        index = 80;    

        //draws the upper border line with dashes
        for(int i = 0; i < SCREEN_WIDTH; ++i)
        {
            vga_buf->vga_mem_address[i] = set_disp(LIGHT_GREY, BLACK, 0x20, false);
        }
        
        update_cursor(30, 0);
        set_color(LIGHT_GREY, BLACK);
        print_string("Terminal");
        set_fg(WHITE);  //sets the cursor color
    }   
//--------------------------------------------------------------------------------------

    //clears the screen from x-axis @ 80 down
    for(; index < ((vga_buf->screen_width) * (vga_buf->screen_height)); ++index)
    {
        vga_buf->vga_mem_address[index] = set_disp(BLACK/*(vga_buf->vga_bg_color)*/, (vga_buf->vga_fg_color), 0x20, true);  
    }
        
    cursor_x_axis = x_axis_position; 
    cursor_y_axis = y_axis_position;
    
    update_screen_cursor(cursor_x_axis, cursor_y_axis);
    
    //boot_up_screen = false;
}

_void update_cursor(uint8_t x, uint8_t y)
{
    update_screen_cursor(x, y);
}

PRIVATE _void clear_screen_for_text(uint8_t x, uint8_t y, uint8_t start_string_p)
{
    _bool is_y = false;
    
    for(int index = 0; index < (x * y); index++)
    {
        vga_buf->vga_mem_address[index] = set_disp((vga_buf->vga_bg_color), (vga_buf->vga_fg_color), 0x20, true);
    }
    
    //clears the upper part that is before the string display if y != 0
    if(!(is_y = (y == 1 ? true : false))) 
    {
        for(int index = 0; index < (x * (y-1)); index++)
        {
            vga_buf->vga_mem_address[index] = ' ';
        }
    }
    
    x = start_string_p;
    
    cursor_x_axis = x;
    cursor_y_axis = (y == 0 ? y : (--y));
    
    update_screen_cursor(cursor_x_axis, cursor_y_axis);
}

_void console_put_string(uint8_t x, uint8_t y, uint8_t start_string_p, char *str, const enum VGA_COLORS bg, const enum VGA_COLORS fg)
{
    set_color(bg, fg);
    
    if(y == 0) y = 1;
    
    clear_screen_for_text(x,y,start_string_p);
    print_string(str);
}

_void scroll_screen()
{
    // Row 25 is the end, this means we need to scroll up
    if(cursor_y_axis >= SCREEN_HEIGHT)
    {
        // Move the current text chunk that makes up the screen
        // back in the buffer by a line
        for (int i = SCREEN_WIDTH; i < ((SCREEN_HEIGHT - 1) * SCREEN_WIDTH); i++)
        {
            vga_buf->vga_mem_address[i] = vga_buf->vga_mem_address[i + SCREEN_WIDTH];
        }

        // The last line should now be blank. Do this by writing
        // 80 spaces to it.
        for (int i = ((SCREEN_HEIGHT - 1) * SCREEN_WIDTH); i < (SCREEN_HEIGHT * SCREEN_WIDTH); i++)
        {
            vga_buf->vga_mem_address[i] = set_disp((vga_buf->vga_bg_color), (vga_buf->vga_fg_color), 0x20, true);
        }
        // The cursor should now be on the last line.
        cursor_y_axis = (SCREEN_HEIGHT - 1);
    }
}

_void get_xy(unsigned* x, unsigned* y) {

	if (x==0 || y==0)
		return;

	*x = cursor_x_axis;
	*y = cursor_y_axis;
}

_void goto_xy(unsigned x, unsigned y)
{
    
	if (cursor_x_axis <= 80)
	    cursor_x_axis = x;

	if (cursor_y_axis <= 25)
	    cursor_y_axis = y;

	//update hardware cursor to new position
	update_screen_cursor(cursor_x_axis, cursor_y_axis);
}

_void bootup_squares()
{
       int v_brk = 0, y = 12, x = 11, z = 13; 

       while(v_brk < 6)
       {
            for(; x < z; ++x)
            {
                vga_buf->vga_mem_address[(y*(vga_buf->screen_width))+x] = set_disp(BROWN, RED, 0x20, true);
            }

            //sleep for about 11ms
            timer_wait(200);
            x += 8;
            z += 10; 
            ++v_brk;
        }
}

_void draw_console_borders()
{   
    for(size_t y_axis = 0; y_axis < 1; ++y_axis)
    {
        for(size_t x_axis = 0; x_axis < SCREEN_WIDTH; ++x_axis)
        {
            vga_buf->vga_mem_address[x_axis] = set_disp(LIGHT_GREY, LIGHT_GREY, '*', true); 
        }
    }
}
//========================================END=========================================================
