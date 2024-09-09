#include "Game.h"
#include "Asteroid.h"
#include "Player.h"
#include <fstream>

// initializes static member variables
vector<Entity*> Game::entities{};
list<vector<Entity*>::const_iterator> Game::toRemoveList{};
list<Entity*> Game::toAddList{};

size_t Game::score{};
size_t Game::highScore{};
float Game::asteroidSpawnTime{};
unordered_map<string, SoundBuffer> Game::soundBuffers;
Game::State Game::state{};

Text Game::continueText{};
Text Game::gameOverText{};

Text Game::scoreText{};

Text Game::highScoreText{};
Text Game::menuText{};
Text Game::playText{};
Text Game::titleText{};
Font Game::font{};

void Game::init() {
    // reads the high score from a file created in the folder
    fstream file("score.dat", ios::binary || ios::in);
    if (file.is_open()) {
        file.read(reinterpret_cast<char*>(&highScore), sizeof(size_t));
        file.close();
    }

    //loads the font from imported file
    font.loadFromFile("BACKTO1982.ttf");

    // sets up the score text
    scoreText.setFont(font);
    scoreText.setPosition(Vector2f(40, 20));
    scoreText.setCharacterSize(38);

    // Set up high score text
    highScoreText.setFont(font);
    highScoreText.setPosition(Vector2f(40, 20));
    highScoreText.setCharacterSize(38);
    highScoreText.setString("High Score: " + to_string(highScore));

    // set up the game over text
    gameOverText.setFont(font);
    gameOverText.setPosition(Vector2f(250, 350));
    gameOverText.setCharacterSize(86);
    gameOverText.setString("Game Over!!");

    // sets up the continue text
    continueText.setFont(font);
    continueText.setPosition(Vector2f(360, 550));
    continueText.setCharacterSize(24);
    continueText.setString("Press SPACE to continue!");

    // set up the title text
    titleText.setFont(font);
    titleText.setPosition(Vector2f(250, 350));
    titleText.setCharacterSize(48);
    titleText.setString("ASTEROID DESTROYER");

    // sets up the play text
    playText.setFont(font);
    playText.setPosition(Vector2f(400, 550));
    playText.setCharacterSize(24);
    playText.setString("Press ENTER to play!");
    // sets up the menu text
    menuText.setFont(font);
    menuText.setPosition(Vector2f(340, 650));
    menuText.setCharacterSize(24);
    menuText.setString("Press ESCAPE to go to menu!");
    // load sound buffer for shooting
    soundBuffers["shoot"].loadFromFile("laser5.wav");
    // sets the initial state to the menu
    state = MENU;
}

void Game::begin() {
    // changes state to playing and adds a player entity
    state = PLAYING;
    entities.push_back(new Player());
    asteroidSpawnTime = ASTEROID_SPAWN_TIME;
    score = 0;
}

void Game::update(RenderWindow& window, float deltaTime) {
    if (state == MENU) {
        // draws menu elements
        window.draw(highScoreText);
        window.draw(titleText);
        window.draw(playText);
        // checks for enter key press to start the game
        if (Keyboard::isKeyPressed(Keyboard::Enter)) {
            begin();
        }
        return;
    }
    // clears lists for adding and removing entities
    toAddList.clear();
    toRemoveList.clear();
    // updates asteroid spawn time
    asteroidSpawnTime -= deltaTime;

    // updates and renders each entity
    for (size_t i = 0; i < entities.size(); i++) {
        entities[i]->update(deltaTime);
        entities[i]->render(window);
    }

    // removes entities marked for removal
    for (const auto& it : toRemoveList) {
        delete* it;
        entities.erase(it);
    }
    // adds new entities
    for (auto& ptr : toAddList) {
        entities.push_back(ptr);
    }

    // spawns asteroids periodically
    if (asteroidSpawnTime <= 0.0f) {
        entities.push_back(new Asteroid());
        asteroidSpawnTime = ASTEROID_SPAWN_TIME;
    }
    // updates and draws the players score
    scoreText.setString(to_string(score));
    window.draw(scoreText);
    // checks if the game is in the game over state
    if (state == GAME_OVER) {
        // clears entities and draws game over elements
        entities.clear();
        window.draw(gameOverText);
        window.draw(continueText);
        window.draw(menuText);
        // restarts the game if space is pressed
        if (Keyboard::isKeyPressed(Keyboard::Space)) {
            begin();
        }
        // returns to the menu if escape is pressed
        if (Keyboard::isKeyPressed(Keyboard::Escape)) {
            state = MENU;
        }
    }
}

void Game::gameOver() {
    // updates the high score if the current score is higher
    if (score > highScore) {
        highScore = score;
        // writes the high score to a file
        ofstream file("score.dat", ios::binary || ios::out);
        if (file.is_open()) {
            file.write(reinterpret_cast<const char*>(&highScore), sizeof(size_t));
            file.close();
        }
        // updates high score text
        highScoreText.setString("High Score: " + to_string(highScore));
    }
    // sets the state to game over
    state = GAME_OVER;
}