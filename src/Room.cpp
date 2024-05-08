/*
 *  Project: SzalontaGrafika2024
 *   Author: Endre
 */

#include <cmath>
#include <iomanip>

#include "Room.hpp"
#include "utils.hpp"

using namespace std;


Room::Room(double sizeX, double sizeY) : // @suppress("Class members should be properly initialized")
		frequency { 0 },
		waveleght { 0 },
		period { 0 },
		kiteres { 0 }
{
	this->sizeX = to_millis(sizeX);
	this->sizeY = to_millis(sizeY);
}

Room::Room(const Room& room) : // @suppress("Class members should be properly initialized")
		sizeX { room.sizeX },
		sizeY { room.sizeY },
		frequency { room.frequency },
		waveleght { room.waveleght },
		period { room.period },
		kiteres { room.kiteres }
{
	// empty
}

Room::Room() : // @suppress("Class members should be properly initialized")
		sizeX { 0 },
		sizeY { 0 },
		frequency { 0 },
		waveleght { 0 },
		period { 0 },
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

double Room::getAngle(const Point& point1, const Point& point2)
{
	double gradient = Point::calcGradientPrecise(point1, point2);
	double angle = atan(gradient) * 180.0 / M_PI;

	if (point2.getX() - point1.getX() < 0)
	{
		angle += 180.0;
	}

	return angle;
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
	waveleght = propagationSpeed * period;

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

	while (abs(sourceGradient) != abs(targetGradient) && increment != 0)
	{
		reflPt = calcNextReflectionPoint(prevDir, increment, reflPt);

		sourceGradient = Point::calcGradient(source, reflPt);
		targetGradient = Point::calcGradient(target, reflPt);

		Direction currDir = calcDirection(wall, sourceGradient, targetGradient);

		if (prevDir != currDir)
		{
			prevDir = currDir;
			increment = increment / 2;
		}
//		cout << "refl pt: " << reflPt
//				<< ", next: " << to_string(currDir)
//				<< ", incr: " << increment << '\n';
	}

	//cout << sourceGradient << " " << targetGradient << endl;

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
	//cout << endl;
}

void Room::calcDistances()
{
	distances.clear();

	cout << fixed << setprecision(3) << setfill(' ');

	distances.push_back(Point::calcDistance(source, target));
//	cout << "Distance: " << setw(6) << to_meters(distances.back()) << endl;

	for (ReflectionPoint reflPt : reflectionPoints)
	{
		distances.push_back(Point::calcDistance(source, reflPt) + Point::calcDistance(reflPt, target));

//		cout << "Distance: " << setw(6) << to_meters(distances.back()) << endl;
	}
}

void Room::calcDisplacement()
{
	cout << fixed << setprecision(10);

	double intensity = pow(10, -12 + soundPressureLevel / 10) / pow(to_meters(distances.front()), 2);
	double time = to_meters(distances.front()) / propagationSpeed;
	double amplitude = sqrt(intensity / (2 * pow(M_PI, 2) * airDensity * propagationSpeed * pow(frequency, 2)));

	displacements.push_back(amplitude * sin(2 * M_PI * (time / period - distances.front() / waveleght)));

//	cout << "amplitud: " << amplitude
//			<< " ido: " << time
//			<< " intensitas: " << intensity
//			<< endl;
//	cout << kiteresek.back() << endl;

	for (int i = 1; i < (int)distances.size(); ++i)
	{
		double intensity = pow(10, -12 + soundPressureLevel / 10) / pow(to_meters(distances[i]), 2);
		double time = to_meters(distances[i]) / propagationSpeed;
		double amplitude = sqrt(intensity / (2 * pow(M_PI, 2) * airDensity * propagationSpeed * pow(frequency, 2)));

		displacements.push_back(amplitude * sin(2 * M_PI * (time / period - (distances[i] + waveleght / 2) / waveleght)));

//		cout << "amplitud: " << amplitude
//				<< " ido: " << time
//				<< " intensitas: " << intensity
//				<< endl;
//		cout << kiteresek.back() << endl;
	}
}

void Room::splAtTarget()
{
	double displX { 0 };
	double displY { 0 };

	displX += displacements.front() * cos(getAngle(source, target) * M_PI / 180.0);
	displY += displacements.front() * sin(getAngle(source, target) * M_PI / 180.0);

	for (size_t i = 0; i < reflectionPoints.size(); i++)
	{
		double angleRad = getAngle(reflectionPoints[i], target) * M_PI / 180.0;
		double displ = displacements[i + 1];

		displX += displ * cos(angleRad);
		displY += displ * sin(angleRad);
	}

	double mainDispl = sqrt(pow(displX, 2) + pow(displY, 2));

	cout << "amplitude: " << mainDispl;

	double intensity = 2 * pow(M_PI, 2) * airDensity * pow(mainDispl, 2) * pow(frequency, 2) * propagationSpeed;

	cout << ", intensity: " << intensity;

	double SPL = 10 * log10(intensity / pow(10, -12));

	cout << ", SPL: " << SPL << endl;


}







