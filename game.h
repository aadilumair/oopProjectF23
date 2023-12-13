#include<cstdlib>
#include<time.h>
#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include <time.h>
#include <Windows.h>
#include <iostream>
using namespace std;
#include "car.h"
#include "food.h"
const char title[] = "OOP-Project, Fall-2023";
using namespace sf;

class Game{
private:
    void checkForCollision();
    bool popFood(int i);
    void checkForFoodCollision();
    bool endGame();
    void pauseGame();
    void resumeGame();
    void returnEnemy();
    bool endBoost();

    int score;

    Text endMessage;
    Text playPause;
    Clock enemyClock;
    Clock boostClock;


public:
    Sprite background; //Game background sprite
    Texture bg_texture;
    Font font;
    Text livesText;
    Text scoresText;
    Player* p; //player 
    
    int noOfEnemies;
    int noOfInactiveEnemies;
    Enemy** en;

    int noOfFoods;
    Food** foods;

    Game(int enemies);
    ~Game();
    

    void start_game();
};

void Game::checkForCollision() {
    for (int i = 0; i < noOfEnemies; i++) {
        if ((int(p->car.getPosition().x) == int((*en + i)->car.getPosition().x)) &&
            (int(p->car.getPosition().y) == int((*en + i)->car.getPosition().y))) {
            p->modifyHealth(-1);
            
            p->car.setPosition(p->R[0].G.x, p->R[0].G.y);
            p->currRing = 0;
            p->moveDir = 'r';
        }
    }
}

bool Game::popFood(int i) {
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

void Game::checkForFoodCollision() {
    for (int i = 0; i < noOfFoods; i++) {
        if ((int(p->car.getPosition().x) == int((*(foods + i))->food.getPosition().x)) &&
            (int(p->car.getPosition().y) == int((*(foods + i))->food.getPosition().y))) {
            p->modifyHealth((*(foods+i))->getExtraLives());
            score += (*(foods + i))->getScore();

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

bool Game::endGame() {
    if (p->getHealth() == 0) {
        endMessage.setString("Wasted");
        endMessage.setFont(font);
        endMessage.setCharacterSize(60);
        endMessage.setPosition(100, 366);
        return true;
    }
    if (noOfFoods == 0) {
        endMessage.setString("You   win   this   level!");
        endMessage.setFont(font);
        endMessage.setCharacterSize(60);
        endMessage.setPosition(10, 366);
        return true;
    }
    return false;
}

void Game::pauseGame() {
    playPause.setString("Paused");
    playPause.setFont(font);
    playPause.setCharacterSize(60);
    playPause.setPosition(100, 366);
}

void Game::resumeGame() {
    playPause.setString("");
    playPause.setFont(font);
    playPause.setCharacterSize(60);
    playPause.setPosition(100, 366);
}

void Game::returnEnemy() {
    
    if (noOfEnemies == 0) {
        if (int((enemyClock.getElapsedTime()).asSeconds()) >= 10) {
            noOfEnemies = noOfInactiveEnemies;
            en = new Enemy * [noOfEnemies];

            for (int i = 0; i < noOfEnemies; i++) {
                *(en + i) = new Enemy(".\\img\\fanoon_sprites\\spooder.png", 2, 1);
            }
        }
    }
    
    
}

bool Game::endBoost() {
    if (p->getBoost()) {
        if (boostClock.getElapsedTime().asSeconds() >= 10) {
            p->setBoost(false);
            p->setSpeed(p->getSpeed() / 1.5);
            return true;
        }
    }
    return false;
}

Game::Game(int enemies)
{

    bg_texture.loadFromFile("img/maze1.png");
    background.setTexture(bg_texture);
    background.setScale(1, 1);
    p = new Player(".\\img\\fanoon_sprites\\duo.png");

    score = 0;

    noOfEnemies = enemies;

    en = new Enemy * [noOfEnemies];

    for (int i = 0; i < noOfEnemies; i++) {
        *(en + i) = new Enemy(".\\img\\fanoon_sprites\\spooder.png", 2, 1);
    }

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
        if ((random > 70)&&(random <= 80)) {
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
 
void Game::start_game()
{
    srand(time(0));
    RenderWindow window(VideoMode(780, 780), title);
    bool leftClick = false, rightClick = false;
    while (window.isOpen())
    {
        Event e;
        while (window.pollEvent(e))
        {
            if (e.type == Event::Closed) // If cross/close is clicked/pressed
                window.close(); //close the game                        	    
        }

        if (Keyboard::isKeyPressed(Keyboard::Left)) //If left key is CLICKED
            leftClick = true;

        if (e.type == sf::Event::KeyReleased) {
            if (e.key.code == sf::Keyboard::Left) {
                if (leftClick) {
                    p->move("l");    // Player will move to INNER RING
                    leftClick = false;
                }
            }
        }

        if (Keyboard::isKeyPressed(Keyboard::Right)) // If right key is CLICKED
            rightClick = true;
        if (e.type == sf::Event::KeyReleased) {
            if (e.key.code == sf::Keyboard::Right) {
                if (rightClick) {
                    p->move("r");    // Player will move to OUTER RING
                    rightClick = false;
                }
            }
        }

        ////////////////////////////////////////////////
        /////  Call your functions here            ////
        //////////////////////////////////////////////
        p->moveFwd();

        for (int i = 0; i < noOfEnemies; i++) {
            (*(en+i))->moveFwd(p->currRing);
        }


        checkForCollision();

        livesText.setString(p->getStrHealth());
        scoresText.setString("Score " + to_string(score));

        checkForFoodCollision();
        returnEnemy();
        endBoost();

        window.clear(Color::Black); //clears the screen
        window.draw(background);  // setting background
        
        window.draw(livesText);
        window.draw(scoresText);

        for (int i = 0; i < noOfFoods; i++) {
            window.draw((*(foods + i))->food);
        }
        window.draw(p->car);
        for (int i = 0; i < noOfEnemies; i++) {
            window.draw((*(en + i))->car);
        }

        if (Keyboard::isKeyPressed(Keyboard::P)) {
            pauseGame();
            window.draw(playPause);
            window.display();
            while (1) {
                if(Keyboard::isKeyPressed(Keyboard::R))
                    break;
            }
            resumeGame();
            window.draw(playPause);
            window.display();
        }

        if (endGame()){
            window.draw(endMessage);
            window.display();
            break;
        }



        window.display();  //Displying all the sprites
    }
    Sleep(10000);
    

}