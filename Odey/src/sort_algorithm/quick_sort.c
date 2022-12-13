#include <sort_algthm/quick_sort.h>

// variables
_quick_sort _quick_sort_t;

//===================== PUBLIC FUNCTIONS ======================
_void __quick_sort(int [], int, int);
uint32_t __partition(int [], int, int);
_void __swap(uint32_t *, uint32_t *);
//=============================================================

//===================== PUBLIC FUNCTIONS IMPLEMENTATION ==============================
_void __quick_sort(int _quick_sort_arr[], int low_index, int high_index)
{
	if(low_index < high_index)
	{
		_quick_sort_t->small_index = __partition(_quick_sort_arr, low_index, high_index);

		__quick_sort(_quick_sort_arr, low_index, (high_index - 1));
		__quick_sort(_quick_sort_arr, (high_index + 1), );
	}
}

uint32_t __partition(int _quick_sort_arr, int low_index, int high_index)
{

}

_void __swap(uint32_t *first_var, uint32_t *second_var)
{
	int temp_var = *first_var;
	*first_var = *second_var;
	*second_var = temp_var;
}
//====================================================================================
