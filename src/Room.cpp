/*
 *  Project: SzalontaGrafika2024
 *   Author: Endre
 */

#include <cmath>
#include <iomanip>

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

string Room::to_string(Direction dir)
{
	switch (dir)
	{
	case TOWARD_SOURCE:
		return "TOWARD_SOURCE";
	case TOWARD_TARGET:
		return "TOWARD_TARGET";
	default:
		throw runtime_error("Unrecognized direction");
	}


}

Room::Direction Room::calcDirection(Wall wall, double sourceGradient, double targetGradient)
{
	return (wall == Right || wall == Left) ?
			abs(sourceGradient) > abs(targetGradient) ? TOWARD_SOURCE : TOWARD_TARGET :
			abs(sourceGradient) < abs(targetGradient) ? TOWARD_SOURCE : TOWARD_TARGET ;
}

ReflectionPoint Room::calcInitalReflectionPoint(Wall wall)
{
	switch (wall)
	{
	case Top:
		return ReflectionPoint((source.getXMillis() + target.getXMillis()) / 2, 0, wall);
	case Bottom:
		return ReflectionPoint((source.getXMillis() + target.getXMillis()) / 2, sizeY, wall);
	case Left:
		return ReflectionPoint(0, (source.getYMillis() + target.getYMillis()) / 2, wall);
	case Right:
		return ReflectionPoint(sizeX, (source.getYMillis() + target.getYMillis()) / 2, wall);
	default:
		throw runtime_error("Unrecognized wall");
	}
}

ReflectionPoint Room::calcNextReflectionPoint(Direction direction, int increment, const ReflectionPoint& reflectionP)
{
	if (reflectionP.getWall() == Right || reflectionP.getWall() == Left)
	{
		int y = direction == TOWARD_SOURCE ?
				reflectionP.getYMillis() + (source.getYMillis() - target.getYMillis()) / abs(source.getYMillis() - target.getYMillis()) * increment :
				reflectionP.getYMillis() + (target.getYMillis() - source.getYMillis()) / abs(target.getYMillis() - source.getYMillis()) * increment ;

		return ReflectionPoint(reflectionP.getXMillis(), y, reflectionP.getWall());
	}
	else
	{
		int x = direction == TOWARD_SOURCE ?
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

ReflectionPoint Room::calcReflectionPoint(Wall wall)
{
	ReflectionPoint reflPt = calcInitalReflectionPoint(wall);

	double sourceGradient = Point::calcGradient(source, reflPt);
	double targetGradient = Point::calcGradient(target, reflPt);

	Direction prevDir = calcDirection(wall, sourceGradient, targetGradient);

	int increment = (wall == Right || wall == Left) ?
			abs(source.getYMillis() - target.getYMillis()) / 5 :
			abs(source.getXMillis() - target.getXMillis()) / 5 ;

	while (abs(sourceGradient) != abs(targetGradient))
	{
		reflPt = calcNextReflectionPoint(prevDir, increment, reflPt);

		sourceGradient = Point::calcGradient(source, reflPt);
		targetGradient = Point::calcGradient(target, reflPt);

		Direction currDir = calcDirection(wall, sourceGradient, targetGradient);

		if (prevDir != currDir)
		{
			prevDir = currDir;
			increment = increment / 2;
			if (increment == 0)
			{
				cout << "Increment is 0, exiting" << endl;
				break;
			}
		}
//		cout << "refl pt: " << reflPt
//				<< ", dir: " << to_string(currDir)
//				<< ", incr: " << increment << '\n';
	}

	if (sourceGradient == targetGradient)
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
			cout << "Reflection point: " << rp << endl;
		}
		else
		{
			cout << "Invalid reflection point" << endl;
		}
	}
}

void Room::calcDistances()
{
	distances.clear();

	cout << fixed << setprecision(3) << setfill(' ');
	for (auto reflPt : reflectionPoints)
	{
		distances.push_back(Point::calcDistance(source, reflPt) + Point::calcDistance(reflPt, target));

		cout << "Distance: " << setw(6) << to_meters(distances.back()) << endl;
	}

	distances.push_back(Point::calcDistance(source, target));
	cout << "Distance: " << setw(6) << to_meters(distances.back()) << endl;
}







