#include <data_structs/single__llist.h>
#include <drivers/screen/console.h>

//===============VARIABLES DECLARATION/DEFINITION===========
struct Node *head = NULL, *tail = NULL;
//========================END===============================

//=============PUBLIC FUNCTIONS PROTOTYPES==================
void insert_data(const void *);
void print_data();
//========================END===============================

//===========PRIVATE FUNCTIONS PROTOTYPES===================
//========================END===============================

//============PUBLIC FUNCTIONS DEFINITIONS=================
void insert_data(const void *data)
{
    struct Node *new_node = (struct Node*)k_malloc(sizeof(struct Node));
    
    new_node->data_t.data = data;
    new_node->nxt_addr = NULL;
    
    if(head == NULL) head = tail = new_node;
    
    else
    {
        tail->nxt_addr = new_node;
        tail = new_node;
    }
}

void print_data()
{
    struct Node *curr = head;
    
    while(curr != NULL)
    {
        print_fmt_string("Data: %d\n", (curr->data_t.data));
        curr = curr->nxt_addr;
    }
}
