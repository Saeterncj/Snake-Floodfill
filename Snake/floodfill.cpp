/// C file layout

/******************************************************************************
*
* @file     shared_data.c
* @brief    Bit manipulation functions
* @version  V1.00
* @date     8, December 2018
*
* @note
*
******************************************************************************/

/*----------------------------------------------------------------------------
*
* Place #include files required to compile this source file here.
*
*----------------------------------------------------------------------------*/
#include "floodfill.h"
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
eFloodFillStates eFF_State = eInitializeValues;
/*----------------------------------------------------------------------------
*
* Place #define constants and macros that will be used only by this
* source file here.
*
*----------------------------------------------------------------------------*/
#define MAX_SNAKE_VAL	555
#define SNAKE_HEAD_VAL  600
/*----------------------------------------------------------------------------
*
* Place typedefs, structs, unions, and enums that will be used only
* by this source file here.
*
*----------------------------------------------------------------------------*/
std::stack<stRowColumn> myStack;
/*----------------------------------------------------------------------------
*
* Place static variables that will be used only by this file here.
*
*----------------------------------------------------------------------------*/
int field[HEIGHT_MAX][WIDTH_MAX];
/*----------------------------------------------------------------------------
*
* Place function bodies here.
*
*----------------------------------------------------------------------------*/
void push_neightbors(stRowColumn currentRowColumn){
	stRowColumn tempRowColumn;
	if (currentRowColumn.y != HEIGHT_MAX - 1 && field[currentRowColumn.y + 1][currentRowColumn.x] != MAX_SNAKE_VAL) {
		tempRowColumn = currentRowColumn;
		tempRowColumn.y = currentRowColumn.y + 1;
		myStack.push(tempRowColumn);
	}
	if (currentRowColumn.x != WIDTH_MAX - 1 && field[currentRowColumn.y][currentRowColumn.x + 1] != MAX_SNAKE_VAL) {
		tempRowColumn = currentRowColumn;
		tempRowColumn.x = currentRowColumn.x + 1;
		myStack.push(tempRowColumn);
	}
	if (currentRowColumn.y != 0 && field[currentRowColumn.y - 1][currentRowColumn.x] != MAX_SNAKE_VAL) {
		tempRowColumn = currentRowColumn;
		tempRowColumn.y = currentRowColumn.y - 1;
		myStack.push(tempRowColumn);
	}
	if (currentRowColumn.x != 0 && field[currentRowColumn.y][currentRowColumn.x - 1] != MAX_SNAKE_VAL) {
		tempRowColumn = currentRowColumn;
		tempRowColumn.x = currentRowColumn.x - 1;
		myStack.push(tempRowColumn);
	}
	
	

}
int find_smallest_neighbor(stRowColumn currentRowColumn) {
	int smallest  = MAX_SNAKE_VAL;
	if (currentRowColumn.y != 0 && smallest > field[currentRowColumn.y - 1][currentRowColumn.x]) {
		smallest = field[currentRowColumn.y - 1][currentRowColumn.x];
	}
	if (currentRowColumn.x != 0 && smallest > field[currentRowColumn.y ][currentRowColumn.x-1]) {
		smallest = field[currentRowColumn.y ][currentRowColumn.x - 1];
	}
	if (currentRowColumn.x != WIDTH_MAX -1 && smallest > field[currentRowColumn.y][currentRowColumn.x + 1]) {
		smallest = field[currentRowColumn.y ][currentRowColumn.x+1];
	}
	if (currentRowColumn.y != HEIGHT_MAX - 1 && smallest > field[currentRowColumn.y + 1][currentRowColumn.x]) {
		smallest = field[currentRowColumn.y + 1][currentRowColumn.x];
	}
	return smallest;
}
int go_smallest_neighbor(stRowColumn snakeHead, int smallest) {
	if (smallest == field[snakeHead.y - 1][snakeHead.x]) {
		eDir = eUp;
	}
	if (smallest == field[snakeHead.y][snakeHead.x - 1]) {
		eDir = eLeft;
	}
	if (smallest == field[snakeHead.y][snakeHead.x + 1]) {
		eDir = eRight;
	}
	if (snakeHead.y != HEIGHT_MAX - 1  && smallest == field[snakeHead.y + 1][snakeHead.x]) {
		eDir = eDown;
	}
	return smallest;
}
void generate_field_values() {
	// create a valid rowcolumn next to fruit to push in stack
	stRowColumn validFruit;
	// valid fruit need to make sure it doesnt push snake.
	if (fruit.x > 0 && field[fruit.y][fruit.x - 1] != MAX_SNAKE_VAL) {
		validFruit.x = fruit.x - 1;
		validFruit.y = fruit.y;
		myStack.push(validFruit);
	}
	if (fruit.y > 0 && field[fruit.y - 1][fruit.x] != MAX_SNAKE_VAL ) {
		validFruit.x = fruit.x;
		validFruit.y = fruit.y - 1;
		myStack.push(validFruit);
	}
	if (fruit.x < WIDTH_MAX - 1 && field[fruit.y][fruit.x + 1] != MAX_SNAKE_VAL) {
		validFruit.x = fruit.x + 1;
		validFruit.y = fruit.y;
		myStack.push(validFruit);
	}
	if (fruit.y < HEIGHT_MAX - 1 && field[fruit.y + 1][fruit.x] != MAX_SNAKE_VAL) {
		validFruit.x = fruit.x;
		validFruit.y = fruit.y + 1;
		myStack.push(validFruit);
	}
	field[fruit.y][fruit.x] = 0;
	int smallest;
	//std::cout << "Start of stacking\n";
	while (!myStack.empty()) {
		//std::cout << "Start of while\n";
		stRowColumn currentElement = myStack.top();
		//std::cout << currentElement.x << ", " << currentElement.y << ", \n";
		myStack.pop();
		if (!(currentElement.x == fruit.x && currentElement.y == fruit.y)) {
			smallest = find_smallest_neighbor(currentElement);
			if (field[currentElement.y][currentElement.x] != smallest + 1) {
				field[currentElement.y][currentElement.x] = smallest + 1;
				push_neightbors(currentElement);
			}
		}
		/*if ((currentElement.x == snake[0].x && currentElement.y == snake[0].y)) {
			while (!myStack.empty()) {
				myStack.pop();
			}
		}*/
		
	}
}
void print_field_values() {
	for (int i = 0; i < HEIGHT_MAX; i++) {
		for (int j = 0; j < WIDTH_MAX; j++) {
			std::cout << std::setw(3) << field[i][j];
		}
		std::cout << "\n";
	}
}

