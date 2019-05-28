//food class
#pragma once
#include <SFML/Graphics.hpp>
#include "DEFINITIONS.h"
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <vector>
class Food {
public:
	Food();
	void TakeALocation(std::vector<sf::RectangleShape> shapes); 
	void Draw(sf::RenderWindow &window);
	sf::Vector2f GeneratePosition();
	sf::RectangleShape &GetShape();
private:
	sf::RectangleShape foodShape;
};