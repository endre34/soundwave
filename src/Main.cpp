/*
 *  Project: SzalontaGrafika2024
 *   Author: Endre
 */

#include <iostream>
#include <SFML/Graphics.hpp>

#include "Header_files/Room.hpp"
#include "Header_files/DrawRoom.hpp"
#include "Header_files/Button.hpp"
#include "Header_files/utils.hpp"

using namespace std;
using namespace sf;


void creditsMenu(RenderWindow& window);

int main()
{
	Room room(8.0, 5.0);
	DrawRoom dRoom(room);

	Cursor arrowCursor;
	Cursor handCursor;

	RenderWindow window(VideoMode(500, 500), "Hanginterferencia modellezese");
	window.setFramerateLimit(60);

	Font* font{ new Font() };
	font->loadFromFile("Media/noto_sans.ttf");
	Text* title{ new Text() };
	title->setFont(*font);
	title->setCharacterSize(40);
	title->setFillColor(Colors::BLACK);
	title->setString(L"Hanginterferencia\nModellezése");
	title->setOrigin(title->getGlobalBounds().width / 2 ,title->getGlobalBounds().height / 2);
	title->setPosition(250, 100);

	Button* start{ new Button(Vector2f(250, 75), Vector2f(250, 250)) };
	Button* credits{ new Button(Vector2f(250, 75), Vector2f(250, 350)) };
	Button* exit{ new Button(Vector2f(250, 75), Vector2f(250, 450)) };

	start->setText("Start");
	credits->setText("Credits");
	exit->setText("Exit");

	bool* atCredits{ new bool{false} };

	if (window.hasFocus())
	while (window.isOpen())
	{
		window.setSize(Vector2u(500, 500));

		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				goto END;
			}

		    if (event.type == sf::Event::Resized)
		    {
		        sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
		        window.setView(sf::View(visibleArea));
		    }

			if (event.type == Event::MouseMoved)
			{
				Vector2f mousePos(Mouse::getPosition(window));

				start->highlight(start->isInside(mousePos));
				credits->highlight(credits->isInside(mousePos));
				exit->highlight(exit->isInside(mousePos));
			}

			if (event.type == Event::MouseButtonPressed)
			{
				Vector2f mousePos(Mouse::getPosition(window));

				if (start->isInside(mousePos))
				{
					delete font;
					delete title;
					delete atCredits;
					delete start;
					delete credits;
					delete exit;

					goto START;
				}

				if (credits->isInside(mousePos))
				{
					*atCredits = true;
				}

				if (exit->isInside(mousePos))
				{
					goto END;
				}
			}
		}

		if (*atCredits)
		{
			creditsMenu(window);

			*atCredits = false;
		}

		window.clear(Colors::LIGHTGREEN);

		window.draw(*title);
		window.draw(*start);
		window.draw(*exit);
		window.draw(*credits);

		window.display();
	}


	START:
	room.setSource(Point(3.0, 3.0));
	room.setTarget(Point(5.0, 2.5));
	room.calcReflectionPoints();
	room.setParams(1000);
	room.calcDistances();
	room.calcDisplacement();

	dRoom.setSize(640);
	dRoom.createPoints();
	dRoom.setMode(SHOW_REFLECTIONS);

	arrowCursor.loadFromSystem(Cursor::Arrow);
	handCursor.loadFromSystem(Cursor::Hand);

	window.setSize(dRoom.getVisualizationSize());


	if (window.hasFocus())
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

		    	dRoom.createPoints();
		    	dRoom.resetMode();

		    	window.setSize(dRoom.getVisualizationSize());
		        sf::FloatRect visibleArea(0, 0, dRoom.getVisualizationSize().x, dRoom.getVisualizationSize().y);
		        window.setView(sf::View(visibleArea));
		    }

		    if (event.type == sf::Event::MouseMoved)
		    {
		    	Vector2f mousePos(event.mouseMove.x, event.mouseMove.y);

	    		if (Mouse::isButtonPressed(Mouse::Left) && dRoom.getMovedPoint() != NOTHING)
	    		{
	    			dRoom.setMoveEnd(mousePos);
	    			dRoom.movePoint();
	    			dRoom.createDistances();
	    		}
	    		else
	    		{
			    	FloatRect sourceBox = dRoom.getSourceBounds();
			    	FloatRect targetBox = dRoom.getTargetBounds();

			    	if (sourceBox.contains(mousePos) || targetBox.contains(mousePos))
			    		window.setMouseCursor(handCursor);
			    	else
			    		window.setMouseCursor(arrowCursor);
	    		}
		    }

		    if (event.type == sf::Event::MouseButtonPressed)
		    {
		    	Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);
		    	FloatRect sourceBox = dRoom.getSourceBounds();
		    	FloatRect targetBox = dRoom.getTargetBounds();

		    	if (sourceBox.contains(mousePos))
		    	{
		    		dRoom.setMoveBegin(mousePos);

		    		dRoom.setMovedPoint(SOURCE);

		    		dRoom.setMode(SHOW_DISTANCES);
		    	}
		    	else if (targetBox.contains(mousePos))
		    	{
		    		dRoom.setMoveBegin(mousePos);

		    		dRoom.setMovedPoint(TARGET);

		    		dRoom.setMode(SHOW_DISTANCES);
		    	}
		    }
		    else if (event.type == sf::Event::MouseButtonReleased)
		    {
		    	dRoom.setMode(SHOW_REFLECTIONS);

		    	dRoom.setMovedPoint(NOTHING);
		    }
		}

		window.clear(Colors::WHITE);
		window.draw(dRoom);
		window.display();
	}


    END: return 0;
}



void creditsMenu(RenderWindow& window)
{
	Button back(Vector2f(250, 75), Vector2f(250, 350));
	back.setText("Back");

	Font font;
	font.loadFromFile("Media/noto_sans.ttf");

	Text credits;
	credits.setFont(font);
	credits.setFillColor(Colors::BLACK);
	credits.setCharacterSize(30);
	credits.setString(L"Készítette: Farkas Endre\n\nTémavezető tanár: Bartyik Zita");
	credits.setOrigin(credits.getGlobalBounds().width / 2, credits.getGlobalBounds().height / 2);
	credits.setPosition(250, 150);

	if (window.hasFocus())
	while (window.isOpen())
	{
		window.setSize(Vector2u(500, 500));

		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				window.close();
			}

			if (event.type == Event::MouseMoved)
			{
				Vector2f mousePos(Mouse::getPosition(window));

				back.highlight(back.isInside(mousePos));
			}

			if (event.type == Event::MouseButtonPressed)
			{
				Vector2f mousePos(Mouse::getPosition(window));

				if (back.isInside(mousePos))
				{
					return;
				}
			}
		}

		window.clear(Colors::LIGHTGREEN);

		window.draw(back);
		window.draw(credits);

		window.display();
	}
}
