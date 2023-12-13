#include <cstdlib>
#include <time.h>
#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include <iostream>
#include "i220744_i221011_car.h"
#include "i220744_i221011_food.h"

const char title[] = "OOP-Project, Fall-2023";
using namespace sf;
using namespace std;

class Game {
private:
    // Private member functions

    // Function to check for collision between player and enemies
    void checkForCollision();

    // Function to remove a food item from the array
    bool popFood(int i);

    // Function to check for collision between player and food items
    void checkForFoodCollision();

    // Function to check if the game has ended
    bool endGame();

    // Function to pause the game
    void pauseGame();

    // Function to resume the game
    void resumeGame();

    // Function to create enemies based on the game level
    void createEnemies();

    // Function to return enemies to the game after a certain time period
    void returnEnemy();

    // Function to check if the player's boost has ended
    bool endBoost();

    bool winLose;    // Flag to indicate game win or lose
    int score;       // Player's score
    int level;       // Current game level

    // Text to display "Paused" during the pause
    Text playPause;

    // Clock to manage enemy appearance
    Clock enemyClock;

    // Clock to manage player's boost duration
    Clock boostClock;

public:
    // Public member variables

    // Game background sprite
    Sprite background;

    // Texture for the game background
    Texture bg_texture;

    // Font for text display
    Font font;

    // Text to display player's remaining lives
    Text livesText;

    // Text to display player's score
    Text scoresText;

    // Player object
    Player* p;

    // Array of enemy objects
    int noOfEnemies;
    int noOfInactiveEnemies;
    Enemy** en;

    // Array of food objects
    int noOfFoods;
    Food** foods;

    // Constructor
    Game(int level);

    // Destructor
    ~Game();

    // Public member functions

    // Function to start the game
    void start_game();

    // Getter for the player's score
    int getScore();

    // Getter for the current game level
    int getLevel();

    // Getter for the game result (win or lose)
    bool getWinLose();
};

// Member function definitions

// Function to check for collision between player and enemies
void Game::checkForCollision() {
    // Check for collision between player and enemies
    for (int i = 0; i < noOfEnemies; i++) {
        if ((int(p->car.getPosition().x) == int((*(en + i))->car.getPosition().x)) &&
            (int(p->car.getPosition().y) == int((*(en + i))->car.getPosition().y))) {
            p->modifyHealth(-1);

            p->car.setPosition(p->R[0].G.x, p->R[0].G.y);
            p->currRing = 0;
            p->moveDir = 'r';
        }
    }
}

// Function to remove a food item from the array
bool Game::popFood(int i) {
    // Pop a food item from the array
    if ((i < 0) || (i > noOfFoods)) {
        return false;
    }

    delete* (foods + i);

    for (int j = i; j < noOfFoods - 1; j++) {
        *(foods + j) = *(foods + j + 1);
    }
    noOfFoods--;

    return true;
}

// Function to check for collision between player and food items
void Game::checkForFoodCollision() {
    // Check for collision between player and food items
    for (int i = 0; i < noOfFoods; i++) {
        if ((int(p->car.getPosition().x) == int((*(foods + i))->food.getPosition().x)) &&
            (int(p->car.getPosition().y) == int((*(foods + i))->food.getPosition().y))) {
            p->modifyHealth((*(foods + i))->getExtraLives());
            score += (*(foods + i))->getScore();

            // Handle special effects of food items
            if (noOfEnemies) {
                if ((*(foods + i))->getHideEnemy()) {
                    for (int i = 0; i < noOfEnemies; i++) {
                        delete* (en + i);
                    }
                    delete[] en;
                    noOfInactiveEnemies = noOfEnemies;
                    noOfEnemies = 0;

                    enemyClock.restart();
                }
            }

            if (!(p->getBoost())) {
                if ((*(foods + i))->getBoost()) {
                    p->setSpeed(p->getSpeed() * 1.5);
                    p->setBoost(true);
                    boostClock.restart();
                }
            }

            popFood(i);
        }
    }
}

// Function to check if the game has ended
bool Game::endGame() {
    // Check if the game has ended (player health is zero or no more foods)
    if (p->getHealth() == 0) {
        winLose = false;
        return true;
    }
    if (noOfFoods == 0) {
        winLose = true;
        return true;
    }
    return false;
}

// Function to pause the game
void Game::pauseGame() {
    // Display "Paused" text on the screen
    playPause.setString("Paused");
    playPause.setFont(font);
    playPause.setCharacterSize(60);
    playPause.setPosition(100, 366);
}

// Function to resume the game
void Game::resumeGame() {
    // Remove "Paused" text from the screen
    playPause.setString("");
    playPause.setFont(font);
    playPause.setCharacterSize(60);
    playPause.setPosition(100, 366);
}

// Function to create enemies based on the game level
void Game::createEnemies() {
    // Create enemies based on the game level
    if (level == 1) {
        noOfEnemies = 1;
        en = new Enemy * [noOfEnemies];
        for (int i = 0; i < noOfEnemies; i++) {
            *(en + i) = new Enemy(".\\img\\fanoon_sprites\\spooder.png", 2, 1);
        }
    }
    else if (level == 2) {
        noOfEnemies = 1;
        en = new Enemy * [noOfEnemies];
        for (int i = 0; i < noOfEnemies; i++) {
            *(en + i) = new Enemy(".\\img\\fanoon_sprites\\spooder.png", 3, 0);
        }
    }
    else if (level == 3) {
        noOfEnemies = 1;
        en = new Enemy * [noOfEnemies];
        for (int i = 0; i < noOfEnemies; i++) {
            *(en + i) = new Enemy(".\\img\\fanoon_sprites\\spooder.png", 3, 0);
            (*(en + i))->setSpeed(0.5);
        }
    }
    else if (level == 4) {
        noOfEnemies = 2;
        en = new Enemy * [noOfEnemies];
        for (int i = 0; i < noOfEnemies; i++) {
            *(en + i) = new Enemy(".\\img\\fanoon_sprites\\spooder.png", 4, 0);
        }
    }
}

