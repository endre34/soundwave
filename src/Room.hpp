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

	void calcReflectionPoints();
	void calcDistances();
	void calcKiteresek();

	ReflectionPoint calcReflectionPoint(Wall wall);

	friend class DrawRoom;

private:
	int sizeX, sizeY;
	Point source, target;
	std::vector<ReflectionPoint> reflectionPoints;

	std::vector<int> distances;
	std::vector<double> kiteresek;

	// terjedesi sebesseg: 343.5
	// levego surusege: 1.2045
	const int SPL = 70;		// @ 1m from source
	int waveleght, frequency;
	double period, maxAmplitude, kiteres;

	enum Direction
	{
		TOWARD_SOURCE,
		TOWARD_TARGET
	};
	std::string to_string(Direction dir);

	Direction calcDirection(Wall wall, double sourceGradient, double targetGradient);
	ReflectionPoint calcInitalReflectionPoint(Wall wall);
	ReflectionPoint calcNextReflectionPoint(Direction direction, int increment, const ReflectionPoint& reflectionP);
};


#endif /* ROOM_HPP_ */
