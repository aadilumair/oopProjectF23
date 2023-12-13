#include <SFML/Graphics.hpp>
#include "game.h"
#include "Highscore.h"

using namespace sf;

class Menu {
    Sprite background; // Game background sprite
    Texture bg_texture;
    const std::string title = "OOP-Project, Fall-2023"; // Replace with your game title

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
                    window.close(); // Close the game                        	    
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
                    window.close(); // Close the game                        	    
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

    void levelSelect() {
        bg_texture.loadFromFile("img/levelSelector.png");
        background.setTexture(bg_texture);
        background.setScale(1, 1);
        RenderWindow window(VideoMode(780, 780), title);
        while (window.isOpen()) {
            Event e;
            while (window.pollEvent(e))
            {
                if (e.type == Event::Closed) // If cross/close is clicked/pressed
                    window.close(); // Close the game                        	    
            }
            window.clear(Color::Black);
            window.draw(background);
            window.display();
            if (Keyboard::isKeyPressed(Keyboard::Num1)) {
                window.close();
                playGame(1);
            }
            if (Keyboard::isKeyPressed(Keyboard::Num2)) {
                window.close();
                playGame(2);
            }
            if (Keyboard::isKeyPressed(Keyboard::Num3)) {
                window.close();
                playGame(3);
            }
            if (Keyboard::isKeyPressed(Keyboard::Num4)) {
                window.close();
                playGame(4);
            }
            if (Keyboard::isKeyPressed(Keyboard::E)) {
                window.close();
            }
        }
    }

    void playGame(int level = 1) {
        Game g(level);
        g.start_game();
        nextLevel(g.getScore(),g.getLevel(), g.getWinLose());
    }

    void nextLevel(int score, int currLevel, bool winLose) { //Complete display of score and level and also whether you win or lose and to call it from playgame
        bg_texture.loadFromFile("img/endGame.png");
        background.setTexture(bg_texture);
        background.setScale(1, 1);
        RenderWindow window(VideoMode(780, 780), title);

        Font font;
        font.loadFromFile(".\\fonts\\ARCADECLASSIC.TTF");

        Text endMessage;
        if(winLose)
            endMessage.setString("Winner  of  the  Level");
        else
            endMessage.setString("Wasted");
        endMessage.setFont(font);
        endMessage.setCharacterSize(60);
        endMessage.setPosition(100, 250);

        Text levelStr;
        levelStr.setString("Level  " + to_string(currLevel));
        levelStr.setFont(font);
        levelStr.setCharacterSize(30);
        levelStr.setPosition(100, 350);
        Text scoreStr;
        scoreStr.setString("Score  " + to_string(score));
        scoreStr.setFont(font);
        scoreStr.setCharacterSize(30);
        scoreStr.setPosition(100, 400);

        while (window.isOpen()) {
            Event e;
            while (window.pollEvent(e))
            {
                if (e.type == Event::Closed) // If cross/close is clicked/pressed
                    window.close(); // Close the game                        	    
            }
            window.clear(Color::Black);
            window.draw(background);
            window.draw(endMessage);
            window.draw(levelStr);
            window.draw(scoreStr);

            window.display();
            if (Keyboard::isKeyPressed(Keyboard::S)) {
                window.close();
                playGame(currLevel + 1);
            }
            if (Keyboard::isKeyPressed(Keyboard::P)) {
                window.close();
                playGame(currLevel);
            }
            if (Keyboard::isKeyPressed(Keyboard::P)) {
                window.close();
                dispMenu();
            }

            if (Keyboard::isKeyPressed(Keyboard::E)) {
                window.close();
            }
        }
    }

    // New function for displaying instructions
    void dispInstructions() {
        bg_texture.loadFromFile("img/instructions.png");
        background.setTexture(bg_texture);
        background.setScale(1, 1);
        RenderWindow window(VideoMode(780, 780), title);
        while (window.isOpen()) {
            Event e;
            while (window.pollEvent(e))
            {
                if (e.type == Event::Closed) // If cross/close is clicked/pressed
                    window.close(); // Close the game
            }
            window.clear(Color::Black);
            window.draw(background);
            window.display();
            if (Keyboard::isKeyPressed(Keyboard::B)) {
                window.close();
                dispMenu();
            }
        }
    }

public:
    Menu() {
    }

    void dispMenu() {
        bg_texture.loadFromFile("img/newMenu.png");
        background.setTexture(bg_texture);
        background.setScale(1, 1);
        RenderWindow window(VideoMode(780, 780), title);
        while (window.isOpen()) {
            Event e;
            while (window.pollEvent(e))
            {
                if (e.type == Event::Closed) // If cross/close is clicked/pressed
                    window.close(); // Close the game                        	    
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
                dispInstructions();
            }
            if (Keyboard::isKeyPressed(Keyboard::E)) {
                window.close();
            }
            if (Keyboard::isKeyPressed(Keyboard::H)) {
                window.close();
                dispHighScores();
            }
            if (Keyboard::isKeyPressed(Keyboard::L)) {
                window.close();
                levelSelect();
            }
        }
    }
};