// Function to return enemies to the game after a certain time period
void Game::returnEnemy() {
    // Return enemies to the game after a certain time period
    if (noOfEnemies == 0) {
        if (int((enemyClock.getElapsedTime()).asSeconds()) >= 10) {
            createEnemies();
        }
    }
}

// Function to check if the player's boost has ended
bool Game::endBoost() {
    // Check if player's boost has ended
    if (p->getBoost()) {
        if (boostClock.getElapsedTime().asSeconds() >= 10) {
            p->setBoost(false);
            p->setSpeed(p->getSpeed() / 1.5);
            return true;
        }
    }
    return false;
}

// Constructor
Game::Game(int l) {
    bg_texture.loadFromFile("img/maze1.png");
    background.setTexture(bg_texture);
    background.setScale(1, 1);
    p = new Player(".\\img\\fanoon_sprites\\duo.png");

    score = 0;
    level = l;
    createEnemies();

    font.loadFromFile(".\\fonts\\ARCADECLASSIC.TTF");
    livesText.setFont(font);
    livesText.setCharacterSize(30);
    livesText.setFillColor(Color::White);

    scoresText.setFont(font);
    scoresText.setCharacterSize(30);
    scoresText.setFillColor(Color::White);
    scoresText.setPosition(0, 20);

    srand(time(0));
    noOfFoods = (Food::N) * (Food::N);
    foods = new Food * [noOfFoods];
    int x = 0;
    int y = 0;
    for (int i = 0; i < noOfFoods; i++) {
        int random = rand() % 100;
        if (random <= 70) {
            *(foods + i) = new RedFood(Food::coordArr[x], Food::coordArr[y]);
        }
        if ((random > 70) && (random <= 80)) {
            *(foods + i) = new GreenFood(Food::coordArr[x], Food::coordArr[y]);
        }
        if ((random > 80) && (random <= 90)) {
            *(foods + i) = new OrangeFood(Food::coordArr[x], Food::coordArr[y]);
        }
        if (random > 90) {
            *(foods + i) = new WhiteFood(Food::coordArr[x], Food::coordArr[y]);
        }

        x++;
        if (x == Food::N) {
            x = 0;
            y++;
        }
    }
}

// Destructor
Game::~Game() {
    delete p;
    if (noOfEnemies) {
        for (int i = 0; i < noOfEnemies; i++) {
            delete* (en + i);
        }
        delete[] en;
    }

    if (noOfFoods) {
        for (int i = 0; i < noOfFoods; i++) {
            delete* (foods + i);
        }
    }
    delete[] foods;
}

// Function to start the game
void Game::start_game() {
    srand(time(0));
    RenderWindow window(VideoMode(780, 780), title);
    bool leftClick = false, rightClick = false;

    while (window.isOpen()) {
        Event e;
        while (window.pollEvent(e)) {
            if (e.type == Event::Closed) {
                window.close();
            }
        }

        // Handle player movement based on key presses
        if (Keyboard::isKeyPressed(Keyboard::I)) {
            leftClick = true;
        }

        if (e.type == sf::Event::KeyReleased) {
            if (e.key.code == sf::Keyboard::I) {
                if (leftClick) {
                    p->move("l");
                    leftClick = false;
                }
            }
        }

        if (Keyboard::isKeyPressed(Keyboard::O)) {
            rightClick = true;
        }

        if (e.type == sf::Event::KeyReleased) {
            if (e.key.code == sf::Keyboard::O) {
                if (rightClick) {
                    p->move("r");
                    rightClick = false;
                }
            }
        }

        // Game logic functions
        p->moveFwd();

        for (int i = 0; i < noOfEnemies; i++) {
            (*(en + i))->moveFwd(p->currRing);
        }

        checkForCollision();

        livesText.setString(p->getStrHealth());
        scoresText.setString("Score " + to_string(score));

        checkForFoodCollision();
        returnEnemy();
        endBoost();

        // Render the game elements
        window.clear(Color::Black);
        window.draw(background);
        window.draw(livesText);
        window.draw(scoresText);

        for (int i = 0; i < noOfFoods; i++) {
            window.draw((*(foods + i))->food);
        }
        window.draw(p->car);
        for (int i = 0; i < noOfEnemies; i++) {
            window.draw((*(en + i))->car);
        }

        // Pause game functionality
        if (Keyboard::isKeyPressed(Keyboard::P)) {
            pauseGame();
            window.draw(playPause);
            window.display();
            while (1) {
                if (Keyboard::isKeyPressed(Keyboard::R))
                    break;
            }
            resumeGame();
            window.draw(playPause);
            window.display();
        }

        // Check for game end conditions
        if (endGame()) {
            window.display();
            break;
        }

        window.display();
    }
}

// Getter for the player's score
int Game::getScore() {
    return score;
}

// Getter for the current game level
int Game::getLevel() {
    return level;
}

// Getter for the game result (win or lose)
bool Game::getWinLose() {
    return winLose;
}
