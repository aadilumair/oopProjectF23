
#include "game.h"
class Menu {
    Sprite background; //Game background sprite
    Texture bg_texture;

    void dispHelp() {
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
                playGame();
            }
            if (Keyboard::isKeyPressed(Keyboard::B)) {
                window.close();
                dispMenu();
            }
            if (Keyboard::isKeyPressed(Keyboard::E)) {
                window.close();
            }
        }
    }

    void dispHighScores() {
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
                playGame();
            }
            if (Keyboard::isKeyPressed(Keyboard::B)) {
                window.close();
                dispMenu();
            }
            if (Keyboard::isKeyPressed(Keyboard::E)) {
                window.close();
            }
        }
    }

    void playGame() {
        Game g(1);
        g.start_game();
    }

public:
    Menu(){
    }

    void dispMenu(){
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
                playGame();
            }
            if (Keyboard::isKeyPressed(Keyboard::I)) {
                window.close();
                dispHelp();
            }
            if (Keyboard::isKeyPressed(Keyboard::E)) {
                window.close();
            }
            if (Keyboard::isKeyPressed(Keyboard::H)) {
                window.close();
                dispHighScores();
            }
        }
    }

    

};
