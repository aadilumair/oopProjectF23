#include "point.h"
#include <SFML/Graphics.hpp>
#include<string.h>
using namespace sf;

class Car
{
public:
	void getPosition();
	bool setPosition(Point loc);
	float getSpeed();
	void setSpeed(float spd);
	Sprite car;

protected:
	Point position;
	float speed;
	
	Texture carTexture;
};

class Player : public Car{
public:
	Player(std::string png_path)
	{

		speed = 0.1;
		carTexture.loadFromFile(png_path);
		car.setTexture(carTexture);
		position.setX(340);
		position.setY(700);
		car.setPosition(position.getX(), position.getY());
		car.setScale(0.75, 0.75);
	}
	void fire()
	{

	}
	void move(std::string s) {
		float delta_x = 0, delta_y = 0;
		if (s == "l")
			delta_x = -1;
		//move the player left
		else if (s == "r")
			delta_x = 1;
			//move the player right
		if (s == "u")
			delta_y = -1;
		else if (s == "d")
			delta_y = 1;

		delta_x *= speed;
		delta_y *= speed;

		car.move(delta_x, delta_y);

	}

};
