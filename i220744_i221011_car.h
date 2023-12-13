#include <SFML/Graphics.hpp>
#include<string.h>
using namespace sf;

struct Coord {
	int x, y;
};
struct Ring
{
	Coord A, B, C, D, E, F, G, H;
};


class Car
{
public:
	float getSpeed();
	void setSpeed(float spd);
	Sprite car;
	Ring R[4];
	char moveDir;

	int currRing;

protected:
	float speed;
	Texture carTexture;
	virtual bool closeToCar(int x, int y) = 0;
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
	bool boostApplied;

public:
	Player(std::string png_path);
	int getHealth();
	string getStrHealth();
	bool setHealth(int);
	bool modifyHealth(int);
	bool setBoost(bool);
	bool getBoost();
	void move(std::string s);
	void moveFwd();
	bool closeToCar(int x, int y);
};

Player::Player(std::string png_path){
	speed = 0.2;
	boostApplied = false;
	health = 3;
	carTexture.loadFromFile(png_path);
	car.setTexture(carTexture);
	car.setPosition(366, 634);
	car.setScale(0.06, 0.06);

	moveDir = 'r';
	currRing = 0;

	R[0].A.x = 99;
	R[0].A.y = 99;
	R[0].B.x = 99;
	R[0].B.y = 634;
	R[0].C.x = 634;
	R[0].C.y = 634;
	R[0].D.x = 634;
	R[0].D.y = 99;

	R[0].E.x = 366;
	R[0].E.y = 99;
	R[0].F.x = 99;
	R[0].F.y = 366;
	R[0].G.x = 366;
	R[0].G.y = 634;
	R[0].H.x = 634;
	R[0].H.y = 366;

	R[1].A.x = 171;
	R[1].A.y = 171;
	R[1].B.x = 171;
	R[1].B.y = 560;
	R[1].C.x = 560;
	R[1].C.y = 560;
	R[1].D.x = 560;
	R[1].D.y = 171;

	R[1].E.x = 366;
	R[1].E.y = 171;
	R[1].F.x = 171;
	R[1].F.y = 366;
	R[1].G.x = 366;
	R[1].G.y = 560;
	R[1].H.x = 560;
	R[1].H.y = 366;

	R[2].A.x = 235;
	R[2].A.y = 235;
	R[2].B.x = 235;
	R[2].B.y = 498;
	R[2].C.x = 498;
	R[2].C.y = 498;
	R[2].D.x = 498;
	R[2].D.y = 235;

	R[2].E.x = 366;
	R[2].E.y = 235;
	R[2].F.x = 235;
	R[2].F.y = 366;
	R[2].G.x = 366;
	R[2].G.y = 498;
	R[2].H.x = 498;
	R[2].H.y = 366;

	R[3].A.x = 289;
	R[3].A.y = 289;
	R[3].B.x = 289;
	R[3].B.y = 440;
	R[3].C.x = 440;
	R[3].C.y = 440;
	R[3].D.x = 440;
	R[3].D.y = 289;

	R[3].E.x = 366;
	R[3].E.y = 289;
	R[3].F.x = 289;
	R[3].F.y = 366;
	R[3].G.x = 366;
	R[3].G.y = 440;
	R[3].H.x = 440;
	R[3].H.y = 366;
}

int Player::getHealth() {
	return health;
}

string Player::getStrHealth() {
	return "Lives " + to_string(health);
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

bool Player::setBoost(bool isApplied) {
	boostApplied = isApplied;
	return true;
}
bool Player::getBoost() {
	return boostApplied;
}

void Player::move(std::string s) { 
	/*this function moves a player between rings. It check
	if the car is first close to points EFGH. Then it will
	check the direction the car is going and appropriatly 
	moves the car b/w rings*/


	if (closeToCar(R[currRing].E.x, R[currRing].E.y) //Check if the the car is close to a move point
		|| closeToCar(R[currRing].F.x, R[currRing].F.y)
		|| closeToCar(R[currRing].G.x, R[currRing].G.y)
		|| closeToCar(R[currRing].H.x, R[currRing].H.y)
		) {
		if (s == "l") 
		{
			if (currRing < 3) {//Move to inner ring
				currRing++;
				if (moveDir == 'l') {
					car.setPosition(R[currRing].E.x, R[currRing].E.y);
				}
				if (moveDir == 'r') {
					car.setPosition(R[currRing].G.x, R[currRing].G.y);
				}
				if (moveDir == 'u') {
					car.setPosition(R[currRing].H.x, R[currRing].H.y);
				}
				if (moveDir == 'd') {
					car.setPosition(R[currRing].F.x, R[currRing].F.y);
				}
			}
		}
		else if (s == "r") {//move to outer ring
			if (currRing > 0) {
				currRing--;
				if (moveDir == 'l') {
					car.setPosition(R[currRing].E.x, R[currRing].E.y);
				}
				if (moveDir == 'r') {
					car.setPosition(R[currRing].G.x, R[currRing].G.y);
				}
				if (moveDir == 'u') {
					car.setPosition(R[currRing].H.x, R[currRing].H.y);
				}
				if (moveDir == 'd') {
					car.setPosition(R[currRing].F.x, R[currRing].F.y);
				}
			}
		}
	}
	
	
}

void Player::moveFwd() { //This function is the default auto movement of the player counter clockwise
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
		if (car.getPosition().y - 1 * speed < R[currRing].D.y) { //Check if the movement will make it go out of bounds or not
			car.setPosition(R[currRing].D.x, R[currRing].D.y);
		}
		else {
			car.move(0, -1 * speed);
		}
	}
	if (moveDir == 'd') {
		if (car.getPosition().y + 1 * speed > R[currRing].B.y) { //Check if the movement will make it go out of bounds or not
			car.setPosition(R[currRing].B.x, R[currRing].B.y);
		}
		else {
			car.move(0, 1 * speed);
		}	
	}
	if (moveDir == 'l') {
		if (car.getPosition().x - 1 * speed < R[currRing].A.x) { //Check if the movement will make it go out of bounds or not
			car.setPosition(R[currRing].A.x, R[currRing].A.y);
		}
		else {
			car.move(-1 * speed, 0);
		}
	}
	if (moveDir == 'r') {
		if (car.getPosition().x + 1 * speed > R[currRing].C.x) { //Check if the movement will make it go out of bounds or not
			car.setPosition(R[currRing].C.x, R[currRing].C.y);
		}
		else {
			car.move(1 * speed, 0);
		}
	}
}

