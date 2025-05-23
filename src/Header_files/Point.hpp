/*
 *  Project: SzalontaGrafika2024
 *   Author: Endre
 */

#ifndef POINT_HPP_
#define POINT_HPP_


enum Wall
{
	Top,
	Bottom,
	Left,
	Right
};

class Point
{
public:
	Point(double x, double y);
	Point(int x, int y);
	Point(const Point& point);
	Point();

//	void setCoords(double x, double y);
//	void setX(double x);
//	void setY(double y);

	void setCoords(int x, int y);
	void setX(int x);
	void setY(int y);

	int getX() const;
	int getY() const;

	double getXMeters() const;
	double getYMeters() const;

	bool isValid() const;

	friend std::ostream& operator <<(std::ostream& out, const Point& point);

	static double calcGradient(const Point& p1, const Point& p2);
	static double calcGradientPrecise(const Point& p1, const Point& p2);
	static int calcDistance(const Point& p1, const Point& p2);

private:
	int x, y;
};

class ReflectionPoint : public Point
{
public:
	ReflectionPoint(double x, double y, Wall wall);
	ReflectionPoint(int x, int y, Wall wall);
	ReflectionPoint();

	Wall getWall() const;

private:
	Wall wall;
};

#endif /* POINT_HPP_ */
