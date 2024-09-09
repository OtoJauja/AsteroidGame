#include "Player.h"
#include "Bullet.h"
#include "Game.h"
#include "Asteroid.h"
#include "Physics.h"
#include "Global.h"

Player::Player()
    : Entity(Vector2f(500, 500), 0), array(LinesStrip, 5), shootTimer() {

    // defines the shape of the player using a vertexArray
    array[0].position = Vector2f(20, 0);
    array[1].position = Vector2f(-30, -20);
    array[2].position = Vector2f(-15, 0);
    array[3].position = Vector2f(-30, 20);
    array[4].position = array[0].position;

    // sets the color of each vertex in the array to yellow
    for (size_t i = 0; i < array.getVertexCount(); i++)
    {
        array[i].color = Color::Yellow;
    }

    // sets the sound buffer for shooting using the games sound buffers
    shootSound.setBuffer(Game::soundBuffers["shoot"]);
}

void Player::update(float deltaTime)
{
    // decreases the shoot timer based on elapsed time
    shootTimer -= deltaTime;

    // handles player rotation to the left
    if (Keyboard::isKeyPressed(Keyboard::A)) {
        angle -= TURN_SPEED * deltaTime;
    }

    // handles player rotation to the right
    if (Keyboard::isKeyPressed(Keyboard::D)) {
        angle += TURN_SPEED * deltaTime;
    }

    // handles player movement forward
    if (Keyboard::isKeyPressed(Keyboard::W)) {
        float radians = angle * (M_PI / 180.0f);

        // updates player position based on movement direction and speed
        position.x += cos(radians) * PLAYER_SPEED * deltaTime;
        position.y += sin(radians) * PLAYER_SPEED * deltaTime;

        // ensures the player stays within the screen boundaries
        position.x = min(max(position.x, PLAYER_W / 2.0f), SCREEN_WIDTH - PLAYER_W / 2.0f);
        position.y = min(max(position.y, PLAYER_H / 2.0f), SCREEN_HEIGHT - PLAYER_H / 2.0f);
    }

    // handles shooting bullets
    if (Keyboard::isKeyPressed(Keyboard::Space) && shootTimer <= 0.0f) {
        // plays shooting sound
        shootSound.play();
        // resets shoot timer
        shootTimer = SHOOT_DELAY;

        // calculates bullet direction based on players angle
        float radians = angle * (M_PI / 180.0f);
        // adds a new bullet to the games toAddList
        Game::toAddList.push_back(new Bullet(position, Vector2f(cos(radians), sin(radians))));
    }

    // creates a transformation for the players position and rotation
    Transform playerTransform = Transform().translate(position).rotate(angle);

    // checks for collisions with asteroids
    for (size_t i = 0; i < Game::entities.size(); i++) {
        if (typeid(*Game::entities[i]) == typeid(Asteroid)) {
            Asteroid* asteroid = dynamic_cast<Asteroid*>(Game::entities[i]);
            Transform asteroidTransform = Transform()
                .translate(asteroid->position).rotate(asteroid->angle);

            // skips collision check if asteroid is recently hit
            if (asteroid->getLife() < ASTEROID_HIT_TIME) {
                continue;
            }

            // checks for collision between player and asteroid
            if (intersects(getTransformed(array, playerTransform),
                getTransformed(asteroid->getVertexArray(), asteroidTransform))) {
                Game::gameOver();
            }
        }
    }
}

void Player::render(RenderWindow& window)
{
    window.draw(array, Transform().translate(position).rotate(angle));// draws the player shape on the window
}