bool Player::closeToCar(int x, int y) {
	int b = 40;//bound length

	if ((((car.getPosition().y) > (y + b)) || ((car.getPosition().y) < (y - b))))
	{
		return false;
	}

	if ((((car.getPosition().x) > (x + b)) || ((car.getPosition().x) < (x - b))))
	{
		return false;
	}

	return true;
}

class Enemy : public Car
{
public:
	Enemy(std::string png_path, int max, int min);
	void setMaxRing(int r);
	void setCurrRing(int r);
	void randChangeRing();
	void moveFwd(int playerRing);

private:
	int maxRing;
	int minRing;
	void move(int playerRing);
	bool closeToCar(int x, int y);
};

Enemy::Enemy(std::string png_path, int max, int min)
{
	speed = 0.1;
	

	

	R[0].A.x = 99;
	R[0].A.y = 99;
	R[0].B.x = 99;
	R[0].B.y = 634;
	R[0].C.x = 634;
	R[0].C.y = 634;
	R[0].D.x = 634;
	R[0].D.y = 99;

	R[0].E.x = 366;
	R[0].E.y = 99;
	R[0].F.x = 99;
	R[0].F.y = 366;
	R[0].G.x = 366;
	R[0].G.y = 634;
	R[0].H.x = 634;
	R[0].H.y = 366;

	R[1].A.x = 171;
	R[1].A.y = 171;
	R[1].B.x = 171;
	R[1].B.y = 560;
	R[1].C.x = 560;
	R[1].C.y = 560;
	R[1].D.x = 560;
	R[1].D.y = 171;

	R[1].E.x = 366;
	R[1].E.y = 171;
	R[1].F.x = 171;
	R[1].F.y = 366;
	R[1].G.x = 366;
	R[1].G.y = 560;
	R[1].H.x = 560;
	R[1].H.y = 366;

	R[2].A.x = 235;
	R[2].A.y = 235;
	R[2].B.x = 235;
	R[2].B.y = 498;
	R[2].C.x = 498;
	R[2].C.y = 498;
	R[2].D.x = 498;
	R[2].D.y = 235;

	R[2].E.x = 366;
	R[2].E.y = 235;
	R[2].F.x = 235;
	R[2].F.y = 366;
	R[2].G.x = 366;
	R[2].G.y = 498;
	R[2].H.x = 498;
	R[2].H.y = 366;

	R[3].A.x = 289;
	R[3].A.y = 289;
	R[3].B.x = 289;
	R[3].B.y = 440;
	R[3].C.x = 440;
	R[3].C.y = 440;
	R[3].D.x = 440;
	R[3].D.y = 289;

	R[3].E.x = 366;
	R[3].E.y = 289;
	R[3].F.x = 289;
	R[3].F.y = 366;
	R[3].G.x = 366;
	R[3].G.y = 440;
	R[3].H.x = 440;
	R[3].H.y = 366;

	maxRing = max;
	
	minRing = min;
	carTexture.loadFromFile(png_path);
	car.setTexture(carTexture);

	int rand1 = rand() % 100;
	int r;
	if (rand1 < 25)
		r = 0;
	if ((rand1 >= 25) && (rand1 < 50))
		r = 1;
	if ((rand1 >= 50) && (rand1 < 75))
		r = 2;
	if (rand1 >= 75)
		r = 3;

	if (r > maxRing)
		r = maxRing;
	if (r < minRing)
		r = minRing;

	currRing = r;
	rand1 = rand() % 100;

	if (rand1 < 33)
	{
		car.setPosition(R[r].E.x, R[r].E.y);
		moveDir = 'r';
	}
	if ((rand1 >= 33) && (rand1 < 66))
	{
		car.setPosition(R[r].F.x, R[r].F.y);
		moveDir = 'u';
	}
	if (rand1 >= 66)
	{
		car.setPosition(R[r].H.x, R[r].H.y);
		moveDir = 'd';
	}

	
	car.setScale(0.06, 0.06);
}

