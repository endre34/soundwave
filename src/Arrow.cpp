/*
 *  Project: SzalontaGrafika2024
 *   Author: Endre
 */

#include <cmath>
#include <iostream>
#include <iomanip>

#include "Arrow.hpp"
#include "Point.hpp"
#include "utils.hpp"


using namespace std;
using namespace sf;


//	Creates an arrow from point1 towards point2

Arrow::Arrow(const Vector2f& point1,const Vector2f& point2)
{
//	#############################	LINE	#########################################
	double size = sqrt(pow(point1.x - point2.x, 2) + pow(point1.y - point2.y, 2));
	line.setSize(Vector2f(size, 3));

	cout << "Size: x: " << line.getSize().x << ", y: " << line.getSize().y << endl;

	line.setOrigin(0, line.getLocalBounds().height / 2);

	line.setPosition(point1);

	cout << "Position: x: " << line.getPosition().x << ", y: " << line.getPosition().y << endl;

	double angle = get_angle(point1, point2);
	line.setRotation(angle);

	cout << "Rotation: " << line.getRotation() << endl;

	line.setFillColor(Color::Black);

	cout << endl;

//	########################	HEAD	##############################################
	head.setFillColor(Color::Black);
	head.setRadius(10);
	head.setPointCount(3);
	head.setOrigin(head.getLocalBounds().width / 2, head.getLocalBounds().height / 2);
	head.setPosition((point1.x + point2.x) / 2, (point1.y + point2.y) / 2);
	head.setRotation(angle + 90);
}

void Arrow::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();

	states.texture = nullptr;

	target.draw(line);
	target.draw(head);
}

double Arrow::get_angle(const sf::Vector2f& point1,const sf::Vector2f& point2)
{
	double gradient = Point::calcGradientPrecise(Point(point1.x, point1.y), Point(point2.x, point2.y));
	double angle = atan(gradient) * 180.0 / M_PI;

	if (point2.x - point1.x < 0)
	{
		angle += 180.0;
	}

	return angle;
}








