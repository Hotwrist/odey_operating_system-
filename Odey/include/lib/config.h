#ifndef		__CONFIG_H__
#define     __CONFIG_H__

#include <stdbool.h>

//=============== ODEY'S DETAILS =========================
#define			KERNEL_VERSION			"1.0"
#define			_VERSION				"1.0"	
#define      	BUILT_TIME				"12:20PM"
#define         BUILT_DATE				"Thursday July 11, 2019"   
//===============================================

//==========DATA TYPES/LINKAGE/MODIFIER===========
#define  		PRIVATE					static
#define         _char					char
#define			_bool					bool
#define    	    _void 					void
#define         _void_star			    void *
#define         _extern                 extern
#define         _volatile				volatile
//================================================

//---------------------- COMPILER SESSION --------------------------------------
// this section contains compiler related built_in tools for proper optimization 
// of the OS codes.
//========================= GCC RELATED =======================================
#define 		BUILTIN_EXPECT(exp, b) 			__builtin_expect((exp), (b))
#define			__type_of__						__typeof__
//=============================================================================

//-------------------------------------------------------------------------------

//================== FOR DATA STRUCTURE USAGE / SORTING ALGORITHMS ===================================
#define __CHARACTERS__
#define __INTEGERS__
#define __STRINGS__

//=====================================================================================================

#endif
