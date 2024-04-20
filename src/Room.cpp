/*
 *  Project: SzalontaGrafika2024
 *   Author: Endre
 */

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

ReflectionPoint Room::getInitalReflectionPoint(Wall wall)
{
	switch (wall)
	{
	case Top:												// y = 0 && x variable
		return ReflectionPoint((source.getXMillis() + target.getXMillis()) / 2, 0, wall);
	case Bottom:											// y = sizeY && x variable
		return ReflectionPoint((source.getXMillis() + target.getXMillis()) / 2, sizeY, wall);
	case Left:												// y variable && x = 0
		return ReflectionPoint(0, (source.getYMillis() + target.getYMillis()) / 2, wall);
	case Right:												// y variable && x = sizeX
		return ReflectionPoint(sizeX, (source.getYMillis() + target.getYMillis()) / 2, wall);
	default:
		throw overflow_error("ERROR: no such value in enum");
		return ReflectionPoint(-1, -1, wall);
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

void Room::setSource(const Point& source)
{
	this->source = source;
}

Point Room::getSource()
{
	return source;
}

void Room::setTarget(const Point& target)
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

int Room::calcDistance(const Point& point1, const Point& point2)
{
	return static_cast<int>(sqrt(pow(point2.getXMillis() - point1.getXMillis(), 2) + pow(point2.getYMillis() - point1.getYMillis(), 2)));
}

ReflectionPoint Room::calcReflectionPoint(Wall wall)
{
	ReflectionPoint reflPt = getInitalReflectionPoint(wall);

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
			distances.push_back(calcDistance(reflectionPoints[i], source) + calcDistance(target, reflectionPoints[i]));

			cout << "Distance of [" << i << "]: " << distances[i] << " mm" << endl;
		}

		distances.push_back(calcDistance(source, target));

		cout << "Distance of [direct]: " << distances.back() << " mm" << endl;
	}
	else
	{
		throw overflow_error("No reflection points");
	}
}







