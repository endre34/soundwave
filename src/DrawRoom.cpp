/*
 *  Project: SzalontaGrafika2024
 *   Author: Endre
 */

#include <iostream>
#include <iomanip>
#include <unistd.h>
#include <cmath>

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
	auto origin = this->bounds.getPosition();

	// source
	points.push_back(VertexArray(TriangleFan, 32));

	for (int i = 0; i < (int)points.back().getVertexCount(); ++i)
	{
		points.back()[i].color = Color::Green;
	}
	points.back()[0].position = Vector2f(origin.x + millisToPixels(room.source.getX()),
			origin.y + millisToPixels(room.source.getY()));

	for (int i = 1; i < (int)points.back().getVertexCount(); ++i)
	{
		double angle = 12 * (i - 1) * M_PI / (double)180;
		points.back()[i].position = Vector2f(points.back()[0].position.x + cos(angle) * 10,
											points.back()[0].position.y + sin(angle) * 10);
	}


	// target
	points.push_back(VertexArray(TriangleFan, 32));

	for (int i = 0; i < (int)points.back().getVertexCount(); ++i)
	{
		points.back()[i].color = Color::Red;
	}
	points.back()[0].position = Vector2f(origin.x + millisToPixels(room.target.getX()),
			origin.y + millisToPixels(room.target.getY()));

	for (int i = 1; i < (int)points.back().getVertexCount(); ++i)
	{
		double angle = 12 * (i) * M_PI / (double)180;
		points.back()[i].position = Vector2f(points.back()[0].position.x + cos(angle) * 10,
											points.back()[0].position.y + sin(angle) * 10);
	}

	// reflection points
	for (ReflectionPoint rp : room.reflectionPoints)
	{
		points.push_back(VertexArray(TriangleFan, 17));

		for (int i = 0; i < (int)points.back().getVertexCount(); ++i)
		{
			points.back()[i].color = Color::Cyan;
		}
		points.back()[0].position = Vector2f(origin.x + millisToPixels(rp.getX()),
				origin.y + millisToPixels(rp.getY()));

		for (int i = 1; i < (int)points.back().getVertexCount(); ++i)
		{
			double angle = (startAngle(rp.getWall()) + 12 * (i - 1)) * M_PI / (double)180;
			points.back()[i].position = Vector2f(points.back()[0].position.x + cos(angle) * 10,
												points.back()[0].position.y + sin(angle) * 10);
		}
	}
}

void DrawRoom::createWaveDir()
{
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

int DrawRoom::startAngle(Wall wall)
{
	switch (wall)
	{
	case Top:
		return 0;
	case Bottom:
		return 180;
	case Left:
		return -90;
	case Right:
		return 90;
	default:
		throw runtime_error("Unrecognized wall");
	}
}







