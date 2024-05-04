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
	dRoom.createPoints();
	dRoom.setMode(SHOW_REFLECTIONS);

	Cursor arrowCursor;
	arrowCursor.loadFromSystem(Cursor::Arrow);

	Cursor handCursor;
	handCursor.loadFromSystem(Cursor::Hand);


	RenderWindow window(VideoMode(dRoom.getVisualizationSize().x, dRoom.getVisualizationSize().y), "Hanginterferencia modellezese");
	window.setFramerateLimit(10);

	while (window.isOpen())
	{
		window.clear(Color(245, 245, 245));
		window.draw(dRoom);

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

		    	dRoom.createPoints();
		    	dRoom.resetMode(SHOW_REFLECTIONS);

		    	window.setSize(dRoom.getVisualizationSize());
		        sf::FloatRect visibleArea(0, 0, dRoom.getVisualizationSize().x, dRoom.getVisualizationSize().y);
		        window.setView(sf::View(visibleArea));
		    }

		    if (event.type == sf::Event::MouseMoved)
		    {
		    	Vector2f mousePos = static_cast<Vector2f>(Mouse::getPosition(window));
		    	FloatRect sourceBox = dRoom.getSourceBounds();
		    	FloatRect targetBox = dRoom.getTargetBounds();

		    	if (sourceBox.contains(mousePos))
		    	{
		    		window.setMouseCursor(handCursor);
		    	}
		    	else if (targetBox.contains(mousePos))
				{
		    		window.setMouseCursor(handCursor);
				}
		    	else
		    	{
		    		window.setMouseCursor(arrowCursor);
		    	}
		    }

		    if (event.type == sf::Event::MouseButtonPressed)
		    {
		    	Vector2f mousePos = static_cast<Vector2f>(Mouse::getPosition(window));
		    	FloatRect sourceBox = dRoom.getSourceBounds();
		    	FloatRect targetBox = dRoom.getTargetBounds();

		    	if (sourceBox.contains(mousePos))
		    	{
		    		dRoom.setMode(SHOW_DISTANCES);
		    	}
		    	else if (targetBox.contains(mousePos))
				{
		    		dRoom.setMode(SHOW_DISTANCES);
				}
		    }
		    else if (event.type == sf::Event::MouseButtonReleased)
		    {
		    	dRoom.setMode(SHOW_REFLECTIONS);
		    }
		}

		window.display();
	}
    return 0;
}
