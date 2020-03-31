
/******************************************************************************
*
* @file     main.cpp
* @brief    snake game
* @version  V1.00
* @date     march 19, 2020
* @note		
*
******************************************************************************/

/*----------------------------------------------------------------------------
*
* Place #include files required to compile this source file here.
*
*----------------------------------------------------------------------------*/

#include "system.h"


/*----------------------------------------------------------------------------
*
* Place #define constants and macros that will be used only by this
* source file here.
*
*----------------------------------------------------------------------------*/



/*----------------------------------------------------------------------------
*
* Define global variables that will be used by both this source file
* and by other source files here.
*
*----------------------------------------------------------------------------*/
int sizeSnake = 10;
stRowColumn snake[SNAKE_MAX];
stRowColumn fruit;
eDirection eDir = eDown, eCurrDir=eDown;
eSnakeDecisionState eSnakeState = ePrepare;

/*----------------------------------------------------------------------------
*
* Place function prototypes that will be used only by this file here.
* This section need only include "forward referenced" functions.
*
*----------------------------------------------------------------------------*/
void update_snake(int, int);
bool check_snake_position(int, int);
bool pause();
bool resume();
/*----------------------------------------------------------------------------
*
* Place typedefs, structs, unions, and enums that will be used only
* by this source file here.
*
*----------------------------------------------------------------------------*/
using namespace sf;

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

void genereate_fruit(int N, int M) {
	// fruit.x = rand() % N;
	fruit.x = rand() % N;
	fruit.y = rand() % M;
}
void update_snake(int N, int M)
{
	// Update snake position from snake[num] -> snake[1]
	
	for (int i = sizeSnake;i > 0;--i)
	{
		snake[i].x = snake[i - 1].x; 
		snake[i].y = snake[i - 1].y;
	}
	// update snake head position based on direction
	if (eDir == eDown) snake[0].y += 1;
	else if (eDir == eLeft) snake[0].x -= 1;
	else if (eDir == eRight) snake[0].x += 1;
	else if (eDir == eUp) snake[0].y -= 1;

	// If snake eats fruit, then generate random fruit.
	bool need_new_fruit = false;
	if ((snake[0].x == fruit.x) && (snake[0].y == fruit.y))
	{
		sizeSnake++; 
		need_new_fruit = true;
		std::cout << "Making NEw fruit\n";
		// floodfill needs to initialize value again
		eFF_State = eInitializeValues;
		// once snake eats fruit, it needs to go top left unless its doing prepare
		if (eSnakeState != ePrepare) {
			eSnakeState = eGoTopLeft;
		}
	}
	// if Snake head is top left, snake is in prepare state 
	if (snake[0].x == 0 && snake[0].y == 0) {
		eSnakeState = ePrepare;
	}// if snake tail is at top left then prepare state is done and time to start floodfill
	if (snake[sizeSnake - 1].x == 0 && snake[sizeSnake - 1].y == 0) {
		eSnakeState = eFloodfill;
	}
	// makes sure fruit isnt on snake
	while (need_new_fruit) {
		genereate_fruit(N, M);
		for (int i = 1;i < sizeSnake;i++) {
			if (fruit.x == snake[i].x && fruit.y == snake[i].y) {
				need_new_fruit = true;
				std::cout << "Need New Fruit\n";
				break;
			}
			else {
				//std::cout << "Dont need New Fruit\n";
				need_new_fruit = false;
			}
		}
	}
	
	

	// Snake bites his body off!
	for (int i = 1;i < sizeSnake;i++) {
		if (snake[0].x == snake[i].x && snake[0].y == snake[i].y) {
			sizeSnake = i;
			std::cout << "Snake bit his body off! :(\n";
		}
	}	
}
bool check_snake_position(int N, int M) {
	bool isOutOfBoundary = false;
	// if snake is out of boundary 
	if (snake[0].x >= N || snake[0].x < 0 || snake[0].y >= M || snake[0].y < 0) isOutOfBoundary = true;
	return isOutOfBoundary;
}
bool pause() {
	// std::cout << "I'm on Pause \n";
	return false;
}
bool resume() {
	std::cout << "I'm now back in windows\n";
	return true;
}
int main()
{
	srand(time(0));
	int N = WIDTH_MAX, M = HEIGHT_MAX;
	int w = N * NUM_PIXEL;
	int h = M * NUM_PIXEL;
	RenderWindow window(VideoMode(w, h), "Snake Game!");

	Texture tBackground, tFruit, tSnake;
	tBackground.loadFromFile("images/white.png");
	tFruit.loadFromFile("images/green.png");
	tSnake.loadFromFile("images/red.png");

	Sprite spriteBackground(tBackground);
	Sprite spriteFruit(tFruit);
	Sprite spriteSnake(tSnake);

	Clock clock;
	float timer = 0, delay = 0.055;
	bool isOutOfBoundary = false;
	bool inSession = true;

	// initialize fruit to (10,10)
	fruit.x = 10;
	fruit.y = 10;
	
	while (window.isOpen())
	{
		float time = clock.getElapsedTime().asSeconds();
		clock.restart();
		timer += time;

		Event e;
		while (window.pollEvent(e))
		{
			if (e.type == Event::Closed)
				window.close();
			if (e.type == sf::Event::LostFocus) {}
				//inSession = pause();
			if (e.type == sf::Event::GainedFocus) {}
				//inSession = resume();
		}

		/*if (Keyboard::isKeyPressed(Keyboard::Left)) eDir = eLeft;
		else if (Keyboard::isKeyPressed(Keyboard::Right)) eDir = eRight;
		else if (Keyboard::isKeyPressed(Keyboard::Up)) eDir = eUp;
		else if (Keyboard::isKeyPressed(Keyboard::Down)) eDir = eDown;*/

		if (timer > delay && inSession) { 
			timer = 0; 
			update_snake(N, M);
			isOutOfBoundary = check_snake_position(N, M);
			if (eSnakeState == eFloodfill) {
				floodfill();
			}
			if (eSnakeState == eGoTopLeft) {
				go_top_left();
			}
			if (eSnakeState == ePrepare) {
				prepare();
			}
		}
		if (isOutOfBoundary || sizeSnake == SNAKE_MAX-1) {
			//std::cout << " Snake is Out of Bound\n";
			inSession = pause();
		}

		////// draw  ///////
		window.clear();

		for (int i = 0; i < N; i++)
			for (int j = 0; j < M; j++)
			{
				spriteBackground.setPosition(i*NUM_PIXEL, j*NUM_PIXEL);
				window.draw(spriteBackground);
			}

		for (int i = 0;i < sizeSnake;i++)
		{
			spriteSnake.setPosition(snake[i].x*NUM_PIXEL, snake[i].y*NUM_PIXEL);  window.draw(spriteSnake);
		}

		spriteFruit.setPosition(fruit.x*NUM_PIXEL, fruit.y*NUM_PIXEL);  window.draw(spriteFruit);

		window.display();
	}
	return 0;
}
