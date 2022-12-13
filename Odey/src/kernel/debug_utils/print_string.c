#include <lib/print_string.h>

_extern uint8_t cursor_x_axis;
_extern uint8_t cursor_y_axis;
_extern _void scroll_screen();
_extern _void update_screen_cursor(const uint8_t , const uint8_t);

//==============PUBLIC FUNCTIONS=====================
_void print_char(const _char);
_void print_string(const _char*);
int print_fmt_string(const _char *, ...);
//===================================================

_extern vga_t *vga_buf;
_extern _void update_screen_cursor(uint8_t, uint8_t);

//=============PUBLIC FUNCTION IMPLEMENTATIONS====================
_void print_char(const _char ch)
{
    
    enum VGA_COLORS bg_color = vga_buf->vga_bg_color;
    enum VGA_COLORS fg_color = vga_buf->vga_fg_color;
    
    uint8_t attribute_byte = ((bg_color << 4) | (fg_color & 0x0F));
    uint16_t attribute = ((attribute_byte << 8));
    
    uint16_t *vga_location;
    
    switch(ch)
    {
        case '\n':
            cursor_x_axis = 0;
            ++cursor_y_axis;
            break;
        case '\r':
            cursor_x_axis = 0;
            break;
        default:
            vga_location = (vga_buf->vga_mem_address) + ((SCREEN_WIDTH * cursor_y_axis) + cursor_x_axis);
            *vga_location = (ch | attribute);
            ++cursor_x_axis;
            break;
    }
    
    if(cursor_x_axis >= SCREEN_WIDTH)
    {
        cursor_y_axis++;
        cursor_x_axis = 0;
    }
    
    if(cursor_y_axis >= SCREEN_HEIGHT)
        scroll_screen();
  
    update_screen_cursor(cursor_x_axis, cursor_y_axis); 
}


_void print_string(const _char *str)
{
    while( *str != '\0') print_char(*str++);
}

int print_fmt_string(const _char *str, ...)
{
    if(!str) return 0;
    
    va_list args;
    va_start (args, str);

    uint32_t index = 0;
    
    for(index = 0; index < string_length(str); index++)
    {
        switch(str[index])
        {
            case '%':
                    switch(str[index + 1])
                    {
                        case 'c':{
                            _char chr = va_arg (args, char);
                            print_char(chr);
                            index++;
                            break;
                        }
                        
                        case 's':{
                            _char *c = va_arg (args, char*);
                            _char s[64];
                            str_cpy(s, c);
                            print_string(s);
                            index++;
                            break;
                        }
                        
                        case 'd':
                        case 'i':{
                            int decimal_num = va_arg (args, int);
                            _char decimal_num_buffer[32] = {0};
                            
                            itoa_s(decimal_num, DECIMAL_BASE, decimal_num_buffer);
                            print_string(decimal_num_buffer);
                            index++;
                            break;
                        }
                        
                        case 'X':
                        case 'x':{
                            int hex_num = va_arg (args, int);
                            _char hex_num_buffer[32] = {0};
                            
                            itoa_s(hex_num, HEXADECIMAL_BASE, hex_num_buffer);
                            print_string(hex_num_buffer);
                            index++;
                            break;
                        }
                        
                        default:
                            va_end (args);
                            return 1;
                    }
                break;
              default:
                    print_char(str[index]);
                    break;
        }
    }
    
    va_end(args);
    return index;
    
}



//================================================================