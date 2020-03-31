#pragma once
#ifndef system_h_
#define system_h_
/******************************************************************************
*
* @file     system.h
* @brief	to include all header files for main
* @date     March 19, 2020
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
#include <SFML/Graphics.hpp>
#include <time.h>
#include <iostream>
#include <stack>
#include <iomanip> 

#include "potential_field.h"
#include "floodfill.h"

/*-----------------------------------------------------------------------------
Meaningful name that describes what is about to follow
-----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------
*
* Place #define constants and macros that are required for this header
* file or that need to be seen by more than one source file here.
*
*----------------------------------------------------------------------------*/
#define SNAKE_MAX	240
#define NUM_PIXEL	16 // each block is 16x16 pixel
#define WIDTH_MAX 16
#define HEIGHT_MAX 16

/*----------------------------------------------------------------------------
*
* Place typedefs, structs, unions, and enums that need to be seen by
* multiple source files here.
*
*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
*
* Place global variables that are used by multiple source files here.
*
*----------------------------------------------------------------------------*/
struct stRowColumn
{
	int x, y;
};

enum eDirection {
	eDown = 1,
	eLeft = 2,
	eRight = 4,
	eUp = 8,
};
enum eSnakeDecisionState {
	eFloodfill,
	eGoTopLeft,
	ePrepare,
};
extern stRowColumn snake[SNAKE_MAX];
extern int sizeSnake;
extern stRowColumn fruit;
extern eDirection eDir;
extern eDirection eCurrDir;
extern eSnakeDecisionState eSnakeState;
extern int field[HEIGHT_MAX][WIDTH_MAX];
/*----------------------------------------------------------------------------
*
* Place function prototypes that need to be seen by multiple source files here.
*
*----------------------------------------------------------------------------*/

// ReturnedDataType functionName(ParametersDataType)
/*----------------------------------------------------------------------------
*
* End of file.
*
*----------------------------------------------------------------------------*/
#endif