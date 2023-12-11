
#include <SFML/Graphics.hpp>
#include <time.h>
#include <iostream>
using namespace std;
#include "car.h"
const char title[] = "OOP-Project, Spring-2023";
using namespace sf;



class Box
{
public:
    RectangleShape shape;
    int direction; // Direction of movement for the box

    Box(float x, float y, float width, float height, int initialDirection)
        : direction(initialDirection)
    {
        shape.setSize(Vector2f(width, height));
        shape.setPosition(x, y);
        shape.setFillColor(Color::Red); // Adjust the color as needed
    }

    void move(float speed, float offsetY)
    {
        shape.move(speed * direction, offsetY);
    }
};

class Game
{
public:
    Sprite background; //Game background sprite
    Texture bg_texture;
    Player* p; //player 
    // add other game attributesstd::vector<Box> smallBoxes; // Declare the vector here
    int direction = 1; // Variable to store the direction of movement
    
    int noOfEnemies;
    Enemy** en;


    Game(int enemies)
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
    }

    ~Game(){
        delete p;
        for (int i = 0; i < noOfEnemies; i++) {
            delete *(en + i);
        }
        delete en;
    }

    void start_game()
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
            window.clear(Color::Black); //clears the screen
            window.draw(background);  // setting background
            window.draw(p->car);
            window.draw((*en)->car);
           

            


            window.display();  //Displying all the sprites
        }


    }


};

