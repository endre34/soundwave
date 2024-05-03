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
	Room room(5.6, 6.0);
	room.setSource(Point(2.7, 3.0));
	room.setTarget(Point(0.4, 5.0));
	room.calcReflectionPoints();
	room.calcDistances();
	//room.setParams(57);
	//room.calcKiteresek();

	DrawRoom dRoom(room);
	dRoom.setSize(640);
	dRoom.calcTransformRatio();
	dRoom.createPoints();
	dRoom.createWaveDir();

	RenderWindow window(VideoMode(dRoom.getWindowSize().x, dRoom.getWindowSize().y), "Hanginterferencia modellezese");
	window.setFramerateLimit(1);

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
