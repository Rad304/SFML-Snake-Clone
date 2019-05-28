#include "Food.h"
/*
	* Constructor
	* @params: sf::Vector2f - represent the size of the foodshape
*/
Food::Food() : foodShape(sf::Vector2f(FOOD_WIDTH,FOOD_HEIGHT)){
	foodShape.setFillColor(sf::Color::Red); //set the shape color to red
	srand(time(NULL));
}
/*
	* Generate a random position on the screen
	* @params: None
	* returns: sf::Vector2f
*/
sf::Vector2f Food::GeneratePosition() {
	int xPos = rand() % (SCREEN_WIDTH / FOOD_WIDTH);
	int yPos = rand() % (SCREEN_WIDTH / FOOD_WIDTH);
	sf::Vector2f Pos(xPos, yPos);
	return Pos;
}

/*
	* avoid spawning the food on the snake...
	* @params: std::vector<sf::RectangleShape> shapes - which represent the snake
	* returns: void
*/
void Food::TakeALocation(std::vector<sf::RectangleShape> shapes) {
	sf::Vector2f Pos = GeneratePosition(); //generate a random position
	for (int i = 0; i < shapes.size(); i++) {
		//if the food is on the snake "position" then we generate another random position 
		if(shapes.at(i).getPosition() == Pos) 
			Pos = GeneratePosition();
	}
	foodShape.setPosition(Pos.x*FOOD_WIDTH, Pos.y*FOOD_HEIGHT); //set the food position
}

/*
	* return the food shape so we can check collision or something...
	* @params: None
	* returns: sf::RectangleShape & 
*/
sf::RectangleShape &Food::GetShape() {
	return foodShape;
}
/*
	* Draw the food on the screen...
	* @params: sf::RenderWindow &window 
	* returns: void
*/
void Food::Draw(sf::RenderWindow &window) {
	window.draw(foodShape); //draw the food
}