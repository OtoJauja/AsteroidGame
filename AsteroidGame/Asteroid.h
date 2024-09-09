#pragma once
#include <iostream>
#include <vector>
#include <list>
#include <random>
#include "sfml/graphics.hpp"
#include "Entity.h"
#include "Global.h"

// constants defining asteroid properties
constexpr float ASTEROID_W = 90.0f;
constexpr float ASTEROID_H = 80.0f;
constexpr float ASTEROID_SPIN = 40.0f;
constexpr float ASTEROID_SPEED = 80.0f;
constexpr float ASTEROID_SPAWN_TIME = 2.0f;
constexpr float ASTEROID_HIT_TIME = 2.0f;

class Asteroid : public Entity {
public:
    // constructor for the Asteroid class
    Asteroid(Vector2f direction = Asteroid::getRandomDirection(),
        Vector2f position = Asteroid::getRandomPosition());

    // update function to handle asteroid movement and interactions
    void update(float deltaTime);

    // render function to draw the asteroid on the window
    void render(RenderWindow& window);

    // function to retrieve the asteroids vertex array
    const VertexArray& getVertexArray() const;

    // functions to generate random direction and position for asteroids
    static Vector2f getRandomDirection();
    static Vector2f getRandomPosition();

    // function to retrieve the life of the asteroid
    float getLife() {
        return life;
    }

private:
    // array representing the shape of the asteroid
    VertexArray array;

    // directions of the asteroids movement
    Vector2f direction;

    // the remaining life of the asteroid
    float life;
};