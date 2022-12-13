#include "k_panic.h"
#include <lib/const.h>

extern void __lock_int();
extern void print_string(const char*);
extern void print_char(const char);

//====================PUBLIC FUNCTIONS PROTOTYPES====================
int kernel_panic(const char*, ...);
//==========================END======================================


static char* sick_pc = " \
                               _______      \n\
                               |.-----.|    \n\
                               ||x . x||    \n\
                               ||_.-._||    \n\
                               `--)-(--`    \n\
                              __[=== o]___  \n\
                             |:::::::::::|\\ \n\
                             `-=========-`()\n\
                                  ODEY   \n\n";



//================ PUBLIC FUNCTIONS DEFINITIONS======================
int kernel_panic(const char *str, ...)
{
    if(!str) return 0;
     
    __lock_int();
    
    va_list args;
    va_start (args, str);
    va_end(args);
    
    print_string(sick_pc);
    
    uint32_t index = 0;
    
    for(index = 0; index < string_length(str); index++)
    {
        switch(str[index])
        {
            case '%':
                    switch(str[index + 1])
                    {
                        case 'c':{
                            char chr = va_arg (args, char);
                            print_char(chr);
                            index++;
                            break;
                        }
                        
                        case 's':{
                            char *c = va_arg (args, char*);
                            char s[64];
                            str_cpy(s, c);
                            print_string(s);
                            index++;
                            break;
                        }
                        case 'd':
                        case 'i':{
                            int decimal_num = va_arg (args, int);
                            char decimal_num_buffer[32] = {0};
                            
                            itoa_s(decimal_num, DECIMAL_BASE, decimal_num_buffer);
                            print_string(decimal_num_buffer);
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

//============================END=====================================
