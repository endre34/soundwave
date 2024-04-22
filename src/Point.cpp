/*
 *  Project: SzalontaGrafika2024
 *   Author: Endre
 */

#include <iomanip>
#include <cmath>

#include "Point.hpp"
#include "utils.hpp"

using namespace std;


Point::Point(double x, double y)
{
	this->x = static_cast<int>(x * 1000.0);
	this->y = static_cast<int>(y * 1000.0);
}

Point::Point(int x, int y) :
		x { x },
		y { y }
{
	// empty
}

Point::Point(const Point& point) :
		x { point.x },
		y { point.y }
{
	// empty
}

Point::Point() :
		x { 0 },
		y { 0 }
{
	// empty
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

int Point::getX() const
{
	return x;
}

int Point::getY() const
{
	return y;
}

double Point::getXMeters() const
{
	return static_cast<double>(x) / 1000.0;
}

double Point::getYMeters() const
{
	return static_cast<double>(y) / 1000.0;
}

bool Point::isValid() const
{
	return x >= 0 && y >= 0;
}

ostream& operator <<(ostream& out, const Point& point)
{
	out << fixed << setprecision(3) << setfill(' ');
	out << "(" << setw(6) << point.getXMeters() << ", " << setw(6) << point.getYMeters() << ")";
	return out;
}

double Point::calcGradient(const Point& p1, const Point& p2)
{
	double gr = (double)(p2.y - p1.y) / (p2.x - p1.x);
	return round_to_precision(gr, 2);
}

int Point::calcDistance(const Point& p1, const Point& p2)
{
	return sqrt(pow(p2.x - p1.x, 2) + pow(p2.y - p1.y, 2));
}


ReflectionPoint::ReflectionPoint(double x, double y, Wall wall) :
		Point(x, y)
{
	this->wall = wall;
}

ReflectionPoint::ReflectionPoint(int x, int y, Wall wall) :
		Point(x, y)
{
	this->wall = wall;
}

ReflectionPoint::ReflectionPoint()
{
	wall = Top;
}

Wall ReflectionPoint::getWall() const
{
	return wall;
}














