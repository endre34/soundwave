/*
 *  Project: SzalontaGrafika2024
 *   Author: Endre
 */

#include "Point.hpp"

Point::Point(double x, double y)
{
	this->x = static_cast<int>(x * 1000.0);
	this->y = static_cast<int>(y * 1000.0);
}

Point::Point(int x, int y)
{
	this->x = x;
	this->y = y;
}

Point::Point()
{
	x = 0;
	y = 0;
}

void Point::setCoords(double x, double y)
{
	setX(x);
	setY(y);
}

void Point::setX(double x)
{
	this->x = static_cast<int>(x * 1000.0);
}

void Point::setY(double y)
{
	this->y = static_cast<int>(y * 1000.0);
}

void Point::setCoords(int x, int y)
{
	setX(x);
	setY(y);
}

void Point::setX(int x)
{
	this->x = x;
}

void Point::setY(int y)
{
	this->y = y;
}

int Point::intGetX()
{
	return x;
}

int Point::intGetY()
{
	return y;
}

double Point::doubleGetX()
{
	return static_cast<double>(x) / 1000.0;
}

double Point::doubleGetY()
{
	return static_cast<double>(y) / 1000.0;
}

std::ostream& operator <<(std::ostream& out, const Point& point)
{
	out << "(" << static_cast<double>(point.x) / 1000.0 << ", " << static_cast<double>(point.y) / 1000.0 << ")";
	return out;
}

ReflectionPoint::ReflectionPoint(double x, double y, Wall wall)
: Point(x, y)
{
	this->wall = wall;
}

ReflectionPoint::ReflectionPoint(int x, int y, Wall wall)
: Point(x, y)
{
	this->wall = wall;
}

ReflectionPoint::ReflectionPoint()
{
	wall = Top;
}

Wall ReflectionPoint::getWall()
{
	return wall;
}














