/*
 *  Project: SzalontaGrafika2024
 *   Author: Endre
 */

#include <cmath>
#include <iostream>
#include <iomanip>

#include "Header_files/ComplexShapes.hpp"
#include "Header_files/Point.hpp"
#include "Header_files/utils.hpp"


using namespace std;
using namespace sf;


//	Creates an arrow from point1 towards point2

Arrow::Arrow(const Vector2f& point1,const Vector2f& point2)
{
//	#############################	LINE	#########################################
	double size = sqrt(pow(point1.x - point2.x, 2) + pow(point1.y - point2.y, 2));
	line.setSize(Vector2f(size, 3));

	line.setOrigin(0, line.getLocalBounds().height / 2);

	line.setPosition(point1);

	double angle = get_angle(point1, point2);
	line.setRotation(angle);

	line.setFillColor(Colors::DARKGREY);

//	########################	HEAD	##############################################
	head.setFillColor(Colors::BLACK);
	head.setRadius(10);
	head.setPointCount(3);
	head.setOrigin(head.getLocalBounds().width / 2, head.getLocalBounds().height / 2);
	head.setPosition((point1.x + point2.x) / 2, (point1.y + point2.y) / 2);
	head.setRotation(angle + 90);
}

void Arrow::draw(RenderTarget& target, RenderStates states) const
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

DoubleHeadedArrow::DoubleHeadedArrow()
{
	// empty
}

DoubleHeadedArrow::DoubleHeadedArrow(const sf::Vector2f& point1,const sf::Vector2f& point2)
{
	setArrow(point1, point2);
}

void DoubleHeadedArrow::setArrow(const Vector2f& point1, const Vector2f& point2)
{
	//	################################	line	#####################################

		double size = sqrt(pow(point1.x - point2.x, 2) + pow(point1.y - point2.y, 2)) - 10;
		line.setSize(Vector2f(size, 3));

		line.setOrigin(0, line.getLocalBounds().height / 2);

		line.setPosition(point1);

		double angle = get_angle(point1, point2);
		line.setRotation(angle);

		line.setFillColor(Colors::RED);

	//	################################	head1	#####################################

		head1.setFillColor(Color::Black);
		head1.setRadius(10);
		head1.setPointCount(3);
		head1.setOrigin(head1.getRadius(), 0);
		head1.setPosition(point1.x, point1.y);
		head1.setRotation(angle - 90);

	//	################################	head2	#####################################

		head2.setFillColor(Colors::BLACK);
		head2.setRadius(10);
		head2.setPointCount(3);
		head2.setOrigin(head2.getRadius(), 0);
		head2.setPosition(point2.x, point2.y);
		head2.setRotation(angle + 90);
}

void DoubleHeadedArrow::draw(RenderTarget& target, RenderStates states) const
{
	states.transform *= getTransform();

	states.texture = nullptr;

	target.draw(line, states);
	target.draw(head1, states);
	target.draw(head2, states);
}

double DoubleHeadedArrow::get_angle(const sf::Vector2f& point1,const sf::Vector2f& point2)
{
	double gradient = Point::calcGradientPrecise(Point(point1.x, point1.y), Point(point2.x, point2.y));
	double angle = atan(gradient) * 180.0 / M_PI;

	if (point2.x - point1.x < 0)
	{
		angle += 180.0;
	}

	return angle;
}

Target::Target()
{
	// empty
}

Target::Target(const Vector2f& position, const sf::CircleShape& source)
{
	inner.setRadius(source.getRadius() * 2 / 3);
	inner.setFillColor(source.getFillColor());
	inner.setOrigin(inner.getRadius(), inner.getRadius());
	inner.setPosition(position);

	outer.setRadius(source.getRadius());
	outer.setFillColor(Colors::WHITE);
	outer.setOrigin(outer.getRadius(), outer.getRadius());
	outer.setPosition(position);
	outer.setOutlineColor(source.getFillColor());
	outer.setOutlineThickness(-source.getRadius() / 6);
}

void Target::setTarget(const Vector2f& position, const sf::CircleShape& source)
{
	inner.setRadius(source.getRadius() * 2 / 3);
	inner.setFillColor(source.getFillColor());
	inner.setOrigin(inner.getRadius(), inner.getRadius());
	inner.setPosition(position);

	outer.setRadius(source.getRadius());
	outer.setFillColor(Colors::WHITE);
	outer.setOrigin(outer.getRadius(), outer.getRadius());
	outer.setPosition(position);
	outer.setOutlineColor(source.getFillColor());
	outer.setOutlineThickness(-source.getRadius() / 6);
}

Vector2f Target::getPosition()
{
	return inner.getPosition();
}

FloatRect Target::getGlobalBounds()
{
	return outer.getGlobalBounds();
}

void Target::move(const sf::Vector2f& offset)
{
	inner.move(offset);
	outer.move(offset);
}

void Target::draw(RenderTarget& target, RenderStates states) const
{
	states.transform *= getTransform();

	states.texture = nullptr;

	target.draw(outer, states);
	target.draw(inner, states);
}










