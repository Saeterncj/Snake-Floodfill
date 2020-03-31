#pragma once
// Header files
#ifndef floodfill_h_
#define floodfill_h_
/******************************************************************************
*
* @file     floodfill.h
* @brief
* @version  V1.00
* @date     march 20, 2020
*
* @note
*
******************************************************************************/

/*----------------------------------------------------------------------------
*
* Include any additional header files that are needed to compile this
* header file here.
*
*----------------------------------------------------------------------------*/
#include "system.h"
/*-----------------------------------------------------------------------------
Meaningful name that describes what is about to follow
-----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------
*
* Place #define constants and macros that are required for this header
* file or that need to be seen by more than one source file here.
*
*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
*
* Place typedefs, structs, unions, and enums that need to be seen by
* multiple source files here.
*
*----------------------------------------------------------------------------*/
enum eFloodFillStates {
	eInitializeValues,
	eMakeDecision, 
};
/*----------------------------------------------------------------------------
*
* Place global variables that are used by multiple source files here.
*
*----------------------------------------------------------------------------*/
// extern 
extern eFloodFillStates eFF_State;
/*----------------------------------------------------------------------------
*
* Place function prototypes that need to be seen by multiple source files here.
*
*----------------------------------------------------------------------------*/

// ReturnedDataType functionName(ParametersDataType)
void floodfill();
void go_top_left();
void prepare();
/*----------------------------------------------------------------------------
*
* End of file.
*
*----------------------------------------------------------------------------*/
#endif