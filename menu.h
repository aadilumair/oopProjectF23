
#include "game.h"
class Menu {
    Sprite background; //Game background sprite
    Texture bg_texture;

    void display_instructions() {
        bg_texture.loadFromFile("img/black.png");
        background.setTexture(bg_texture);
        background.setScale(1, 1);
        RenderWindow window(VideoMode(780, 780), title);
        while (window.isOpen()) {
            Event e;
            while (window.pollEvent(e))
            {
                if (e.type == Event::Closed) // If cross/close is clicked/pressed
                    window.close(); //close the game                        	    
            }
            window.clear(Color::Black);
            window.draw(background);
            window.display();
            if (Keyboard::isKeyPressed(Keyboard::S)) {
                window.close();
                Game g;
                g.start_game();
            }
            if (Keyboard::isKeyPressed(Keyboard::B)) {
                window.close();
                display_menu();
            }
            if (Keyboard::isKeyPressed(Keyboard::E)) {
                window.close();
            }
            if (Keyboard::isKeyPressed(Keyboard::H)) {
                std::cout << "H pressed";
                window.close();
            }
        }
    }

public:
    Menu()
    {
    }

    void display_menu(){
        bg_texture.loadFromFile("img/newMenu.png");
        background.setTexture(bg_texture);
        background.setScale(1, 1);
        RenderWindow window(VideoMode(780, 780), title);
        while (window.isOpen()) {
            Event e;
            while (window.pollEvent(e))
            {
                if (e.type == Event::Closed) // If cross/close is clicked/pressed
                    window.close(); //close the game                        	    
            }
            window.clear(Color::Black);
            window.draw(background);
            window.display();
            if (Keyboard::isKeyPressed(Keyboard::S)) {
                window.close();
                Game g;
                g.start_game();
            }
            if (Keyboard::isKeyPressed(Keyboard::I)) {
                window.close();
                display_instructions();
            }
            if (Keyboard::isKeyPressed(Keyboard::E)) {
                window.close();
            }
            if (Keyboard::isKeyPressed(Keyboard::H)) {
                std::cout << "H pressed";
                window.close();
            }
        }
    }

    

};
