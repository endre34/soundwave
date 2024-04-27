/*
 *  Project: SzalontaGrafika2024
 *   Author: Endre
 */

#include <iostream>
#include <iomanip>
#include <unistd.h>

#include "DrawRoom.hpp"
#include "utils.hpp"

using namespace std;
using namespace sf;


DrawRoom::DrawRoom(Room& r):
		room(r),
		sizeX { 0 },
		sizeY { 0 },
		ratio { 1 }
{
	bounds.setPosition(Vector2f(50, 50));
	bounds.getPosition();
	bounds.setFillColor(Color::White);
	bounds.setOutlineColor(Color::Blue);
	bounds.setOutlineThickness(3);


}

void DrawRoom::setSize(int x)
{
	double ratio = (double)room.sizeX / room.sizeY;

	this->sizeX = x;
	this->sizeY = x / ratio;

	bounds.setSize(Vector2f(x, x / ratio));

	if (bounds.getSize().y > 900)
	{
		this->sizeX = 900 * ratio;
		this->sizeY = 900;

		bounds.setSize(Vector2f(900 * ratio, 900));
	}
}

Vector2u DrawRoom::getSize()
{
	return Vector2u(bounds.getSize());
}

Vector2u DrawRoom::getWindowSize()
{
	Vector2u v2u(bounds.getSize());
	v2u.x += 100;
	v2u.y += 100;
	return v2u;
}

void DrawRoom::calcTransformRatio()
{
	ratio = room.sizeX / bounds.getSize().x;
}

void DrawRoom::createPoints()
{
	// source
	points.push_back(CircleShape(10));
	points.back().setFillColor(Color::Green);
	{
	auto bounds = points.back().getLocalBounds();
	points.back().setOrigin(bounds.width / 2, bounds.height / 2);

	auto origin = this->bounds.getPosition();
	points.back().setPosition(Vector2f(origin.x + millisToPixels(room.source.getX()),
			origin .y + millisToPixels(room.source.getY())));
	}

	// target
	points.push_back(CircleShape(10));
	points.back().setFillColor(Color::Red);
	{
	auto bounds = points.back().getLocalBounds();
	points.back().setOrigin(bounds.width / 2, bounds.height / 2);

	auto origin = this->bounds.getPosition();
	points.back().setPosition(Vector2f(origin.x + millisToPixels(room.target.getX()),
			origin.y + millisToPixels(room.target.getY())));
	}

	// reflection points
	for (auto i : room.reflectionPoints)
	{
		points.emplace_back(CircleShape(7));
		points.back().setFillColor(Color::Yellow);

		auto bounds = points.back().getLocalBounds();
		points.back().setOrigin(bounds.width / 2, bounds.height / 2);

		auto origin = this->bounds.getPosition();
		points.back().setPosition(origin.x + millisToPixels(i.getX()), origin.y + millisToPixels(i.getY()));
	}
}

void DrawRoom::createWaveDir()
{
	for (auto i : points)
	{
		waveDirections.emplace_back(room.source, Point(i.getPosition().x, i.getPosition().y), ratio);
		waveDirections.emplace_back(Point(i.getPosition().x, i.getPosition().y), room.target, ratio);
	}
	waveDirections.emplace_back(room.source, room.target, ratio);
}

double DrawRoom::millisToPixels(int millis)
{
	return millis / ratio;
}

void DrawRoom::draw(RenderTarget& target, RenderStates states) const
{
	states.transform *= getTransform();

	states.texture = nullptr;

	target.draw(bounds);

	for (auto i : waveDirections)
	{
		target.draw(i);
	}

	for (auto i : points)
	{
		target.draw(i);
	}
}