void go_top_left() {
	if (eDir == eDown) {
		eDir = eRight;
	}
	else  if (snake[0].y > 0) {
		eDir = eUp;
	}
	else {
		eDir = eLeft;
	}
}
void prepare() {
	if (eDir == eLeft) {
		eDir = eDown;
	}
	else if (eDir == eDown && snake[0].y == HEIGHT_MAX - 1) {
		eDir = eRight;
	}
	else if (eDir == eRight && snake[0].y == HEIGHT_MAX - 1) {
		eDir = eUp;
	}
	else if (eDir == eUp && snake[0].y == 1) {
		eDir = eRight;
	}
	else if (eDir == eRight && snake[0].y == 1) {
		eDir = eDown;
	}
}

void floodfill() {
	// Only time we initialize field is at beginning of program or snake eats fruit
	if (eFF_State == eInitializeValues) {
		for (int i = 0; i < HEIGHT_MAX; i++) {
			for (int j = 0; j < WIDTH_MAX; j++) {
				field[i][j] = MAX_SNAKE_VAL-5;
			}
		}
 		// initialize snakes position in field to be max snake value
		for (int i(0); i < sizeSnake; i++) {
			field[snake[i].y][snake[i].x] = MAX_SNAKE_VAL;
		}
		//field[snake[0].y][snake[0].x] = SNAKE_HEAD_VAL; 

		//std::cout << "Generating Field Values\n";
		generate_field_values();
		eFF_State = eMakeDecision;
		print_field_values();
		std::cout << "Snake Size: " << sizeSnake << "\n";
	}
	if (eFF_State == eMakeDecision) {
		// look for smallest neighbor and set eDir = Direction. 
		
		int smallest = find_smallest_neighbor(snake[0]);
		go_smallest_neighbor(snake[0], smallest);
	}
}