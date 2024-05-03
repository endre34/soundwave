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

	RenderWindow window(VideoMode(dRoom.getVisualizationSize().x, dRoom.getVisualizationSize().y), "Hanginterferencia modellezese");
	window.setFramerateLimit(30);

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
		    	dRoom.setSize(event.size.width - dRoom.getExtension() * 2);
		    	dRoom.calcTransformRatio();
		    	dRoom.createPoints();
		    	dRoom.createWaveDir();

//		    	cout << "Room: x: " << dRoom.getVisualizationSize().x << ", y: " <<  dRoom.getVisualizationSize().y << endl;
//		    	cout << "Window: x: " << event.size.width << ", y: " <<  event.size.height << endl;
//		    	cout << endl;


		    	// viewport only works with actual window size
//		        sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
//		        window.setView(sf::View(visibleArea));

		    	window.setSize(dRoom.getVisualizationSize());
		        sf::FloatRect visibleArea(0, 0, dRoom.getVisualizationSize().x, dRoom.getVisualizationSize().y);
		        window.setView(sf::View(visibleArea));
		    }
		}

		window.clear(Color(245, 245, 245));
		window.draw(dRoom);
		window.display();
	}
    return 0;
}
