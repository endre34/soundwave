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

	void setSource(const Point& source);
	void setTarget(const Point target);
	void setParams(const int freq);
	void setSize(const int sizeX, const int sizeY);

	void calcReflectionPoints();
	void calcDistances();

	Point calcReflectionP(const Wall wall);

private:
	int sizeX, sizeY;
	Point source, target;
	std::vector<ReflectionPoint> reflectionPoints;

	enum Direction
	{
		To_Source,
		To_Target
	};

	std::vector<int> distances;
	int waveleght;
	double period;

	double calcDir(const Point p1, const Point p2);

	Point getInitalRP(const Wall wall);
	ReflectionPoint getNextRP(const Direction direction,
			const int increment, const ReflectionPoint reflectionP);
};


#endif /* ROOM_HPP_ */
