/*
 *  Project: SzalontaGrafika2024
 *   Author: Endre
 */

#ifndef ROOM_HPP_
#define ROOM_HPP_

#include <vector>

#include "Point.hpp"


class Room
{
public:
	Room(double sizeX, double sizeY);
	Room(const Room& room);
	Room();

	void setSource(const Point& source);
	void setTarget(const Point& target);
	void setParams(int freq);
	void setSize(double sizeX, double sizeY);

	Point getSource();
	Point getTarget();

	int getFrequency();
	double getSizeX();
	double getSizeY();

	void calcReflectionPoints();
	void calcDistances();
	void calcDisplacement();
	double getTargetSPL();
	void calcBestPos();

	ReflectionPoint calcReflectionPoint(Wall wall);

	friend class DrawRoom;

	constexpr static double propagationSpeed{ 343.5 };	// m/s
	constexpr static double airDensity{ 1.2045 };		// kg/m^3
	constexpr static int soundPressureLevel{ 70 };		// dB @ 1m from source

private:
	int sizeX, sizeY;
	Point source, target;
	Point optimalPosition;

	std::vector<ReflectionPoint> reflectionPoints;
	std::vector<int> distances;
	std::vector<double> displacements;

	int frequency;
	double waveleght, period, kiteres;

	double targetSPL { soundPressureLevel };

	enum Direction
	{
		TOWARD_SOURCE,
		TOWARD_TARGET
	};

	std::string to_string(Direction dir);

	Direction calcDirection(Wall wall, double sourceGradient, double targetGradient);
	ReflectionPoint calcInitalReflectionPoint(Wall wall);
	ReflectionPoint calcNextReflectionPoint(Direction direction, int increment, const ReflectionPoint& reflectionP);
	double getAngle(const Point& point1, const Point& point2);
	int xRange(int x);
	int yRange(int y);
	void calcDisplOnly();
};


#endif /* ROOM_HPP_ */
