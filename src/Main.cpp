/*
 *  Project: SzalontaGrafika2024
 *   Author: Endre
 */

#include <iostream>
#include <SFML/Graphics.hpp>

#include "Room.hpp"
#include "DrawRoom.hpp"

using namespace std;
using namespace sf;


int main()
{
	Room room(16, 9);
	DrawRoom droom(room);
    return 0;
}
