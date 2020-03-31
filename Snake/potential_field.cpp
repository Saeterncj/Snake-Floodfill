/// C file layout

/******************************************************************************
*
* @file     potential_field.cpp
* @brief    Bit manipulation functions
* @version  V1.00
* @date     march 19,2020
*
* @note
*
******************************************************************************/

/*----------------------------------------------------------------------------
*
* Place #include files required to compile this source file here.
*
*----------------------------------------------------------------------------*/
#include "potential_field.h"
/*----------------------------------------------------------------------------
*
* Place function prototypes that will be used only by this file here.
* This section need only include "forward referenced" functions.
*
*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------
*
* Define global variables that will be used by both this source file
* and by other source files here.
*
*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
*
* Place #define constants and macros that will be used only by this
* source file here.
*
*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
*
* Place typedefs, structs, unions, and enums that will be used only
* by this source file here.
*
*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
*
* Place static variables that will be used only by this file here.
*
*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
*
* Place function bodies here.
*
*----------------------------------------------------------------------------*/
void potential_field() {
	stRowColumn force_attractive,force_repulsive,total_force;
	for (int i(0); i < 2;i++) {
		force_attractive.x = fruit.x - snake[0].x;
		force_attractive.y = fruit.y - snake[0].y;
		force_repulsive.x = snake[1].x - snake[0].x;
		force_repulsive.y = snake[1].y - snake[0].y;
		//force_repulsive.x =0;
		//force_repulsive.y =0;
	}
	total_force.x = force_attractive.x - force_repulsive.x;
	total_force.y = force_attractive.y - force_repulsive.y;

	std::cout << total_force.x << ", " << total_force.y << "\n";
	if (total_force.x > 0 && total_force.x >= abs(total_force.y)) {
		if (eCurrDir != eLeft){
			eDir = eRight;
			eCurrDir = eRight;
		}
		else {
			eDir = eUp;
			eCurrDir = eUp;
			std::cout << eDir << "Snake Couldnt make a decision\n";
		}
	}
	else if (total_force.x < 0 && abs(total_force.x) >= abs(total_force.y) ) {
		if (eCurrDir != eRight) {
			eDir = eLeft;
			eCurrDir = eLeft;
		}
		else {
			eDir = eUp;
			eCurrDir = eUp;
			std::cout << eDir << "Snake Couldnt make a decision\n";
		}
		
	}
	else if (total_force.y > 0 && abs(total_force.y) > abs(total_force.x) ) {
		if (eCurrDir != eUp) {
			eDir = eDown;
			eCurrDir = eDown;
		}
		else {
			eDir = eRight;
			eCurrDir = eRight;
			std::cout << eDir << "Snake Couldnt make a decision\n";
		}
		
	}
	else if (total_force.y < 0 && abs(total_force.y) > abs(total_force.x) ) {
		if (eCurrDir != eDown) {
			eDir = eUp;
			eCurrDir = eUp;
		}
		else {
			eDir = eLeft;
			eCurrDir = eLeft;
			std::cout << eDir << "Snake Couldnt make a decision\n";
		}
		
	}
	else {

		/*std::cout << eDir << "Snake Couldnt make a decision\n";*/
	}
}