void Enemy::move(int playerRing) {
	/*this function moves an enemy between rings. It check
	if the car is first close to points EFGH. Then it will
	check the ring the player is going and appropriatly
	moves the enemy b/w rings*/
	string s = "";
	if (playerRing>currRing) {
		s = "l";
	}
	else if (playerRing < currRing) {
		s = "r";
	}

	int deviation = 5;

	if (closeToCar(R[currRing].E.x, R[currRing].E.y) //Check if the the car is close to a move point
		|| closeToCar(R[currRing].F.x, R[currRing].F.y)
		|| closeToCar(R[currRing].G.x, R[currRing].G.y)
		|| closeToCar(R[currRing].H.x, R[currRing].H.y)
		) {
		if (s == "l")
		{
			if (currRing < maxRing) {//Move to inner ring
				currRing++;
				if (moveDir == 'r') {
					car.setPosition(R[currRing].E.x + deviation, R[currRing].E.y);
				}
				if (moveDir == 'l') {
					car.setPosition(R[currRing].G.x - deviation, R[currRing].G.y);
				}
				if (moveDir == 'd') {
					car.setPosition(R[currRing].H.x, R[currRing].H.y + deviation);
				}
				if (moveDir == 'u') {
					car.setPosition(R[currRing].F.x, R[currRing].F.y - deviation);
				}
			}
		}
		else if (s == "r") {//move to outer ring
			if (currRing > minRing) {
				currRing--;
				if (moveDir == 'r') {
					car.setPosition(R[currRing].E.x + deviation, R[currRing].E.y);
				}
				if (moveDir == 'l') {
					car.setPosition(R[currRing].G.x - deviation, R[currRing].G.y);
				}
				if (moveDir == 'd') {
					car.setPosition(R[currRing].H.x, R[currRing].H.y + deviation);
				}
				if (moveDir == 'u') {
					car.setPosition(R[currRing].F.x, R[currRing].F.y - deviation);
				}
			}
		}
	}


}


void Enemy::moveFwd(int playerRing) { //This function is the default auto movement of the player counter clockwise
	if ((car.getPosition().x == R[currRing].A.x) && (car.getPosition().y == R[currRing].A.y))//corner A 
	{
		moveDir = 'r';//set movement to right
	}
	if ((car.getPosition().x == R[currRing].B.x) && (car.getPosition().y == R[currRing].B.y))//corner B
	{
		moveDir = 'u';//set movement to up
	}
	if ((car.getPosition().x == R[currRing].C.x) && (car.getPosition().y == R[currRing].C.y))//corner C
	{
		moveDir = 'l';//set movement to left
	}
	if ((car.getPosition().x == R[currRing].D.x) && (car.getPosition().y == R[currRing].D.y))//corner D
	{
		moveDir = 'd';//set movement to down
	}

	if (moveDir == 'u') {
		if (car.getPosition().y - 1 * speed < R[currRing].A.y) { //Check if the movement will make it go out of bounds or not
			car.setPosition(R[currRing].A.x, R[currRing].A.y);
		}
		else {
			car.move(0, -1 * speed);
		}
	}
	if (moveDir == 'd') {
		if (car.getPosition().y + 1 * speed > R[currRing].C.y) { //Check if the movement will make it go out of bounds or not
			car.setPosition(R[currRing].C.x, R[currRing].C.y);
		}
		else {
			car.move(0, 1 * speed);
		}
	}
	if (moveDir == 'l') {
		if (car.getPosition().x - 1 * speed < R[currRing].B.x) { //Check if the movement will make it go out of bounds or not
			car.setPosition(R[currRing].B.x, R[currRing].B.y);
		}
		else {
			car.move(-1 * speed, 0);
		}
	}
	if (moveDir == 'r') {
		if (car.getPosition().x + 1 * speed > R[currRing].D.x) { //Check if the movement will make it go out of bounds or not
			car.setPosition(R[currRing].D.x, R[currRing].D.y);
		}
		else {
			car.move(1 * speed, 0);
		}
	}
	move(playerRing);
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

bool Enemy::closeToCar(int x, int y) {
	int b = 1;//bound length

	if ((((car.getPosition().y) > (y + b)) || ((car.getPosition().y) < (y - b))))
	{
		return false;
	}

	if ((((car.getPosition().x) > (x + b)) || ((car.getPosition().x) < (x - b))))
	{
		return false;
	}

	return true;
}