#include "Snake.h"
#include <iostream>

/*
	* Constructor
	* @params: sf::Vector2f - represent the size of the snake head shape
*/
Snake::Snake(){
	sf::RectangleShape shape(sf::Vector2f(SNAKE_WIDTH, SNAKE_HEIGHT)); //create the snake head shape
	shape.setFillColor(sf::Color::White); //set the head shape color to white
	snakeShape.push_back(shape); //add the head , after we will be adding elements to the tail when eating the food...
}
void Snake::MoveSnake(float x, float y) {
	if (snakeShape.size() > 0) {
		// move the snake head by the params x and y
		// this function adds x and y to the current position of the snake head
		snakeShape[0].move(x, y); 
	}	
}
/*
	* Draw the snake on the screen...
	* @params: sf::RenderWindow &window
	* returns: void
*/
void Snake::Draw(sf::RenderWindow &window) {
	//draw the head and the tail to the screen...
	//the element 0 is the head
	//the others is the tail elements
	for (int i = 0; i < snakeShape.size(); i++) {
		window.draw(snakeShape.at(i));
	}
		
}

/*
	* Change the snake direction...
	* @params: sf::Keyboard::Key key - a keyboard key
	* returns: void
*/
void Snake::setDirection(sf::Keyboard::Key key) {
	//the length of the tail is 0 then we can move on every direction...
	if (tilelength < 1) {
		if (key == sf::Keyboard::Up)
			currentDirection = ID::isMovingUp; 
		else if (key == sf::Keyboard::Down)
			currentDirection = ID::isMovingDown;
		else if (key == sf::Keyboard::Left)
			currentDirection = ID::isMovingLeft;
		else if (key == sf::Keyboard::Right)
			currentDirection = ID::isMovingRight;
	}
	//the length of the tail is greater than 0 then we can't move on the opposite of the current direction...
	else {
		if (key == sf::Keyboard::Up && currentDirection != ID::isMovingDown)
			currentDirection = ID::isMovingUp;
		else if (key == sf::Keyboard::Down && currentDirection != ID::isMovingUp)
			currentDirection = ID::isMovingDown;
		else if (key == sf::Keyboard::Left && currentDirection != ID::isMovingRight)
			currentDirection = ID::isMovingLeft;
		else if (key == sf::Keyboard::Right && currentDirection != ID::isMovingLeft)
			currentDirection = ID::isMovingRight;
	}
	
}
/*
	* Update the snake position based on the direction...
	* @params: sf::RenderWindow &window
	* returns: void
*/
void Snake::Update(sf::RenderWindow &window) {
	/*
	 *the n-1 element in the tail take the current position of the n-2 element in the tail
	 *the n-2 element in the tail take the current position of the n-3 element in the tail
	 .
	 .
	 .
	 the 1st element in the tail takes the current position of the head
	*/
	for (int i = snakeShape.size()-1; i >= 1; i--) {
		snakeShape.at(i).setPosition(snakeShape.at(i-1).getPosition());
	}
	//move the snake based on the current direction
	if(currentDirection == ID::isMovingUp)
		MoveSnake(0, -1 * SNAKE_WIDTH);
	else if(currentDirection == ID::isMovingDown)
		MoveSnake(0, 1 * SNAKE_WIDTH);
	else if(currentDirection == ID::isMovingLeft)
		MoveSnake(-1 * SNAKE_WIDTH, 0);
	else if(currentDirection == ID::isMovingRight)
		MoveSnake(1 * SNAKE_WIDTH, 0);
	
	//checking if the snake is out of the screen
	if (snakeShape[0].getPosition().x > window.getSize().x)
		snakeShape[0].setPosition(0, snakeShape[0].getPosition().y);
	else if (snakeShape[0].getPosition().x < 0)
		snakeShape[0].setPosition(window.getSize().x, snakeShape[0].getPosition().y);
	else if (snakeShape[0].getPosition().y > window.getSize().y)
		snakeShape[0].setPosition(snakeShape[0].getPosition().x, 0);
	else if (snakeShape[0].getPosition().y < 0)
		snakeShape[0].setPosition(snakeShape[0].getPosition().x, window.getSize().y);
}
/*
	* Check for collision, we use it to check if the snake head is colliding with the food...
	* @params: sf::RectangleShape shape
	* returns: bool
*/
bool Snake::isColliding(sf::RectangleShape shape) {
	if (snakeShape.size() > 0) {
		sf::Rect<float> rect1 = snakeShape[0].getGlobalBounds();
		sf::Rect<float> rect2 = shape.getGlobalBounds();

		if (rect1.intersects(rect2))
		{
			return true;
		}
		else
		{
			return false;
		}
	}
}


/*
	* Check if the snake head is colliding with one of the tail elements...
	* @params: None
	* returns: bool
*/
bool Snake::isCollidingWithTail() {
	for (int i = 1; i < snakeShape.size(); i++) {
		if (this->isColliding(snakeShape.at(i))) {
			return true;
		}
	}
	return false;
}

/*
	* add an element to the tail...
	* @params: None
	* returns: Void
*/
void Snake::add() {
	tilelength++; //increment the tilelength value
	sf::RectangleShape shape(sf::Vector2f(SNAKE_WIDTH, SNAKE_HEIGHT));
	shape.setFillColor(sf::Color::White); //set the tail element shape color to white
	shape.setPosition(-50.0f, -50.0f);	//just a random default position before attaching it to the tail elements 
	snakeShape.push_back(shape); //add the new tail element
}

/*
	* return the snake head and tail elements, so we can check collision or something...
	* @params: None
	* returns: std::vector<sf::RectangleShape> &
*/
const std::vector<sf::RectangleShape> &Snake::GetSnakeShape() const {
	return snakeShape;
}
