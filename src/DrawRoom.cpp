/*
 *  Project: SzalontaGrafika2024
 *   Author: Endre
 */

#include "DrawRoom.hpp"

using namespace std;
using namespace sf;

DrawRoom::DrawRoom(const Room& room)
{
	this->room = new Room(room);
}

DrawRoom::~DrawRoom()
{
	delete room;
}

void DrawRoom::draw(RenderTarget& target, RenderStates states) const
{
	states.transform *= getTransform();

	states.texture = nullptr;

	target.draw(bounds);

	for (auto i : points)
	{
		target.draw(i);
	}
}
