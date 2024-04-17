/*
 *  Project: SzalontaGrafika2024
 *   Author: Endre
 */

//#include <cmath>
//
//#include "DrawRoom.hpp"
//
//
//DrawRoom::DrawRoom(const int sizeX, const int sizeY)
//{
//	Room(sizeX, sizeY);
//
//	setSize(sizeX, sizeY);
//
//	room.setFillColor(sf::Color::White);
//	room.setOutlineColor(sf::Color::Black);
//	room.setOutlineThickness(10.f);
//	room.setPosition(0.f, 0.f);
//}
//
//void DrawRoom::setSize(const int sizeX, const int sizeY)
//{
//	this->sizeX = sizeX;
//	this->sizeY = sizeY;
//
//	double ratio = static_cast<double>(sizeX) / static_cast<double>(sizeY);
//
//	room.setSize(sf::Vector2f(640.f, round(640.0 * 1.0 / ratio)));
//	if (room.getSize().y > 1000)
//		room.setSize(sf::Vector2f(round(1000 * ratio), 1000));
//}
//
//
//
//
//
//
//
//
//void DrawRoom::draw(sf::RenderTarget& target, sf::RenderStates& states) const
//{
//	states.transform *= getTransform();
//	states.texture = NULL;
//
//	target.draw(room, states);
//	for (auto &i : drawpoints)
//	{
//		target.draw(i, states);
//	}
//}

