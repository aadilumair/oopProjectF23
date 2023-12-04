#include <SFML/Graphics.hpp>
#include<string.h>
using namespace sf;

class Car
{
public:
	float getSpeed();
	void setSpeed(float spd);
	Sprite car;

protected:
	float speed;
	Texture carTexture;
};

float Car::getSpeed() {

}
void Car::setSpeed(float spd) {

}



class Player : public Car{
private:
	int health;

public:
	Player(std::string png_path);
	int getHealth();
	bool setHealth(int);
	bool modifyHealth(int);
	void move(std::string s);
};

Player::Player(std::string png_path){
	speed = 0.1;
	health = 3;
	carTexture.loadFromFile(png_path);
	car.setTexture(carTexture);
	car.setPosition(340, 700);
	car.setScale(0.75, 0.75);
}

int Player::getHealth() {
	return health;
}
bool Player::setHealth(int h) {
	if (h >= 0) {
		health = h;
		return true;
	}
	return false;
}

bool Player::modifyHealth(int h) {
	if ((h + health) >= 0) {
		health += h;
		return true;
	}
	return false;
}

void Player::move(std::string s) {
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

class Enemy : Car
{
public:
	Enemy(std::string png_path);
	void move(std::string s);

private:
	int maxRing;
};

Enemy::Enemy(std::string png_path)
{
	speed = 0.1;
	maxRing = 0;
	carTexture.loadFromFile(png_path);
	car.setTexture(carTexture);
	car.setPosition(340, 700);
	car.setScale(0.75, 0.75);
}

void Enemy::move(std::string s) {
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