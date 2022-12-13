#include <lib/odey.h>
#include <lib/print_string.h>
#include <drivers/screen/terminal.h>

//====================VARIABLES============================
//bool leave = false;
PRIVATE _bool clear_all = false;
//=======================END===============================


//===================PUBLIC FUNCTIONS============================
_char get_ch(); //gets last keyboard key pressed.
_void cmds(); //displays lists of terminal commands.
_void run(); //init the terminal
_bool clear_tty();
//========================END====================================

//==================PRIVATE FUNCTIONS============================
PRIVATE _void msg_init_tty(); //initializes the terminal screen();
PRIVATE _bool parse_cmds(char *);
PRIVATE _void t_cmd();    //current terminal command(s)
PRIVATE enum KEY_CODE get_key();
//=========================END===================================

//================PRIVATE FUNCTIONS IMPLEMENTATION==================
PRIVATE _void msg_init_tty()
{ 
    set_fg(LIGHT_GREY);
    print_char('>'); 
}

PRIVATE _bool parse_cmds(_char *cmd_buf)
{
    //Return key is not buffered and so does cmd_buf contains '\0'?
    if(*cmd_buf != '\0')
    {

        if(str_cmp(cmd_buf, "help") == 0) cmds();
        
        else if(str_cmp(cmd_buf, "cls") == 0) clear_screen(0,1,false);
        
        else if(str_cmp(cmd_buf, "hello") == 0) os();

        else if(str_cmp(cmd_buf, "--version") == 0) os_version();
        
        else if(str_cmp(cmd_buf, "exit") == 0) return true; 
    
        else
        {
            set_fg(RED);
            print_err("Unknown Command\n"); 
        }
    }
    else{ ; } //do nothing on a 'return key' press
    
    return false;
}

PRIVATE _void t_cmd()
{
    msg_init_tty();

    
}

PRIVATE enum KEY_CODE get_key()
{
}

//=============================END=================================



//================PUBLIC FUNCTIONS IMPLEMENTATION==================
_char get_ch()
{
}

_void cmds()
{
    set_fg(BROWN);
    print_string("+-----------ODEY TERMINAL COMMANDS---------------+\n");
    print_string("hello       ==>   OS details\n");
    print_string("cls         ==>   Clears The Console Screen\n");
    print_string("exit        ==>   Exits The Console Screen\n");
    print_string("--version   ==>   Displays OS Latest Version\n");
}

_void run()
{
    set_color(BLACK, BLACK);
    clear_screen(0,0,true);
    bootup_squares();
    
    set_color(BLACK, LIGHT_GREY);
    clear_screen(0,1,false);
    enable_cursor(11,11);
    t_cmd();
}

_bool clear_tty()
{
    return clear_all;
}
//=============================END=================================================
