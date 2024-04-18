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

int to_milis(double meters)
{
	return static_cast<int>(meters * 1000.0);
}

Room::Room(double sizeX, double sizeY)
{
	this->sizeX = static_cast<int>(sizeX * 1000.0);
	this->sizeY = sizeY;

	waveleght = 0;
	period = 0;
}

Room::Room()
{
	sizeX = 0;
	sizeY = 0;

	waveleght = 0;
	period = 0;
}

double Room::calcDir(Point p1, Point p2)
{
	return (p2.doubleGetY() - p1.doubleGetY()) / (p2.doubleGetX() - p1.doubleGetX());
}

Point Room::getInitalRP(const Wall wall)
{
	switch (wall)
	{
	case Top:												// y = 0 && x variable
		return Point((source.intGetX() + target.intGetX()) / 2, 0);
	case Bottom:											// y = sizeY && x variable
		return Point((source.intGetX() + target.intGetX()) / 2, sizeY * 1000);
	case Left:												// y variable && x = 0
		return Point(0, (source.intGetY() + target.intGetY()) / 2);
	case Right:												// y variable && x = sizeX
		return Point(sizeX * 1000, (source.intGetY() + target.intGetY()) / 2);
	default:
		throw std::overflow_error("ERROR: no such value in enum");
		return Point(-1, -1);
	}
}

ReflectionPoint Room::getNextRP(const Direction direction,
		const int increment, ReflectionPoint reflectionP)
{
	if (reflectionP.getWall() == Right || reflectionP.getWall() == Left)
	{
		int y = direction == To_Source ?
				reflectionP.intGetY() + (source.intGetY() - target.intGetY()) / abs(source.intGetY() - target.intGetY()) * increment :
				reflectionP.intGetY() + (target.intGetY() - source.intGetY()) / abs(target.intGetY() - source.intGetY()) * increment ;

		return ReflectionPoint(reflectionP.intGetX(), y, reflectionP.getWall());
	}
	else
	{
		int x = direction == To_Source ?
				reflectionP.intGetX() + (source.intGetX() - target.intGetX()) / abs(source.intGetX() - target.intGetX()) * increment :
				reflectionP.intGetX() + (target.intGetX() - source.intGetX()) / abs(target.intGetX() - source.intGetX()) * increment ;

		return ReflectionPoint(x, reflectionP.intGetY(), reflectionP.getWall());
	}
}

void Room::setSource(const Point& source)					// in meters
{
	this->source = source;
}

void Room::setTarget(const Point target)					// in meters
{
	this->target = target;
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
	ReflectionPoint reflectionP;

	{
		Point point = getInitalRP(wall);
		reflectionP = ReflectionPoint(point.intGetX(), point.intGetY(), wall);
	}

	int increment = wall == Right || wall == Left ? 		// set effective increment
			abs(source.intGetY() - target.intGetY()) / 3 :
			abs(source.intGetX() - target.intGetX()) / 3 ;

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
	while (abs(dir_fromSource) != abs(dir_fromTarget))
	{
		Direction direction = abs(dir_fromSource) < abs(dir_fromTarget) ? To_Source : To_Target;

		if (originalDirection != direction)
		{
			originalDirection = direction;
			increment = increment / 2;
			if (increment == 0)
				break;
		}

		reflectionP = getNextRP(direction, increment, reflectionP);

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
		if (reflectionP.intGetX() != -1)
		{
			reflectionPoints.emplace_back(ReflectionPoint(reflectionP.intGetX(), reflectionP.intGetY(), static_cast<Wall>(i)));
		}
	}
}

void Room::calcDistances()
{
	if ((int)reflectionPoints.size() != 0)
	{
		for (int i = 0; i < (int)reflectionPoints.size(); ++i)
		{
			distances.emplace_back(sqrt(pow(reflectionPoints[i].intGetX() - source.intGetX(), 2) + pow(reflectionPoints[i].intGetY() - source.intGetY(), 2))
					+ sqrt((pow(target.intGetX() - reflectionPoints[i].intGetX(), 2) + pow(target.intGetY() - reflectionPoints[i].intGetY(), 2))));

			std::cout << "Distance of [" << i << "]: " << distances[i] << " mm" << std::endl;
		}

		distances.emplace_back(sqrt((pow(target.intGetX() - source.intGetX(), 2) + pow(target.intGetY() - source.intGetY(), 2))));

		std::cout << "Distance of [direct]: " << distances.back() << " mm" << std::endl;
	}
	else
	{
		throw std::overflow_error("No reflection points");
	}
}







