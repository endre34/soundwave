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
		extension { 25 },
		ratio { 1 }
{
	bounds.setPosition(Vector2f(extension, extension));
	bounds.getPosition();
	bounds.setFillColor(Color::White);
	bounds.setOutlineColor(Color::Blue);
	bounds.setOutlineThickness(3);


}

void DrawRoom::setSize(int x)
{
	double ratio = (double)room.sizeX / room.sizeY;

	bounds.setSize(Vector2f(x, x / ratio));

	int maxY = 900 - extension * 2;
	if (bounds.getSize().y > maxY)
	{
		bounds.setSize(Vector2f(maxY * ratio, maxY));
	}
}

Vector2u DrawRoom::getRoomSize()
{
	return Vector2u(bounds.getSize());
}

Vector2u DrawRoom::getVisualizationSize()
{
	Vector2u v2u(bounds.getSize());
	v2u.x += extension * 2;
	v2u.y += extension * 2;
	return v2u;
}

void DrawRoom::calcTransformRatio()
{
	ratio = room.sizeX / bounds.getSize().x;
}

void DrawRoom::createPoints()
{
	reflectionPoints.clear();

	auto origin = bounds.getPosition();
	double rpSize = 10;
	double stSize = 15;

	// source
	source.setFillColor(Color(104, 216, 107));
	source.setRadius(stSize);
	source.setOrigin(stSize, stSize);
	source.setPosition(origin.x + millisToPixels(room.source.getX()),
			origin.y + millisToPixels(room.source.getY()));


	// target
	target.setTarget(Vector2f(origin.x + millisToPixels(room.target.getX()),
			origin.y + millisToPixels(room.target.getY())), source);

	// reflection points
	for (ReflectionPoint rp : room.reflectionPoints)
	{
		reflectionPoints.push_back(VertexArray(TriangleFan, 17));

		for (int i = 0; i < (int)reflectionPoints.back().getVertexCount(); ++i)
		{
			reflectionPoints.back()[i].color = Color::Cyan;
		}
		reflectionPoints.back()[0].position = Vector2f(origin.x + millisToPixels(rp.getX()),
				origin.y + millisToPixels(rp.getY()));

		for (int i = 1; i < (int)reflectionPoints.back().getVertexCount(); ++i)
		{
			double angle = (startAngle(rp.getWall()) + 12 * (i - 1)) * M_PI / (double)180;
			reflectionPoints.back()[i].position = Vector2f(reflectionPoints.back()[0].position.x + cos(angle) * rpSize,
												reflectionPoints.back()[0].position.y + sin(angle) * rpSize);
		}
	}
}

void DrawRoom::createWaveDir()
{
	waveDirections.clear();

	for (int i = 0; i < (int)reflectionPoints.size(); ++i)
	{
		waveDirections.emplace_back(source.getPosition(), reflectionPoints[i][0].position);
		waveDirections.emplace_back(reflectionPoints[i][0].position, target.getPosition());
	}
	waveDirections.emplace_back(source.getPosition(), target.getPosition());
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

	for (auto i : reflectionPoints)
	{
		target.draw(i);
	}

	target.draw(this->source, states);
	target.draw(this->target, states);
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


int DrawRoom::getExtension()
{
	return extension;
}







