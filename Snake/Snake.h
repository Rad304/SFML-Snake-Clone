//snake class
#pragma once

#include <SFML/Graphics.hpp>
#include "DEFINITIONS.h"
#include <vector>
#include "Direction.h"
class Snake {
public:
	Snake();
	void MoveSnake(float x,float y);
	void Draw(sf::RenderWindow &window);
	void setDirection(sf::Keyboard::Key key);
	bool isColliding(sf::RectangleShape shape);
	bool isCollidingWithTail();
	void Update(sf::RenderWindow &window);
	void add();
	const std::vector<sf::RectangleShape> &GetSnakeShape() const;
private:
	std::vector<sf::RectangleShape> snakeShape;
	int tilelength = 0;
	int currentDirection = ID::isMovingRight; //default snake direction
};