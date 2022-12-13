//...............................................
//...............................................
//Initiated on Friday, the 26th of July, 2019
//      @ 10:40PM
//by the OS creator, Odey john Ebinyi.
//...............................................
//...............................................

#ifndef __QUICK_SORT_H__
#define __QUICK_SORT_H__

#include <stdint.h>
#include <lib/config.h>

// A struct for the quick sort algorithm
typedef struct quick_sort
{
	int small_index;
	int low_index;
	int high_index;
	int pivot;
	int len;
}_quick_sort;

//======================================================
_extern _void __quick_sort(int [], int, int);
_extern uint32_t __partition(int [], int, int);
_extern _void __swap(uint32_t *, uint32_t *);
//======================================================

#endif