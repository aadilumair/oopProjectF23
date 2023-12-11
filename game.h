
#include <SFML/Graphics.hpp>
#include <time.h>
#include <iostream>
using namespace std;
#include "car.h"
const char title[] = "OOP-Project, Fall-2023";
using namespace sf;

class Game{
private:
    void checkForCollision();


public:
    Sprite background; //Game background sprite
    Texture bg_texture;
    Font font;
    Text livesText;
    Player* p; //player 
    
    int noOfEnemies;
    Enemy** en;

    Game(int enemies);
    ~Game();
    

    void start_game();
};

void Game::checkForCollision() {
    for (int i = 0; i < noOfEnemies; i++) {
        if ((int(p->car.getPosition().x) == int((*en + i)->car.getPosition().x)) &&
            (int(p->car.getPosition().y) == int((*en + i)->car.getPosition().y))) {
            p->setHealth(p->getHealth() - 1);
            
            p->car.setPosition(p->R[0].G.x, p->R[0].G.y);
            p->currRing = 0;
            p->moveDir = 'r';
        }
    }
}

Game::Game(int enemies)
{

    bg_texture.loadFromFile("img/maze1.png");
    background.setTexture(bg_texture);
    background.setScale(1, 1);
    p = new Player(".\\img\\fanoon_sprites\\duo.png");

    noOfEnemies = enemies;

    en = new Enemy * [noOfEnemies];

    for (int i = 0; i < noOfEnemies; i++) {
        *(en + i) = new Enemy(".\\img\\fanoon_sprites\\spooder.png", 2, 1);
    }

    font.loadFromFile(".\\fonts\\ARCADECLASSIC.TTF");
    livesText.setFont(font);
    livesText.setCharacterSize(30);
    livesText.setFillColor(Color::White);


}

Game::~Game() {
    delete p;
    for (int i = 0; i < noOfEnemies; i++) {
        delete* (en + i);
    }
    delete en;
}

void Game::start_game()
{
    srand(time(0));
    RenderWindow window(VideoMode(780, 780), title);
    Clock clock;
    float timer = 0;
    bool leftClick = false, rightClick = false;
    while (window.isOpen())
    {
        float time = clock.getElapsedTime().asSeconds();
        clock.restart();
        timer += time;
        //cout<<time<<endl; 
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

        if (Keyboard::isKeyPressed(Keyboard::Up)) //If up key is pressed
            p->move("u");    //playet will move upwards
        if (Keyboard::isKeyPressed(Keyboard::Down)) // If down key is pressed
            p->move("d");  //player will move downwards

        ////////////////////////////////////////////////
        /////  Call your functions here            ////
        //////////////////////////////////////////////
        p->moveFwd();
        (*en)->moveFwd();

        checkForCollision();

        livesText.setString(p->getStrHealth());

        window.clear(Color::Black); //clears the screen
        window.draw(background);  // setting background
        window.draw(p->car);
        window.draw((*en)->car);
        window.draw(livesText);





        window.display();  //Displying all the sprites
    }


}