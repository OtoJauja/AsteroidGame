#pragma once
#include "sfml/graphics.hpp"
#include "sfml/audio.hpp"
#include "Entity.h"
#include "Global.h"
#include "Bullet.h"
#include "Game.h"

// constants defining player dimensions and movement speeds
constexpr float PLAYER_W = 50.0f;
constexpr float PLAYER_H = 40.0f;
constexpr float TURN_SPEED = 200.0f;
constexpr float PLAYER_SPEED = 200.0f;

class Player : public Entity {
public:
    // constructor for Player class
    Player();

    void update(float deltaTime);// update function to handle player movement and actions

    void render(RenderWindow& window);// render function to draw the player on the window

private:
    // VertexArray representing the players shape
    VertexArray array;

    // sound for player's shooting action
    Sound shootSound;

    // timer to control the rate of players shooting
    float shootTimer;
};