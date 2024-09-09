#include "Asteroid.h"
#include "Global.h"
#include <random>

// constructor for the Asteroid class with initialization list
Asteroid::Asteroid(Vector2f direction, Vector2f position)
	: Entity(position, 0), direction(direction), array(LinesStrip, 12), life() {
	// defines the vertices of the asteroid shape
	array[0].position = Vector2f(-40, 40);
	array[1].position = Vector2f(-50, 10);
	array[2].position = Vector2f(-10, -20);
	array[3].position = Vector2f(-20, -40);
	array[4].position = Vector2f(10, -40);
	array[5].position = Vector2f(40, -20);
	array[6].position = Vector2f(40, -10);
	array[7].position = Vector2f(50, 0);
	array[8].position = Vector2f(40, 20);
	array[9].position = Vector2f(20, 40);
	array[10].position = Vector2f(0, 30);
	array[11].position = array[0].position;

	// sets the color of each vertex in the array
	for (size_t i = 0; i < array.getVertexCount(); i++)
	{
		array[i].color = Color::White;
	}
}

// function for handling asteroid movement and rotation
void Asteroid::update(float deltaTime) {
	life += deltaTime;

	// updates position based on speed and direction
	position += ASTEROID_SPEED * direction * deltaTime;
	angle += ASTEROID_SPIN * deltaTime;

	// handles asteroid wrapping around the screen edges
	if (position.x < ASTEROID_W / 2.0f) {
		direction.x = abs(direction.x);
	}
	else if (position.x > SCREEN_WIDTH - ASTEROID_W / 2.0f) {
		direction.x = -abs(direction.x);
	}

	if (position.y < ASTEROID_H / 2.0f) {
		direction.y = abs(direction.y);
	}
	else if (position.y > SCREEN_HEIGHT - ASTEROID_H / 2.0f) {
		direction.y = -abs(direction.y);
	}
}

// function for drawing the asteroid on the window
void Asteroid::render(RenderWindow& window)
{
	// draws the asteroid using a transformed vertex array
	window.draw(array, Transform().translate(position).rotate(angle));
}

// function to retrieve the asteroids vertex array
const VertexArray& Asteroid::getVertexArray() const {
	return array;
}

// function to generate a random direction for asteroids
Vector2f Asteroid::getRandomDirection()
{
	random_device rd;
	mt19937 gen(rd());
	uniform_real_distribution<float> dist(0.0f, 2.0f * M_PI);

	// generates a random angle and convert it to a direction vector
	float angle = dist(gen);
	return Vector2f(cos(angle), sin(angle));
}

// static function to generate a random position for asteroids
Vector2f Asteroid::getRandomPosition()
{
	random_device rd;
	mt19937 gen(rd());
	uniform_real_distribution<float> xAxis(ASTEROID_W / 2.0f, SCREEN_WIDTH - ASTEROID_W / 2.0f);
	uniform_real_distribution<float> yAxis(ASTEROID_H / 2.0f, SCREEN_HEIGHT - ASTEROID_H / 2.0f);

	// generates random x and y coordinates
	return Vector2f(xAxis(gen), yAxis(gen));
}