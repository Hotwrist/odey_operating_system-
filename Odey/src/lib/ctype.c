#include <lib/ctype.h>

int is_alpha(int c)
{
    return ((is_lower(c) || is_upper(c)) ? 1 : 0);
}

int is_ascii(int c)
{
    return (c >= 0 && c <= 0x7F);
}

int is_alnum(int c)
{
    return ((is_digit(c) || is_alpha(c)) ? 1 : 0);
}

/*int is_punct(int c)
{
  //implement later  
}
*/
int is_space(int c)
{
    return ( c == '\t' || c == '\n' || c == 0x20 );
}

/*int is_print(int c)
{
    
}
*/
int is_digit(int c)
{
    return ( c >= '0' && c <= '9'); 
}

int is_hex_digit(int c)
{
    return (((is_digit(c) || (c >= 'a' && c <= 'f') || (c >= 'A' && c <= 'F'))) ? 1 : 0);
}

int is_lower(int c)
{
    return ((c >= 'a' && c <= 'z') ? 1 : 0);
}

int is_upper(int c)
{
    return ((c >= 'A' && c <= 'Z') ? 1 : 0);
}

int to_upper(int c)
{
    if(is_lower(c))
        return (c - ('a' - 'A'));
    else
        return c;
}

int to_lower(int c)
{
    if(is_upper(c))
        return (c + ('a' - 'A'));
    else
        return c;
}
