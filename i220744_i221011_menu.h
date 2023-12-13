#include <SFML/Graphics.hpp>
#include "i220744_i221011_game.h"
#include "i220744_i221011_Highscore.h"

using namespace sf;

class Menu {
    Sprite background; // Game background sprite
    Texture bg_texture;
    const std::string title = "OOP-Project, Fall-2023"; // Replace with your game title

    // Function to display help screen
    void dispHelp() {
        // Load background texture
        bg_texture.loadFromFile("img/black.png");
        background.setTexture(bg_texture);
        background.setScale(1, 1);

        // Create a window
        RenderWindow window(VideoMode(780, 780), title);

        while (window.isOpen()) {
            Event e;
            while (window.pollEvent(e)) {
                if (e.type == Event::Closed)
                    window.close(); // Close the game
            }

            // Draw the background
            window.clear(Color::Black);
            window.draw(background);
            window.display();

            // Check for key presses to navigate
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

    // Function to display high scores screen
    void dispHighScores() {
        // Load background texture
        bg_texture.loadFromFile("img/black.png");
        background.setTexture(bg_texture);
        background.setScale(1, 1);

        // Create a window
        RenderWindow window(VideoMode(780, 780), title);

        while (window.isOpen()) {
            Event e;
            while (window.pollEvent(e)) {
                if (e.type == Event::Closed)
                    window.close(); // Close the game
            }

            // Draw the background
            window.clear(Color::Black);
            window.draw(background);
            window.display();

            // Check for key presses to navigate
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

    // Function to display level selection screen
    void levelSelect() {
        // Load background texture
        bg_texture.loadFromFile("img/levelSelector.png");
        background.setTexture(bg_texture);
        background.setScale(1, 1);

        // Create a window
        RenderWindow window(VideoMode(780, 780), title);

        while (window.isOpen()) {
            Event e;
            while (window.pollEvent(e)) {
                if (e.type == Event::Closed)
                    window.close(); // Close the game
            }

            // Draw the background
            window.clear(Color::Black);
            window.draw(background);
            window.display();

            // Check for key presses to select levels
            if (Keyboard::isKeyPressed(Keyboard::Num1)) {
                window.close();
                playGame(1);
            }
            if (Keyboard::isKeyPressed(Keyboard::Num2)) {
                window.close();
                playGame(2);
            }
            // ... repeat for other levels
            if (Keyboard::isKeyPressed(Keyboard::E)) {
                window.close();
            }
        }
    }

    // Function to play the game at a specific level
    void playGame(int level = 1) {
        Game g(level);
        g.start_game();
        nextLevel(g.getScore(), g.getLevel(), g.getWinLose());
    }

    // Function to display end-of-level screen
    void nextLevel(int score, int currLevel, bool winLose) {
        // Load background texture
        bg_texture.loadFromFile("img/endGame.png");
        background.setTexture(bg_texture);
        background.setScale(1, 1);

        // Create a window
        RenderWindow window(VideoMode(780, 780), title);

        // Load font for text display
        Font font;
        font.loadFromFile(".\\fonts\\ARCADECLASSIC.TTF");

        // Set up text for display
        Text endMessage;
        if (winLose)
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
            while (window.pollEvent(e)) {
                if (e.type == Event::Closed)
                    window.close(); // Close the game
            }

            // Draw the background and text
            window.clear(Color::Black);
            window.draw(background);
            window.draw(endMessage);
            window.draw(levelStr);
            window.draw(scoreStr);
            window.display();

            // Check for key presses to navigate
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

    // Function to display instructions screen
    void dispInstructions() {
        // Load background texture
        bg_texture.loadFromFile("img/instructions.png");
        background.setTexture(bg_texture);
        background.setScale(1, 1);

        // Create a window
        RenderWindow window(VideoMode(780, 780), title);

        while (window.isOpen()) {
            Event e;
            while (window.pollEvent(e)) {
                if (e.type == Event::Closed)
                    window.close(); // Close the game
            }

            // Draw the background
            window.clear(Color::Black);
            window.draw(background);
            window.display();

            // Check for key press to return to menu
            if (Keyboard::isKeyPressed(Keyboard::B)) {
                window.close();
                dispMenu();
            }
        }
    }

public:
    Menu() {
    }

    // Function to display the main menu
    void dispMenu() {
        // Load background texture
        bg_texture.loadFromFile("img/newMenu.png");
        background.setTexture(bg_texture);
        background.setScale(1, 1);

        // Create a window
        RenderWindow window(VideoMode(780, 780), title);

        while (window.isOpen()) {
            Event e;
            while (window.pollEvent(e)) {
                if (e.type == Event::Closed)
                    window.close(); // Close the game
            }

            // Draw the background
            window.clear(Color::Black);
            window.draw(background);
            window.display();

            // Check for key presses to navigate
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
