
#include <SFML/Graphics.hpp>
#include <time.h>
#include <iostream>
using namespace std;
#include "player.h"
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
    // add other game attributes
    std::vector<Box> smallBoxes; // Declare the vector here
    int direction = 1; // Variable to store the direction of movement


    Game()
    {
        p = new Player(".\\img\\enemy_1.png");
        bg_texture.loadFromFile("img/background.jpg");
        background.setTexture(bg_texture);
        background.setScale(2, 1.5);
        initializeSmallBoxes();

    }
    void initializeSmallBoxes()
    {
        // Add code here to initialize small boxes as needed
        smallBoxes.emplace_back(200.f, 300.f, 30.f, 30.f, 1); // Initial direction is 1 (right)
        smallBoxes.emplace_back(400.f, 500.f, 30.f, 30.f, -1); // Initial direction is -1 (left)
    }

    void start_game()
    {
        srand(time(0));
        RenderWindow window(VideoMode(780, 780), title);
        Clock clock;
        float timer = 0;

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

            if (Keyboard::isKeyPressed(Keyboard::Left)) //If left key is pressed
                p->move("l");    // Player will move to left
            if (Keyboard::isKeyPressed(Keyboard::Right)) // If right key is pressed
                p->move("r");  //player will move to right
            if (Keyboard::isKeyPressed(Keyboard::Up)) //If up key is pressed
                p->move("u");    //playet will move upwards
            if (Keyboard::isKeyPressed(Keyboard::Down)) // If down key is pressed
                p->move("d");  //player will move downwards

            ////////////////////////////////////////////////
            /////  Call your functions here            ////
            //////////////////////////////////////////////

            window.clear(Color::Black); //clears the screen
            window.draw(background);  // setting background
           

            // Move and draw small boxes
            for (auto& smallBox : smallBoxes)
            {
                // Adjust the movement speed
                float speed = 2.0f;

                // Move the box
                smallBox.move(speed, 0.0f);

                // Check if the box reached the right or left boundary
                if (smallBox.shape.getPosition().x + smallBox.shape.getSize().x > window.getSize().x ||
                    smallBox.shape.getPosition().x < 0)
                {
                    // Reflect the direction if the box reached the boundary
                    smallBox.direction = -smallBox.direction;
                }

                window.draw(smallBox.shape);
            }


            window.display();  //Displying all the sprites
        }


    }


};

