#include <SFML/Graphics.hpp>
#include<string.h>
using namespace sf;

struct Coord {
	int x, y;
};
struct Ring
{
	Coord A, B, C, D;
};


class Car
{
public:
	float getSpeed();
	void setSpeed(float spd);
	Sprite car;
	Ring R[4];

protected:
	float speed;
	Texture carTexture;
	int currRing;
	char moveDir;
};

float Car::getSpeed() {
	return speed;
}
void Car::setSpeed(float spd) {
	speed = spd;
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
	void moveFwd();
};

Player::Player(std::string png_path){
	speed = 0.5;
	health = 3;
	carTexture.loadFromFile(png_path);
	car.setTexture(carTexture);
	car.setPosition(366, 634);
	car.setScale(0.06, 0.06);

	moveDir = 'r';

	R[0].A.x = 99;
	R[0].A.y = 99;
	R[0].B.x = 99;
	R[0].B.y = 634;
	R[0].C.x = 634;
	R[0].C.y = 634;
	R[0].D.x = 634;
	R[0].D.y = 99;

	R[1].A.x = 171;
	R[1].A.y = 171;
	R[1].B.x = 171;
	R[1].B.y = 560;
	R[1].C.x = 560;
	R[1].C.y = 560;
	R[1].D.x = 560;
	R[1].D.y = 171;

	R[2].A.x = 235;
	R[2].A.y = 235;
	R[2].B.x = 235;
	R[2].B.y = 498;
	R[2].C.x = 498;
	R[2].C.y = 498;
	R[2].D.x = 498;
	R[2].D.y = 235;

	R[3].A.x = 289;
	R[3].A.y = 289;
	R[3].B.x = 289;
	R[3].B.y = 440;
	R[3].C.x = 440;
	R[3].C.y = 440;
	R[3].D.x = 440;
	R[3].D.y = 289;




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

void Player::moveFwd() {
	
	
		cout << "";
		if ((car.getPosition().x == R[currRing].A.x) && (car.getPosition().y == R[currRing].A.y))//corner A 
		{
			moveDir = 'd';//set movement to down
		}
		if ((car.getPosition().x == R[currRing].B.x) && (car.getPosition().y == R[currRing].B.y))//corner B
		{
			moveDir = 'r';//set movement to right
		}
		if ((car.getPosition().x == R[currRing].C.x) && (car.getPosition().y == R[currRing].C.y))//corner C
		{
			moveDir = 'u';//set movement to up
		}
		if ((car.getPosition().x == R[currRing].D.x) && (car.getPosition().y == R[currRing].D.y))//corner D
		{
			moveDir = 'l';//set movement to left
		}
	
	

	if (moveDir == 'u') {
		car.move(0, -1 * speed);
	}
	if (moveDir == 'd') {
		car.move(0, 1 * speed);
	}
	if (moveDir == 'l') {
		car.move(-1 * speed, 0);
	}
	if (moveDir == 'r') {
		car.move(1 * speed, 0);
	}
}

class Enemy : Car
{
public:
	Enemy(std::string png_path);
	void move();
	void setMaxRing(int r);
	void setCurrRing(int r);
	void randChangeRing();

private:
	int maxRing;
};

Enemy::Enemy(std::string png_path)
{
	speed = 0.1;
	maxRing = 0;
	currRing = 0;
	carTexture.loadFromFile(png_path);
	car.setTexture(carTexture);
	car.setPosition(340, 700);
	car.setScale(0.75, 0.75);
}

void Enemy::move() {
	float delta_x = 0, delta_y = 0;
	string s = "l";
	if (s == "l")
		delta_x = -1;
	//move the enemy left
	else if (s == "r")
		delta_x = 1;
	//move the enemy right
	if (s == "u")
		delta_y = -1;
	else if (s == "d")
		delta_y = 1;

	delta_x *= speed;
	delta_y *= speed;

	car.move(delta_x, delta_y);

}

void Enemy::setMaxRing(int r){
	maxRing = r;
}
void Enemy::setCurrRing(int r){
	maxRing = r;
}
void Enemy::randChangeRing(){
	//if at turnPoint, then take random value form 0 to maxRing and change currRing to this value. Also move the car to that track
}