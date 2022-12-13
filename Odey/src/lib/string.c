#include <lib/string.h>
#include <lib/const.h>
#include <lib/config.h>

//============PUBLIC FUNCTIONS PROTOTYPES=======================
_void_star mem_set(_void_star, int8_t, uint32_t);
uint32_t string_length(const _char*);
_char* str_cpy(_char *, const _char *);
int str_cmp(const _char *, const _char *);
_void_star mem_cpy(_void_star, const _void_star, uint32_t); 
_char *stripper(_char *);
//==========================END=================================

//===========PUBLIC FUNCTIONS DEFINITIONS=======================
_void_star mem_set(_void_star dest, int8_t value, uint32_t count)
{
    int8_t *dest_ptr = (int8_t*)dest;
                                                                
    for(size_t index = 0; index < count; index++)
        dest_ptr[index] = value;
    
    return (_void_star)dest;
    /*char *temp = dest;
    for(;count != 0; count--) *temp++ = value;
    return dest;*/
}

uint32_t string_length(const _char *str)
{
    uint32_t length_of_string = 0;
    
    while((*str++) != '\0') length_of_string++;
    
    return length_of_string;
}


_char *str_cpy(_char *s1, const _char *s2)
{
    _char *s1_p = s1;
    while ((*s1++ = *s2++));
    return s1_p;
}

/*this function strips white space off the beginning 
 *of a string only
 */
_char *stripper(_char *str)
{
    while(*str)
    {
        //is the first and subsequent chars of 'str'
        //a blank space(' ') ?
        if(*str == 0x20)
        {
            *str++;
            continue;
        }

        else break;
    }

    return str;
}

int str_cmp (const _char* str1, const _char* str2) 
{
	int res=0;
	while (!(res = *(unsigned char*)str1 - *(unsigned char*)str2) && *str2)
		++str1, ++str2;

	if (res < 0)
		res = -1;
	if (res > 0)
		res = 1;
    return res;
}

_void_star mem_cpy(_void_star dest, const _void_star src, uint32_t len)
{
    int8_t *dest_ptr = (int8_t*)dest;
    const int8_t *src_ptr = (const int8_t*)src;
    
    for(size_t index = 0; index < len; index++)
        dest_ptr[index] = src_ptr[index];
    
    return dest_ptr;
}


//this function converts an int to a char; 
_void itoa(unsigned num, unsigned base, _char *buffer)
{
    _char buffer_chars[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
    _char temp_buffer[32];
    
    int index_pos = 0;
    int index_pos2 = 0;
    int top = 0;
    
    if(num == 0 || base > HEXADECIMAL_BASE)
    {
        buffer[0] = '0';
        buffer[1] = '\0';
        
        return;
    }
    
    while(num != 0)
    {
        temp_buffer[index_pos] = buffer_chars[num % base];
        index_pos++;
        num /= base;
    }
    
    top = index_pos--;
    
    for(index_pos2 = 0; index_pos2 < top; index_pos--,index_pos2++)
    {
        buffer[index_pos2] = temp_buffer[index_pos];
    }

    buffer[index_pos2] = 0;
}

//this function converts an int to a string
_void itoa_s(int num, unsigned base, _char *buffer)
{
    if(base > HEXADECIMAL_BASE)
        return;
    if(num < 0)
    {
        *buffer++ = '-';
        num *= -1;
    }
    itoa(num, base, buffer);
}

//==============================END==========================================
