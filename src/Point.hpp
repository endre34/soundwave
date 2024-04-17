/*
 *  Project: SzalontaGrafika2024
 *   Author: Endre
 */

#ifndef POINT_HPP_
#define POINT_HPP_

#include <iostream>

enum Wall
{
	Top,
	Bottom,
	Left,
	Right
};

class Point
{
public:
	Point(double x, double y);
	Point(int x, int y);
	Point();

	void setCoords(double x, double y);
	void setX(double x);
	void setY(double y);

	void setCoords(int x, int y);
	void setX(int x);
	void setY(int y);

	int intGetX();
	int intGetY();

	double doubleGetX();
	double doubleGetY();

	friend std::ostream& operator <<(std::ostream& out, const Point& point);

private:
	int x, y;
};

class ReflectionPoint : public Point
{
public:
	ReflectionPoint(double x, double y, Wall wall);
	ReflectionPoint(int x, int y, Wall wall);
	ReflectionPoint();

	Wall getWall();

private:
	Wall wall;
};

#endif /* POINT_HPP_ */
