/*
 *  Project: SzalontaGrafika2024
 *   Author: Endre
 */

#include <iostream>
#include <SFML/Graphics.hpp>

#include "Room.hpp"
#include "DrawRoom.hpp"
#include "utils.hpp"

using namespace std;
using namespace sf;


int main()
{
	Room room(10.0, 10.0);
	room.setSource(Point(4.3, 4.8));
	room.setTarget(Point(9.1, 8.7));
	room.calcReflectionPoints();
	room.calcDistances();

	DrawRoom droom(room);
    return 0;
}
