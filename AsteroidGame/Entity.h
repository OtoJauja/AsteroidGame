#pragma once
#include "sfml/graphics.hpp"
#include "sfml/window.hpp"
#include "sfml/system.hpp"

// namespaces for convenience
using namespace sf;
using namespace std;

// base class representing a game entity
class Entity {
public:
    // constructor initializes the entitys position and angle
    Entity(Vector2f position, float angle) :
        position(position), angle(angle) {}

    // virtual function for updating the entitys state
    virtual void update(float deltaTime) = 0;

    // virtual function for rendering the entity on the window
    virtual void render(RenderWindow& window) = 0;

    // position of the entity in 2D space
    Vector2f position;

    // angle of the rotation for the entity
    float angle;
};