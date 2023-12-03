#pragma once
#include<cmath>
#include <iostream>

class Point
{
public:
	Point(int xVal = 0, int yVal = 0);;
	~Point();

	int getX();
	int getY();
	bool setX(int newX);
	bool setY(int newY);
	void move(int dx = 0, int dy = 0);
	double distanceTo(Point otherPoint);
	void print();

private:
	int x, y;
};

Point::Point(int xVal, int yVal){
	x = xVal;
	y = yVal;
}

int Point::getX() {
	return x;
}

int Point::getY(){
	return y;
}

bool Point::setX(int newX) {
	x = newX;
	return true;
}

bool Point::setY(int newY) {
	y = newY;
	return true;
}
void Point::move(int dx, int dy) {
	x += dx;
	y += dy;
}
double Point::distanceTo(Point otherPoint) {
	return sqrt(pow(double(x) - double(otherPoint.x), 2) + pow(double(y) - double(otherPoint.y), 2));
}
void Point::print() {
	std::cout << "(" << x << "," << y << ")";
}
