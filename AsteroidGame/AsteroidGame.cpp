#include <iostream>
#include "Game.h"
#include "Physics.h"

using namespace sf;
using namespace std;

int main() {
	RenderWindow window(VideoMode(1200, 900), "Asteroid Destroyer", Style::Close | Style::Titlebar); // create a window object with a given video mode, title, and style 
	Clock clock;// creates a clock object to measure the elapsed time 

	// calls the init function to initialize the game settings and variables
	Game::init();

	// enters the main game loop
	while (window.isOpen())
	{
		// gets the elapsed time since the last frame update and restart the clock
		float deltaTime = clock.restart().asSeconds();
		// creates an event object to store the user input events
		Event e{};
		// poll the events from the window
		while (window.pollEvent(e))
		{
			//check if the user has requested to close the window
			if (e.type == Event::Closed) {
				//close the window
				window.close();
			}
		}
		// clears the window with a black color
		window.clear();
		// calls the update function to update and render the game objects and logic
		Game::update(window, deltaTime);

		// displays the window on the screen
		window.display();
	}
}