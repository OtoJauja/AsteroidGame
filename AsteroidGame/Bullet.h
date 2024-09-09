#pragma once
#include "sfml/graphics.hpp"
#include "Entity.h"
#include "Global.h"
#include "Game.h"
#include "Physics.h"

using namespace physics;

// constants defining bullet properties
constexpr float BULLET_SPEED = 400.0f;
constexpr float SHOOT_DELAY = 0.5f;
constexpr float BULLET_LIFE = 3.0f;

class Bullet : public Entity {
public:
    // constructor for Bullet class
    Bullet(Vector2f position, Vector2f direction);

    // function to handle bullet movement and interactions
    void update(float deltaTime);

    // function to draw the bullet on the window
    void render(RenderWindow& window);

private:
    Vector2f direction;   // direction of the bullet
    CircleShape shape;    // shape representing the bullet
    float lifetime;       // remaining lifetime of the bullet
};