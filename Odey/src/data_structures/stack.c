#include <data_structures/stack.h>

//====================== PUBLIC FUNCTIONS ===================
_void init_stack_struct();
_void push(_void_star data);
uint32_t peek();
uint32_t pop();
_bool is_stack_empty();
_bool is_stack_full();
_void show_stack_contents();
//===========================================================

//=============================================================
// global variables to be used on the stack data structures
struct _stack stack_t;
struct _stack *stack_ptr = &stack_t;
//==============================================================

_void init_stack_struct()
{
    for(int index = 0; index < 4; ++index)
    {
            stack_ptr->stack_arr[index] = 0;
    }

    stack_ptr->top = EMPTY_STACK;
}

_void push(_void_star data)
{
	if(!is_stack_full())  stack_ptr->stack_arr[++stack_ptr->top] = data;
	else print_string("ERROR: Stack Filled Up!");
}

uint32_t peek()
{
	if(!is_stack_empty()) return stack_ptr->stack_arr[stack_ptr->top];
}

uint32_t pop()
{
	if(!is_stack_empty())  return stack_ptr->stack_arr[stack_ptr->top--];
	else print_string("ERROR: Stack is Empty!");
}

_bool is_stack_empty()
{
	return (stack_ptr->top == EMPTY_STACK);
}

_bool is_stack_full()
{
	return (stack_ptr->top == (STACK_SIZE - 1));
}

_void show_stack_contents()
{
    print_string("Stack Contents: \n");

    for(int index = 0; index < 4; ++index)
    {
        uint32_t val = pop();

		#ifdef __CHARACTERS__
        	print_fmt_string("==> %c\n", val);
        #else
        	print_fmt_string("==> %d\n", val);
        #endif
    }
}



