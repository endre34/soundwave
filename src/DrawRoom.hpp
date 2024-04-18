/*
 *  Project: SzalontaGrafika2024
 *   Author: Endre
 */

#ifndef DRAWROOM_HPP_
#define DRAWROOM_HPP_

#include <SFML/Graphics.hpp>

#include "Room.hpp"

class DrawRoom
{
public:
	DrawRoom(const Room& room);
	~DrawRoom();

private:
	Room* room;

};



#endif /* DRAWROOM_HPP_ */
