#pragma once
#include <SFML/Graphics.hpp>
#include<string.h>
using namespace sf;

class Food
{
public:
	static int N;
	static int coordArr[];

	Sprite food;

protected:
	int score;
	int extraLives;
	float boost;
	bool hideEnemy;

	int durationOfEffect;

	Texture tex;
};

int Food::N = 8;
int Food::coordArr[] = { 99, 171, 235, 289, 440, 498, 560, 634 };

class RedFood : public Food
{
public:
	RedFood(int x, int y);

private:

};

RedFood::RedFood(int x, int y)
{
	tex.loadFromFile(".\\img\\fanoon_sprites\\red_rectangle.png");
	food.setTexture(tex);
	food.setScale(0.04, 0.04);
	food.setPosition(x, y);

	score = 10;
	extraLives = 0;
	boost = 0;
	hideEnemy = false;
	durationOfEffect = 0;
}


class GreenFood : public Food
{
public:
	GreenFood(int x, int y);

private:

};

GreenFood::GreenFood(int x, int y)
{
	tex.loadFromFile(".\\img\\fanoon_sprites\\green_circle.png");
	food.setTexture(tex);
	food.setScale(0.04, 0.04);
	food.setPosition(x, y);

	score = 20;
	extraLives = 1;
	boost = 0;
	hideEnemy = false;
	durationOfEffect = 0;
}


class OrangeFood : public Food
{
public:
	OrangeFood(int x, int y);

private:

};

OrangeFood::OrangeFood(int x, int y)
{
	tex.loadFromFile(".\\img\\fanoon_sprites\\orange_pentagon.png");
	food.setTexture(tex);
	food.setScale(0.04, 0.04);
	food.setPosition(x, y);

	score = 10;
	extraLives = 0;
	boost = 1.5;
	hideEnemy = false;
	durationOfEffect = 10;
}


class WhiteFood : public Food
{
public:
	WhiteFood(int x, int y);

private:

};

WhiteFood::WhiteFood(int x, int y)
{
	tex.loadFromFile(".\\img\\fanoon_sprites\\white_triangle.png");
	food.setTexture(tex);
	food.setScale(0.04, 0.04);
	food.setPosition(x, y);

	score = 0;
	extraLives = 0;
	boost = 0;
	hideEnemy = true;
	durationOfEffect = 10;
}


