/*
 *  Project: SzalontaGrafika2024
 *   Author: Endre
 */

#ifndef ROOM_HPP_
#define ROOM_HPP_

#include <vector>

#include "Point.hpp"


class Room										// Mi az amplitudo es az ido???
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

	void calcReflectionPoints();
	void calcDistances();

	int calcDistance(const Point& point1, const Point& point2);
	ReflectionPoint calcReflectionPoint(Wall wall);

private:
	int sizeX, sizeY;
	Point source, target;
	std::vector<ReflectionPoint> reflectionPoints;

	std::vector<int> distances;

	int waveleght;
	double period;

	enum Direction
	{
		To_Source,
		To_Target
	};

	ReflectionPoint calcInitalReflectionPoint(Wall wall);
	ReflectionPoint getNextReflectionPoint(Direction direction, int increment, const ReflectionPoint& reflectionP);
};


#endif /* ROOM_HPP_ */
