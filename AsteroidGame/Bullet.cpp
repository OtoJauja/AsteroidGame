#include "Bullet.h"
#include "Game.h"
#include "Asteroid.h"

Bullet::Bullet(Vector2f position, Vector2f direction)
    : shape(1.0f), direction(direction), Entity(position, 0.0f), lifetime(BULLET_LIFE) {}

// function for handling bullet movement and interactions
void Bullet::update(float deltaTime)
{
    // reduces the lifetime of the bullet
    lifetime -= deltaTime;

    // moves the bullet in the specified direction
    position += direction * BULLET_SPEED * deltaTime;

    // checks if the bullets lifetime has expired
    if (lifetime <= 0.0f) {
        // adds the bullet to the list of entities to be removed
        Game::toRemoveList.push_back(find(Game::entities.begin(), Game::entities.end(), this));
    }

    // checks for a collisions with asteroids
    for (size_t i = 0; i < Game::entities.size(); i++) {
        if (typeid(*Game::entities[i]) == typeid(Asteroid)) {
            Asteroid* asteroid = dynamic_cast<Asteroid*>(Game::entities[i]);

            // creates a transformation for the asteroid
            Transform transform = Transform()
                .translate(asteroid->position)
                .rotate(asteroid->angle);

            // checks if the bullet intersects with the transformed asteroid shape
            if (intersects(position, getTransformed(asteroid->getVertexArray(), transform))) {
                lifetime = 0.0f;  // sets bullet lifetime to 0 upon collision
                // adds the asteroid to the list of entities to be removed
                Game::toRemoveList.push_back(find(Game::entities.begin(), Game::entities.end(), asteroid));
                Game::score += 10;  // increases the score by 10
            }
        }
    }
}

// function for drawing the bullet on the window
void Bullet::render(RenderWindow& window)
{
    window.draw(shape, Transform().translate(position));
}