///////////////////////////////////////
/////////Created by Rad304////////////
////////////Snake Clone//////////////
////////////C++ & SFML//////////////
///////////////////////////////////
#include <SFML/Graphics.hpp>
#include "DEFINITIONS.h"
#include "Snake.h"
#include "Food.h"
#include "GameStates.h"
int main()
{
	sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "C++ & SFML Snake Game by Rad304!"); //create a window
	sf::Clock clock; //clock
	float dt = 1.0f / 3.0f; //3fps game :p 
	Snake snake; //snake object
	Food food; //food object
	int currentGameState = GState::GameState; //Default game state 
	sf::Font font; //font object
	font.loadFromFile(FONT_FILEPATH);	//loading the font
	sf::Text gameStateText("", font);  //a simple text to show the gameState
	gameStateText.setCharacterSize(30);			//character size
	gameStateText.setStyle(sf::Text::Bold);		//set the text style as Bold
	gameStateText.setFillColor(sf::Color::Red); //set the text color as a red color
	food.TakeALocation(snake.GetSnakeShape());	//setting an initial location for the food
	
	//the game loop...
	while (window.isOpen())	
	{
		// Process events
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type) {
			//close buttton is clicked
			case sf::Event::Closed:
				window.close(); // Close window: exit
			//a key is pressed 
			case sf::Event::KeyPressed:
				//updating the snake direction based on arrow key pressed...
				if (event.key.code == sf::Keyboard::Up)
					snake.setDirection(sf::Keyboard::Up);
				else if(event.key.code == sf::Keyboard::Down)
					snake.setDirection(sf::Keyboard::Down);
				else if (event.key.code == sf::Keyboard::Right)
					snake.setDirection(sf::Keyboard::Right);
				else if (event.key.code == sf::Keyboard::Left)
					snake.setDirection(sf::Keyboard::Left);
				//P key is pressed
				if (event.key.code == sf::Keyboard::P) {
					//currentGameState is the GameState
					if (currentGameState == GState::GameState) {
						currentGameState = GState::PauseState; //set currentGameState to the PauseState
						gameStateText.setString("Paused"); //change the gameStateText to "Paused"
						gameStateText.setPosition(window.getSize().x / 2 - gameStateText.getGlobalBounds().width / 2, window.getSize().y / 2 - gameStateText.getGlobalBounds().height / 2); //Set the gameStateText position to the center of the screen
					}
					//currentGameState is the PauseState
					else if (currentGameState == GState::PauseState) {
						currentGameState = GState::GameState; //set currentGameState to GameState
						gameStateText.setString("");
					}	
				}
			}
		}
		//currentGameState is the GameState
		if (currentGameState == GState::GameState) {
			//instead of updating the game position every tick of the game loop
			//we will update the game every dt seconds....
			//so we somehow create a frame independant gameplay....
			if (clock.getElapsedTime().asSeconds() > dt) {
				snake.Update(window); //update the snake
				clock.restart(); //restart the clock
			}
			//the snake is collinding with the food
			if (snake.isColliding(food.GetShape())) {
				food.TakeALocation(snake.GetSnakeShape()); //change the food location
				snake.add(); //add an element to the tail
			}
			//the snake is collinding with the tail
			if (snake.isCollidingWithTail()) {
				currentGameState = GState::GameOverState; //set the current state to the GameOverState
				gameStateText.setString("Game Over"); //change the gameStateText to "Game Over"
				gameStateText.setPosition(window.getSize().x / 2 - gameStateText.getGlobalBounds().width / 2, window.getSize().y / 2 - gameStateText.getGlobalBounds().height / 2); //Set the gameStateText position to the center of the screen
			}
		}
		window.clear(); // clear the window
		food.Draw(window); //draw the food
		snake.Draw(window); //draw the snake
		if(currentGameState == GState::PauseState || currentGameState == GState::GameOverState) window.draw(gameStateText); //we show the gameStateText only if the game is on the PauseState or GameOverState 
		window.display(); //display
	}

	return 0;
}