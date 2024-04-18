/*
 *  Project: SzalontaGrafika2024
 *   Author: Endre
 */

#include "DrawRoom.hpp"

DrawRoom::DrawRoom(const Room& room)
{
	this->room = new Room(room);
}

DrawRoom::~DrawRoom()
{
	delete Room room;
}
