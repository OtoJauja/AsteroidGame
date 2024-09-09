#pragma once
#include <iostream>
#include <vector>
#include <list>
#include <unordered_map>
#include "sfml/audio.hpp"
#include "Entity.h"

class Game {
public:
    // initializes the game
    static void init();
    // starts the game
    static void begin();
    // updates the game state
    static void update(RenderWindow& window, float deltaTime);
    // handles game over conditions
    static void gameOver();
    // collection of entities in the game
    static vector<Entity*> entities;
    // list of iterators pointing to entities to be removed
    static list<vector<Entity*>::const_iterator> toRemoveList;
    // list of entities to be added
    static list<Entity*> toAddList;
    // players score
    static size_t score;
    // sound buffers for in-game sounds
    static unordered_map<string, SoundBuffer> soundBuffers;

private:
    // the time between asteroid spawns
    static float asteroidSpawnTime;
    // players high score
    static size_t highScore;
    // texts displayed during the game
    static Text continueText;
    static Text gameOverText;
    static Text scoreText;
    static Text menuText;
    static Text playText;
    static Text titleText;
    static Text highScoreText;
    // font for rendering texts
    static Font font;
    // enum representing the current state of the game
    static enum State { MENU, PLAYING, GAME_OVER } state;
};