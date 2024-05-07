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
		frequency { 0 },
		period { 0 },
		maxAmplitude { 0 },
		kiteres { 0 }
{
	this->sizeX = to_millis(sizeX);
	this->sizeY = to_millis(sizeY);
}

Room::Room(const Room& room) :
		sizeX { room.sizeX },
		sizeY { room.sizeY },
		waveleght { room.waveleght },
		frequency { room.frequency },
		period { room.period },
		maxAmplitude { room.maxAmplitude },
		kiteres { room.kiteres }
{
	// empty
}

Room::Room() :
		sizeX { 0 },
		sizeY { 0 },
		waveleght { 0 },
		frequency { 0 },
		period { 0 },
		maxAmplitude { 0 },
		kiteres { 0 }
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
			(abs(sourceGradient) > abs(targetGradient) ? TOWARD_SOURCE : TOWARD_TARGET) :
			(abs(sourceGradient) < abs(targetGradient) ? TOWARD_SOURCE : TOWARD_TARGET) ;
}

ReflectionPoint Room::calcInitalReflectionPoint(Wall wall)
{
	switch (wall)
	{
	case Top:
		return ReflectionPoint((source.getX() + target.getX()) / 2, 0, wall);
	case Bottom:
		return ReflectionPoint((source.getX() + target.getX()) / 2, sizeY, wall);
	case Left:
		return ReflectionPoint(0, (source.getY() + target.getY()) / 2, wall);
	case Right:
		return ReflectionPoint(sizeX, (source.getY() + target.getY()) / 2, wall);
	default:
		throw runtime_error("Unrecognized wall");
	}
}

ReflectionPoint Room::calcNextReflectionPoint(Direction direction, int increment, const ReflectionPoint& reflectionP)
{
	if (reflectionP.getWall() == Right || reflectionP.getWall() == Left)
	{
		int y = direction == TOWARD_SOURCE ?
				reflectionP.getY() + (source.getY() - target.getY()) / abs(source.getY() - target.getY()) * increment :
				reflectionP.getY() + (target.getY() - source.getY()) / abs(target.getY() - source.getY()) * increment ;

		return ReflectionPoint(reflectionP.getX(), y, reflectionP.getWall());
	}
	else
	{
		int x = direction == TOWARD_SOURCE ?
				reflectionP.getX() + (source.getX() - target.getX()) / abs(source.getX() - target.getX()) * increment :
				reflectionP.getX() + (target.getX() - source.getX()) / abs(target.getX() - source.getX()) * increment ;

		return ReflectionPoint(x, reflectionP.getY(), reflectionP.getWall());
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

Point Room::getTarget()
{
	return target;
}

void Room::setTarget(const Point& target)
{
	this->target = target;
}

void Room::setParams(int freq)
{
	frequency = freq;
	period = 1.0 / (double)freq;
	waveleght = round(343500.0 * period);
	maxAmplitude = sqrt(pow(10, -12 + SPL / 10 + 6) / (2 * pow(M_PI, 2) * 1.2045 * 343.5 * pow(freq, 2)));

//	cout << fixed << setprecision(5);
//	cout << "maxampl: " << maxAmplitude << " mm" << endl;
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

	// Muszaly 4 legyen maskent atszokik a target-en
	int increment = (wall == Right || wall == Left) ?
			abs(source.getY() - target.getY()) / 4 :
			abs(source.getX() - target.getX()) / 4 ;

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
//				cout << "Increment is 0, exiting" << endl;
				break;
			}
		}
//		cout << "refl pt: " << reflPt
//				<< ", next: " << to_string(currDir)
//				<< ", incr: " << increment << '\n';
	}

	cout << sourceGradient << " " << targetGradient << endl;

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
//			cout << "Reflection point: " << rp << endl;
		}
		else
		{
//			cout << "Invalid reflection point" << endl;
		}
	}
	cout << endl;
}

void Room::calcDistances()
{
	distances.clear();

	cout << fixed << setprecision(3) << setfill(' ');

	distances.push_back(Point::calcDistance(source, target));
//	cout << "Distance: " << setw(6) << to_meters(distances.back()) << endl;

	for (auto reflPt : reflectionPoints)
	{
		distances.push_back(Point::calcDistance(source, reflPt) + Point::calcDistance(reflPt, target));

//		cout << "Distance: " << setw(6) << to_meters(distances.back()) << endl;
	}
}

void Room::calcKiteresek()
{
	cout << fixed << setprecision(10);
	{
		double intensity = pow(10, -12 + (double)SPL / 10) / pow(to_meters(distances.front()), 2);
		double time = distances.front() / 343.5;
		double amplitude = sqrt(intensity / (2 * pow(M_PI, 2) * 1.2045 * 343.5 * pow(frequency, 2)));
		kiteresek.push_back(amplitude * sin(2 * M_PI * (time / period - distances.front() / waveleght)));
		cout << kiteresek.back() << endl;
	}

	for (int i = 1; i < (int)distances.size(); ++i)
	{
		double intensity = pow(10, -12 + (double)SPL / 10) / pow(to_meters(distances[i]), 2);
		double time = distances[i] / 343.5;
		double amplitude = sqrt(intensity * pow(10, 6) / (2 * pow(M_PI, 2) * 1.2045 * 343.5 * pow(frequency, 2)));
		kiteresek.push_back(amplitude * sin(2 * M_PI * (time / period - (distances[i] + waveleght / 2) / waveleght)));
		cout << kiteresek.back() << endl;
	}
}







