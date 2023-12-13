//Aadil Umair 22I-0744 Muhammad Hassan 22I-1011
#pragma once
#include <SFML/Graphics.hpp>
#include <string>
using namespace sf;

// Base class representing a generic food item
class Food
{
public:
    static int N;            // Number of available food items
    static int coordArr[];   // Array storing coordinates for each food item

    Sprite food;             // Sprite for displaying the food item

    // Getters for common properties
    int getScore();
    int getExtraLives();
    float getBoost();
    bool getHideEnemy();
    int getDurationOfEffect();

protected:
    int score;               // Score awarded when the food is consumed
    int extraLives;          // Extra lives awarded when the food is consumed
    float boost;             // Speed boost awarded when the food is consumed
    bool hideEnemy;          // Boolean indicating if the enemy should be hidden
    int durationOfEffect;    // Duration of the food item's effect

    Texture tex;             // Texture for the food item
};

// Initialization of static members
int Food::N = 8;
int Food::coordArr[] = { 99, 171, 235, 289, 440, 498, 560, 634 };

// Implementation of common getters for Food class
int Food::getScore() {
    return score;
}

int Food::getExtraLives() {
    return extraLives;
}

float Food::getBoost() {
    return boost;
}

bool Food::getHideEnemy() {
    return hideEnemy;
}

int Food::getDurationOfEffect() {
    return durationOfEffect;
}

// Derived class representing a Red Food item
class RedFood : public Food
{
public:
    RedFood(int x, int y);  // Constructor for RedFood

private:

};

// Constructor for RedFood
RedFood::RedFood(int x, int y)
{
    tex.loadFromFile(".\\img\\fanoon_sprites\\red_rectangle.png");
    food.setTexture(tex);
    food.setScale(0.04, 0.04);
    food.setPosition(x, y);

    // Set properties specific to RedFood
    score = 10;
    extraLives = 0;
    boost = 0;
    hideEnemy = false;
    durationOfEffect = 0;
}

// Derived class representing a Green Food item
class GreenFood : public Food
{
public:
    GreenFood(int x, int y);  // Constructor for GreenFood

private:

};

// Constructor for GreenFood
GreenFood::GreenFood(int x, int y)
{
    tex.loadFromFile(".\\img\\fanoon_sprites\\green_circle.png");
    food.setTexture(tex);
    food.setScale(0.04, 0.04);
    food.setPosition(x, y);

    // Set properties specific to GreenFood
    score = 20;
    extraLives = 1;
    boost = 0;
    hideEnemy = false;
    durationOfEffect = 0;
}

// Derived class representing an Orange Food item
class OrangeFood : public Food
{
public:
    OrangeFood(int x, int y);  // Constructor for OrangeFood

private:

};

// Constructor for OrangeFood
OrangeFood::OrangeFood(int x, int y)
{
    tex.loadFromFile(".\\img\\fanoon_sprites\\orange_pentagon.png");
    food.setTexture(tex);
    food.setScale(0.04, 0.04);
    food.setPosition(x, y);

    // Set properties specific to OrangeFood
    score = 10;
    extraLives = 0;
    boost = 1.5;
    hideEnemy = false;
    durationOfEffect = 10;
}

// Derived class representing a White Food item
class WhiteFood : public Food
{
public:
    WhiteFood(int x, int y);  // Constructor for WhiteFood

private:

};

// Constructor for WhiteFood
WhiteFood::WhiteFood(int x, int y)
{
    tex.loadFromFile(".\\img\\fanoon_sprites\\white_triangle.png");
    food.setTexture(tex);
    food.setScale(0.04, 0.04);
    food.setPosition(x, y);

    // Set properties specific to WhiteFood
    score = 0;
    extraLives = 0;
    boost = 0;
    hideEnemy = true;
    durationOfEffect = 10;
}
