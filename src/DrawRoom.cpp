/*
 *  Project: SzalontaGrafika2024
 *   Author: Endre
 */

#include <iostream>
#include <iomanip>
#include <cmath>

#include "Header_files/DrawRoom.hpp"
#include "Header_files/utils.hpp"

using namespace std;
using namespace sf;


DrawRoom::DrawRoom(Room& r):
		room(r),
		mode { UNSELECTED },
		extension { 25 },
		ratio { 1 },
		movedObject { NOTHING },
		begin(0, 0),
		end(begin)
{
	bounds.setPosition(Vector2f(extension, extension));
	bounds.getPosition();
	bounds.setFillColor(Colors::WHITE);
	bounds.setOutlineColor(Colors::BLUE);
	bounds.setOutlineThickness(3);

	font.loadFromFile("Media/noto_sans.ttf");
	textX.setFont(font);
	textY.setFont(font);
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

	calcTransformRatio();
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


void DrawRoom::setMode(Mode mode)
{
	switch (mode)
	{
	case SHOW_REFLECTIONS:
		if (this->mode != mode)
		{
			room.calcReflectionPoints();
			room.calcDistances();
			room.calcDisplacement();

			cout << endl;
			cout << fixed << setprecision(3);
			cout << "Hangintenzitas a hallgatonal: " << room.getTargetSPL() << endl;
			room.calcBestPos();

			createReflectionPoints();
			createWaveDir();
			createBestPos();

			this->mode = mode;
		}
		break;

	case SHOW_DISTANCES:
		if (this->mode != mode)
		{
			createDistances();

			this->mode = mode;
		}
		break;

	default:
		break;
	}
}

void DrawRoom::resetMode()
{
	Mode mode = this->mode;
	this->mode = UNSELECTED;

	setMode(mode);
}

void DrawRoom::createPoints()
{
	Vector2f origin = bounds.getPosition();

	double Size = 15;

	// source
	source.setFillColor(Colors::RED);
	source.setRadius(Size);
	source.setOrigin(Size, Size);
	source.setPosition(origin.x + millisToPixels(room.source.getX()),
			origin.y + millisToPixels(room.source.getY()));


	// target
	target.setTarget(Vector2f(origin.x + millisToPixels(room.target.getX()),
			origin.y + millisToPixels(room.target.getY())), source);
}

void DrawRoom::setMoveBegin(const Vector2f& pos)
{
	begin = pos;
}

void DrawRoom::setMoveEnd(const Vector2f& pos)
{
	end = pos;
}

void DrawRoom::setMovedPoint(Object object)
{
	movedObject = object;
}

Object DrawRoom::getMovedPoint()
{
	return movedObject;
}

void DrawRoom::movePoint()
{
	Vector2f delta(end.x - begin.x, end.y - begin.y);

	switch (movedObject)
	{
	case SOURCE:
		source.move(delta);

		room.setSource(Point(pixelsToMillis(source.getPosition().x - bounds.getPosition().x),
							pixelsToMillis(source.getPosition().y - bounds.getPosition().y)));

		break;

	case TARGET:
		target.move(delta);

		room.setTarget(Point(pixelsToMillis(target.getPosition().x - bounds.getPosition().x),
							pixelsToMillis(target.getPosition().y - bounds.getPosition().y)));

		break;

	default:
		break;
	}
	begin = end;
}

int DrawRoom::getExtension()
{
	return extension;
}

FloatRect DrawRoom::getSourceBounds()
{
	return this->source.getGlobalBounds();
}

FloatRect DrawRoom::getTargetBounds()
{
	return target.getGlobalBounds();
}

Vector2f DrawRoom::getSourcePos()
{
	return source.getPosition();
}

void DrawRoom::createDistances()
{
	if (movedObject == SOURCE)
	{
		Vector2f pointX(bounds.getPosition().x, source.getPosition().y);
		Vector2f pointS(source.getPosition().x - 8, source.getPosition().y);
		distX.setArrow(pointS, pointX);

		textX.setCharacterSize(15);
		textX.setFillColor(Colors::BLACK);

		string meters = to_string(room.getSource().getXMeters());
		meters.erase(meters.find_last_not_of('0') + 1, string::npos);
		meters += " m";
		textX.setString(meters);

		textX.setOrigin(textX.getGlobalBounds().width / 2, textX.getGlobalBounds().height);
		textX.setPosition((pointX.x + pointS.x) / 2, (pointX.y + pointS.y) / 2 - 10);


		Vector2f pointY(source.getPosition().x, bounds.getPosition().y);
		pointS = Vector2f(source.getPosition().x, source.getPosition().y - 8);
		distY.setArrow(pointS, pointY);

		textY.setCharacterSize(15);
		textY.setFillColor(Colors::BLACK);


		meters = to_string(room.getSource().getYMeters());
		meters.erase(meters.find_last_not_of('0') + 1, string::npos);
		meters += " m";
		textY.setString(meters);

		textY.setOrigin(0, textY.getGlobalBounds().height / 2);
		textY.setPosition((pointY.x + pointS.x) / 2 + 10, (pointY.y + pointS.y) / 2);
	}
	else if (movedObject == TARGET)
	{
		Vector2f pointX(bounds.getPosition().x, target.getPosition().y);
		Vector2f pointT(target.getPosition().x - 8, target.getPosition().y);
		distX.setArrow(pointT, pointX);

		textX.setCharacterSize(15);
		textX.setFillColor(Colors::BLACK);

		string meters = to_string(room.getTarget().getXMeters());
		meters.erase(meters.find_last_not_of('0') + 1, string::npos);
		meters += " m";
		textX.setString(meters);

		textX.setOrigin(textX.getGlobalBounds().width / 2, textX.getGlobalBounds().height);
		textX.setPosition((pointX.x + pointT.x) / 2, (pointX.y + pointT.y) / 2 - 10);

		Vector2f pointY(target.getPosition().x, bounds.getPosition().y);
		pointT = Vector2f(target.getPosition().x, target.getPosition().y - 8);
		distY.setArrow(pointT, pointY);

		textY.setCharacterSize(15);
		textY.setFillColor(Colors::BLACK);

		meters = to_string(room.getTarget().getYMeters());
		meters.erase(meters.find_last_not_of('0') + 1, string::npos);
		meters += " m";
		textY.setString(meters);

		textY.setOrigin(0, textY.getGlobalBounds().height / 2);
		textY.setPosition((pointY.x + pointT.x) / 2 + 10, (pointY.y + pointT.y) / 2);
	}
}

void DrawRoom::createReflectionPoints()
{
	reflectionPoints.clear();

	double rpSize = 10;
	Vector2f origin = bounds.getPosition();

	for (ReflectionPoint rp : room.reflectionPoints)
	{
		reflectionPoints.push_back(VertexArray(TriangleFan, 17));

		for (int i = 0; i < (int)reflectionPoints.back().getVertexCount(); ++i)
		{
			reflectionPoints.back()[i].color = Colors::CYAN;
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

void DrawRoom::createBestPos()
{
	optimalPosition.setRadius(15);
	optimalPosition.setFillColor(Colors::TRANSPARENTGREEN);
	optimalPosition.setOrigin(optimalPosition.getRadius(), optimalPosition.getRadius());
	optimalPosition.setPosition(bounds.getPosition().x + millisToPixels(room.optimalPosition.getX()),
								bounds.getPosition().y + millisToPixels(room.optimalPosition.getY()));

}

void DrawRoom::calcTransformRatio()
{
	ratio = room.sizeX / bounds.getSize().x;
}

double DrawRoom::millisToPixels(int millis)
{
	return millis / ratio;
}

int DrawRoom::pixelsToMillis(double pixels)
{
	return (int)(pixels * ratio);
}

void DrawRoom::draw(RenderTarget& target, RenderStates states) const
{
	states.transform *= getTransform();

	states.texture = nullptr;

	target.draw(bounds);

	switch (mode)
	{
	case SHOW_REFLECTIONS:

		for (auto i : waveDirections)
		{
			target.draw(i);
		}

		for (VertexArray i : reflectionPoints)
		{
			target.draw(i);
		}

		break;

	case SHOW_DISTANCES:

		target.draw(distX, states);
		target.draw(textX, states);

		target.draw(distY, states);
		target.draw(textY, states);

		break;

	default:
		break;
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










