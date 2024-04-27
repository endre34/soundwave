/*
 *  Project: SzalontaGrafika2024
 *   Author: Endre
 */

#include <cmath>

#include "Arrow.hpp"


using namespace std;
using namespace sf;


//	Creates an arrow from point1 towards point2

Arrow::Arrow(const Point& point1,const Point& point2, double ratio)
{
	double size = sqrt(pow(point1.getX() - point2.getX(), 2) + pow(point1.getY() - point2.getY(), 2));
	line.setSize(Vector2f(2.5, size));

	line.setOrigin(line.getGlobalBounds().width / 2, 0);
	line.setPosition(point1.getX(), point1.getY());

	line.setRotation(atan(Point::calcGradient(point1, point2)));

	line.setFillColor(Color::Black);
}

void Arrow::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();

	states.texture = nullptr;

	target.draw(line);
	target.draw(head);
}

