/*
 * room.h
 *
 *  Created on: Apr 3, 2024
 *      Author: Endre
 */

#ifndef ROOM_H_
#define ROOM_H_

#include <vector>

enum Wall
{
	Top,
	Bottom,
	Left,
	Right
};

struct Point
{
	int x;										// Milimeters
	int y;

	Point();
	Point(const int x, const int y);

	void to_mm();
	void to_m();								// not available
	void out();
};

class Room										// Mi az amplitudo es az ido???
{
public:
	Room(const int sizeX, const int sizeY);

	void setSource(const Point source);
	void setTarget(const Point target);
	void setParams(const int freq);

	void calcReflectionPoints();
	void calcDistances();

	Point calcReflectionP(const Wall wall);

private:
	enum Direction
	{
		To_Source,
		To_Target
	};

	struct ReflectionP
	{
		Point point;
		Wall wall;

		ReflectionP(const Point point, const Wall wall);
	};

	int sizeX, sizeY;											// Meters
	Point source, target;										// Milimeters
	std::vector<ReflectionP> reflectionPoints;
	std::vector<int> distances;
	int waveleght;												// Milimeters
	double period;

	double calcDir(const Point p1, const Point p2);

	Point getInitalRP(const Wall wall);
	Point getNextRP(const Direction direction, const Wall wall,
			const int increment, const Point reflectionP);
};


#endif /* ROOM_H_ */
