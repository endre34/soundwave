/*
 *  Project: SzalontaGrafika2024
 *   Author: Endre
 */

#include <iostream>
#include <iomanip>
#include <cmath>

#include "Room.hpp"

double myRound(double value, int decimal_places)
{
    const double multiplier = std::pow(10.0, decimal_places);
    return std::round(value * multiplier) / multiplier;
}

Point::Point(const int x, const int y)
{
	this->x = x;
	this->y = y;
}

void Point::to_mm()
{
	x = x * 1000;
	y = y * 1000;
}

void Point::out()
{
	std::cout << '(' << (double)x / 1000.0 << ", " << (double)y / 1000.0 << ')' << std::setprecision(5) <<  std::endl;
}

Room::ReflectionP::ReflectionP(const Point point, const Wall wall)
{
	this->point = point;
	this->wall = wall;
}

Room::Room(const int sizeX, const int sizeY)
{
	this->sizeX = sizeX;
	this->sizeY = sizeY;
//	point1 = {farthest.x / 3, farthest.y / 2};
//	point2 = {farthest.x * 2 / 3, farthest.y / 2};
}

double Room::calcDir(const Point p1, const Point p2)
{
	return ((double)p2.y - (double)p1.y) / ((double)p2.x - (double)p1.x);
}

Point Room::getInitalRP(const Wall wall)
{
	switch (wall)
	{
	case Top:												// y = 0 && x variable
		return Point((source.x + target.x) / 2, 0);
	case Bottom:											// y = sizeY && x variable
		return Point((source.x + target.x) / 2, sizeY * 1000);
	case Left:												// y variable && x = 0
		return Point(0, (source.y + target.y) / 2);
	case Right:												// y variable && x = sizeX
		return Point(sizeX * 1000, (source.y + target.y) / 2);
	default:
		throw std::overflow_error("ERROR: no such value in enum");
		return Point(-1, -1);
	}
}

Point Room::getNextRP(const Direction direction, const Wall wall,
		const int increment, const Point reflectionP)
{
	if (wall == Right || wall == Left)
	{
		int y = direction == To_Source ?
				reflectionP.y + (source.y - target.y) / abs(source.y - target.y) * increment :
				reflectionP.y + (target.y - source.y) / abs(target.y - source.y) * increment ;

		return Point(reflectionP.x, y);
	}
	else
	{
		int x = direction == To_Source ?
				reflectionP.x + (source.x - target.x) / abs(source.x - target.x) * increment :
				reflectionP.x + (target.x - source.x) / abs(target.x - source.x) * increment ;

		return Point(x, reflectionP.y);
	}
}

void Room::setSource(const Point& source)					// in meters
{
	this->source = source;
	this->source.to_mm();
}

void Room::setTarget(const Point target)					// in meters
{
	this->target = target;
	this->target.to_mm();
}

void Room::setParams(const int freq)
{
	period = 1.0 / (double)freq;
	waveleght = round(340000.0 * period);

	std::cout << "Periodus: " << period << " s" << std::endl;
	std::cout << "Hullamhossz: " << waveleght << " mm" << std::endl;
}

void Room::setSize(const int sizeX, const int sizeY)
{
	this->sizeX = sizeX;
	this->sizeY = sizeY;
}

Point Room::calcReflectionP(const Wall wall)
{

	Point reflectionP = getInitalRP(wall);

	int increment = wall == Right || wall == Left ? 		// set effective increment
			abs(source.y - target.y) / 3 :
			abs(source.x - target.x) / 3 ;

	bool with_mR = false;

	double dir_fromSource;
	double dir_fromTarget;
	if (with_mR)
	{
		dir_fromSource = myRound(calcDir(source, reflectionP), 3);
		dir_fromTarget = myRound(calcDir(target, reflectionP), 3);
	}
	else
	{
		dir_fromSource = calcDir(source, reflectionP);
		dir_fromTarget = calcDir(target, reflectionP);
	}

//	std::cout << "RP: ";
//	reflectionP.out();
//	std::cout << "Pitch: " << dir_fromSource << ' ' << dir_fromTarget << std::setprecision(5) << std::endl;
//
//	std::cout << dir_fromSource << std::endl;

	Direction originalDirection = abs(dir_fromSource) < abs(dir_fromTarget) ? To_Source : To_Target;
	bool GO = true;
	while (abs(dir_fromSource) != abs(dir_fromTarget) && GO)
	{
		Direction direction = abs(dir_fromSource) < abs(dir_fromTarget) ? To_Source : To_Target;

		if (originalDirection != direction)
		{
			originalDirection = direction;
			increment = increment / 2;
			if (increment == 0)
				break;
		}

		reflectionP = getNextRP(direction, wall, increment, reflectionP);

		if (with_mR)
		{
			dir_fromSource = myRound(calcDir(source, reflectionP), 3);
			dir_fromTarget = myRound(calcDir(target, reflectionP), 3);
		}
		else
		{
			dir_fromSource = calcDir(source, reflectionP);
			dir_fromTarget = calcDir(target, reflectionP);
		}

//		std::cout << "RP: ";
//		reflectionP.out();
//		std::cout << "Pitch: " << dir_fromSource << ' ' << dir_fromTarget << std::setprecision(5) << std::endl;
//		std::cout << "Increment: " << increment << std::endl;
	}

	if (dir_fromSource == dir_fromTarget)
		return Point(-1, -1);									// Collision with target in reflection path
																// No reflection point
	return reflectionP;
}

void Room::calcReflectionPoints()
{
	for (int i = Top; i <= Right; ++i)
	{
		Point reflectionP = calcReflectionP(static_cast<Wall>(i));
		if (reflectionP.x != -1)
		{
			reflectionPoints.emplace_back(ReflectionP(reflectionP, static_cast<Wall>(i)));
		}
	}
}

void Room::calcDistances()
{
	if ((int)reflectionPoints.size() != 0)
	{
		for (int i = 0; i < (int)reflectionPoints.size(); ++i)
		{
			distances.emplace_back(sqrt(pow(reflectionPoints[i].point.x - source.x, 2) + pow(reflectionPoints[i].point.y - source.y, 2))
					+ sqrt((pow(target.x - reflectionPoints[i].point.x, 2) + pow(target.y - reflectionPoints[i].point.y, 2))));

			std::cout << "Distance of [" << i << "]: " << distances[i] << " mm" << std::endl;
		}

		distances.emplace_back(sqrt((pow(target.x - source.x, 2) + pow(target.y - source.y, 2))));

		std::cout << "Distance of [direct]: " << distances.back() << " mm" << std::endl;
	}
	else
	{
		throw std::overflow_error("No reflection points");
	}
}







