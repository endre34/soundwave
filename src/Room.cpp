/*
 *  Project: SzalontaGrafika2024
 *   Author: Endre
 */

#include <iostream>
#include <iomanip>
#include <cmath>

#include "Room.hpp"
#include "utils.hpp"

using namespace std;


Room::Room(double sizeX, double sizeY) :
		waveleght { 0 },
		period { 0 }
{
	this->sizeX = to_millis(sizeX);
	this->sizeY = to_millis(sizeY);
}

Room::Room(const Room& room) :
		sizeX { room.sizeX },
		sizeY { room.sizeY },
		waveleght { room.waveleght },
		period { room.period }
{
	// empty
}

Room::Room() :
		sizeX { 0 },
		sizeY { 0 },
		waveleght { 0 },
		period { 0 }
{
	// empty
}

double Room::calcDir(const Point& p1, const Point& p2)
{
	return (p2.getYMeters() - p1.getYMeters()) / (p2.getXMeters() - p1.getXMeters());
}

Point Room::getInitalReflectionPoint(Wall wall)
{
	switch (wall)
	{
	case Top:												// y = 0 && x variable
		return Point((source.getXMillis() + target.getXMillis()) / 2, 0);
	case Bottom:											// y = sizeY && x variable
		return Point((source.getXMillis() + target.getXMillis()) / 2, sizeY * 1000);
	case Left:												// y variable && x = 0
		return Point(0, (source.getYMillis() + target.getYMillis()) / 2);
	case Right:												// y variable && x = sizeX
		return Point(sizeX * 1000, (source.getYMillis() + target.getYMillis()) / 2);
	default:
		throw overflow_error("ERROR: no such value in enum");
		return Point(-1, -1);
	}
}

ReflectionPoint Room::getNextReflectionPoint(Direction direction, int increment, const ReflectionPoint& reflectionP)
{
	if (reflectionP.getWall() == Right || reflectionP.getWall() == Left)
	{
		int y = direction == To_Source ?
				reflectionP.getYMillis() + (source.getYMillis() - target.getYMillis()) / abs(source.getYMillis() - target.getYMillis()) * increment :
				reflectionP.getYMillis() + (target.getYMillis() - source.getYMillis()) / abs(target.getYMillis() - source.getYMillis()) * increment ;

		return ReflectionPoint(reflectionP.getXMillis(), y, reflectionP.getWall());
	}
	else
	{
		int x = direction == To_Source ?
				reflectionP.getXMillis() + (source.getXMillis() - target.getXMillis()) / abs(source.getXMillis() - target.getXMillis()) * increment :
				reflectionP.getXMillis() + (target.getXMillis() - source.getXMillis()) / abs(target.getXMillis() - source.getXMillis()) * increment ;

		return ReflectionPoint(x, reflectionP.getYMillis(), reflectionP.getWall());
	}
}

void Room::setSource(const Point& source)					// in meters
{
	this->source = source;
}

Point Room::getSource()
{
	return source;
}

void Room::setTarget(const Point& target)					// in meters
{
	this->target = target;
}

void Room::setParams(int freq)
{
	period = 1.0 / (double)freq;
	waveleght = round(340000.0 * period);

	cout << "Periodus: " << period * 1000 << " ms" << endl;
	cout << "Hullamhossz: " << waveleght << " mm" << endl;
}

void Room::setSize(double sizeX, double sizeY)
{
	this->sizeX = to_millis(sizeX);
	this->sizeY = to_millis(sizeY);
}

ReflectionPoint Room::calcReflectionPoint(Wall wall)
{
	ReflectionPoint reflPt;

	{
		Point point = getInitalReflectionPoint(wall);
		reflPt = ReflectionPoint(point.getXMillis(), point.getYMillis(), wall);
	}

	int increment = wall == Right || wall == Left ? 		// set effective increment
			abs(source.getYMillis() - target.getYMillis()) / 3 :
			abs(source.getXMillis() - target.getXMillis()) / 3 ;

	bool with_mR = false;

	double dir_fromSource;
	double dir_fromTarget;
	if (with_mR)
	{
		dir_fromSource = round_to_precision(calcDir(source, reflPt), 3);
		dir_fromTarget = round_to_precision(calcDir(target, reflPt), 3);
	}
	else
	{
		dir_fromSource = calcDir(source, reflPt);
		dir_fromTarget = calcDir(target, reflPt);
	}

//	cout << "RP: ";
//	reflectionP.out();
//	cout << "Pitch: " << dir_fromSource << ' ' << dir_fromTarget << setprecision(5) << endl;
//
//	cout << dir_fromSource << endl;

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

		reflPt = getNextReflectionPoint(direction, increment, reflPt);

		if (with_mR)
		{
			dir_fromSource = round_to_precision(calcDir(source, reflPt), 3);
			dir_fromTarget = round_to_precision(calcDir(target, reflPt), 3);
		}
		else
		{
			dir_fromSource = calcDir(source, reflPt);
			dir_fromTarget = calcDir(target, reflPt);
		}

//		cout << "RP: ";
//		reflectionP.out();
//		cout << "Pitch: " << dir_fromSource << ' ' << dir_fromTarget << setprecision(5) << endl;
//		cout << "Increment: " << increment << endl;
	}

	if (dir_fromSource == dir_fromTarget)
		return ReflectionPoint(-1, -1, wall);					// Collision with target in reflection path
																// No reflection point
	return reflPt;
}

void Room::calcReflectionPoints()
{
	reflectionPoints.clear();

	for (int i = Top; i <= Right; ++i)
	{
		ReflectionPoint rp = calcReflectionPoint(static_cast<Wall>(i));
		if (rp.isValid())
		{
			reflectionPoints.push_back(rp);
		}
	}
}

void Room::calcDistances()
{
	distances.clear();

	if ((int)reflectionPoints.size() != 0)
	{
		for (int i = 0; i < (int)reflectionPoints.size(); ++i)
		{
			distances.emplace_back(sqrt(pow(reflectionPoints[i].getXMillis() - source.getXMillis(), 2) + pow(reflectionPoints[i].getYMillis() - source.getYMillis(), 2))
					+ sqrt((pow(target.getXMillis() - reflectionPoints[i].getXMillis(), 2) + pow(target.getYMillis() - reflectionPoints[i].getYMillis(), 2))));

			cout << "Distance of [" << i << "]: " << distances[i] << " mm" << endl;
		}

		distances.emplace_back(sqrt((pow(target.getXMillis() - source.getXMillis(), 2) + pow(target.getYMillis() - source.getYMillis(), 2))));

		cout << "Distance of [direct]: " << distances.back() << " mm" << endl;
	}
	else
	{
		throw overflow_error("No reflection points");
	}
}







