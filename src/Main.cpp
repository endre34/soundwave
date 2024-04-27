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
	Room room(5.6, 6.5);
	room.setSource(Point(1.0, 2.6));
	room.setTarget(Point(3.7, 4.0));
	room.calcReflectionPoints();
	room.calcDistances();
	//room.setParams(57);
	//room.calcKiteresek();

	DrawRoom dRoom(room);
	dRoom.setSize(640);
	dRoom.calcTransformRatio();
	dRoom.createPoints();
	dRoom.createWaveDir();

	RenderWindow window(VideoMode(dRoom.getWindowSize().x, dRoom.getWindowSize().y), "test1");
	window.setFramerateLimit(1);

//	window.setSize(dRoom.getWindowSize());

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				window.close();
			}

		    if (event.type == sf::Event::Resized)
		    {
		        sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
		        window.setView(sf::View(visibleArea));
		    }
		}

		window.clear(Color::White);
		window.draw(dRoom);
		window.display();
	}
    return 0;
}
