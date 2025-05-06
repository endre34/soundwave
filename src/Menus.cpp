/*
 * Menus.cpp
 *
 *  Created on: Apr 28, 2025
 *      Author: kali
 */

#include "Header_files/Menus.hpp"
#include "Header_files/utils.hpp"
#include "Header_files/Room.hpp"

using namespace std;
using namespace sf;

sideMenu::sideMenu(Vector2f size, float fromWidth)
{
	mainBody.setSize(size);
	mainBody.setPosition(fromWidth, 0);
	mainBody.setFillColor(Colors::LIGHTGREEN);

	//#########################################	text	#################################

	font.loadFromFile("Media/noto_sans.ttf");
	menu_title.setFont(font);
	roomSize_title.setFont(font);
	roomSize_x.setFont(font);
	roomSize_y.setFont(font);
	reflections_title.setFont(font);
	positions_title.setFont(font);
	sound_title.setFont(font);
	sound.setFont(font);

	menu_title.setStyle(Text::Bold);
	roomSize_title.setStyle(Text::Bold);
	roomSize_x.setStyle(Text::Regular);
	roomSize_y.setStyle(Text::Regular);
	reflections_title.setStyle(Text::Bold);
	positions_title.setStyle(Text::Bold);
	sound_title.setStyle(Text::Bold);
	sound.setStyle(Text::Regular);

	menu_title.setFillColor(Colors::BLACK);
	roomSize_title.setFillColor(Colors::BLACK);
	roomSize_x.setFillColor(Colors::BLACK);
	roomSize_y.setFillColor(Colors::BLACK);
	reflections_title.setFillColor(Colors::BLACK);
	positions_title.setFillColor(Colors::BLACK);
	sound_title.setFillColor(Colors::BLACK);
	sound.setFillColor(Colors::BLACK);

	menu_title.setCharacterSize(24);
	menu_title.setString("MENU");
	menu_title.setOrigin(menu_title.getGlobalBounds().width / 2, menu_title.getGlobalBounds().height / 2);
	menu_title.setPosition(fromWidth + mainBody.getSize().x / 2, 25);

	roomSize_title.setCharacterSize(24);
	roomSize_title.setString("Room Size");
	roomSize_title.setOrigin(roomSize_title.getGlobalBounds().width / 2, roomSize_title.getGlobalBounds().height / 2);
	roomSize_title.setPosition(fromWidth + mainBody.getSize().x / 2, 75);

	roomSize_x.setCharacterSize(18);
	roomSize_x.setString("X:");
	roomSize_x.setOrigin(roomSize_x.getGlobalBounds().width / 2, roomSize_x.getGlobalBounds().height / 2);
	roomSize_x.setPosition(fromWidth + mainBody.getSize().x / 2 - 50, 110);

	roomSize_y.setCharacterSize(18);
	roomSize_y.setString("Y:");
	roomSize_y.setOrigin(roomSize_y.getGlobalBounds().width / 2, roomSize_y.getGlobalBounds().height / 2);
	roomSize_y.setPosition(fromWidth + mainBody.getSize().x / 2 - 50, 150);

	reflections_title.setCharacterSize(24);
	reflections_title.setString("Reflections");
	reflections_title.setOrigin(reflections_title.getGlobalBounds().width / 2, reflections_title.getGlobalBounds().height / 2);
	reflections_title.setPosition(fromWidth + mainBody.getSize().x / 2, 200);

	positions_title.setCharacterSize(24);
	positions_title.setString("Best Position");
	positions_title.setOrigin(positions_title.getGlobalBounds().width / 2, positions_title.getGlobalBounds().height / 2);
	positions_title.setPosition(fromWidth + mainBody.getSize().x / 2, 325);

	sound_title.setCharacterSize(24);
	sound_title.setString("Soundwave");
	sound_title.setOrigin(sound_title.getGlobalBounds().width / 2, sound_title.getGlobalBounds().height / 2);
	sound_title.setPosition(fromWidth + mainBody.getSize().x / 2, 450);

	sound.setCharacterSize(18);
	sound.setString("Hz:");
	sound.setOrigin(sound.getGlobalBounds().width / 2, sound.getGlobalBounds().height / 2);
	sound.setPosition(fromWidth + mainBody.getSize().x / 2 - 65, 490);

	//#########################################	buttons	#################################

	reflections.setSize(Vector2f(150, 50));
	reflections.setPos(Vector2f(fromWidth + mainBody.getSize().x / 2, 250));
	bestPos.setSize(Vector2f(150, 50));
	bestPos.setPos(Vector2f(fromWidth + mainBody.getSize().x / 2, 375));
	back.setSize(Vector2f(150, 50));
	back.setPos(Vector2f(fromWidth + mainBody.getSize().x / 2, 575));

	back.setText("Back");
	reflections.setText("Hide");
	bestPos.setText("Show");

	//#########################################	textbox	#################################

	x.setSize(Vector2f(70, 30));
	x.setPos(Vector2f(fromWidth + mainBody.getSize().x / 2, 113));
	y.setSize(Vector2f(70, 30));
	y.setPos(Vector2f(fromWidth + mainBody.getSize().x / 2, 153));
	hertz.setSize(Vector2f(70, 30));
	hertz.setPos(Vector2f(fromWidth + mainBody.getSize().x / 2, 490));

}

string sideMenu::checkAction(sf::Event& event, sf::Vector2f& mousePos)
{
	if (event.type == sf::Event::MouseMoved)
	{
		reflections.highlight(reflections.isInside(mousePos));
		bestPos.highlight(bestPos.isInside(mousePos));
		back.highlight(back.isInside(mousePos));

		x.highlight(x.isInside(mousePos));
		y.highlight(y.isInside(mousePos));
		hertz.highlight(hertz.isInside(mousePos));
	}

	if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
	{
		// Buttons
		if (reflections.isInside(mousePos)) return "reflections";
		if (bestPos.isInside(mousePos)) return "bestPos";
		if (back.isInside(mousePos)) return "back";

		x.deselect();
		y.deselect();
		hertz.deselect();

		if (x.isInside(mousePos))
		{
			if (x.getState())
			{
				x.deselect();
				return "";
			}
			else
			{
				x.select(); y.deselect(); hertz.deselect();
				return "x";
			}
		}

		if (y.isInside(mousePos))
		{
			if (y.getState())
			{
				y.deselect();
				return "";
			}
			else
			{
				y.select(); x.deselect(); hertz.deselect();
				return "y";
			}
		}

		if (hertz.isInside(mousePos))
		{
			if (hertz.getState())
			{
				hertz.deselect();
				return "";
			}
			else
			{
				hertz.select(); x.deselect(); y.deselect();
				return "hertz";
			}
		}

		x.deselect();
		y.deselect();
		hertz.deselect();
	}

	return "";
}



void sideMenu::setSize(Vector2f size)
{
	mainBody.setSize(size);
}

void sideMenu::setBegin(float fromWidth)
{
	mainBody.setPosition(fromWidth, 0);

	//#########################################	text	#################################

	menu_title.setPosition(fromWidth + mainBody.getSize().x / 2, 25);
	roomSize_title.setPosition(fromWidth + mainBody.getSize().x / 2, 75);
	roomSize_x.setPosition(fromWidth + mainBody.getSize().x / 2 - 50, 113);
	roomSize_y.setPosition(fromWidth + mainBody.getSize().x / 2 - 50, 153);
	reflections_title.setPosition(fromWidth + mainBody.getSize().x / 2, 200);
	positions_title.setPosition(fromWidth + mainBody.getSize().x / 2, 325);
	sound_title.setPosition(fromWidth + mainBody.getSize().x / 2, 450);
	sound.setPosition(fromWidth + mainBody.getSize().x / 2 - 65, 490);

	//#########################################	buttons	#################################

	reflections.setPos(Vector2f(fromWidth + mainBody.getSize().x / 2, 250));
	bestPos.setPos(Vector2f(fromWidth + mainBody.getSize().x / 2, 375));
	back.setPos(Vector2f(fromWidth + mainBody.getSize().x / 2, 575));

	//#########################################	textbox	#################################

	x.setPos(Vector2f(fromWidth + mainBody.getSize().x / 2, 110));
	y.setPos(Vector2f(fromWidth + mainBody.getSize().x / 2, 150));
	hertz.setPos(Vector2f(fromWidth + mainBody.getSize().x / 2, 490));
}

Vector2f sideMenu::getSize()
{
	return mainBody.getSize();
}

float sideMenu::getBegin()
{
	return mainBody.getPosition().x;
}

void sideMenu::draw(RenderTarget& target, RenderStates states) const
{
	states.transform *= getTransform();

	states.texture = nullptr;

	target.draw(mainBody, states);

	target.draw(menu_title, states);
	target.draw(roomSize_title, states);
	target.draw(reflections_title, states);
	target.draw(positions_title, states);
	target.draw(sound_title, states);
	target.draw(sound, states);
	target.draw(roomSize_x, states);
	target.draw(roomSize_y, states);

	target.draw(x, states);
	target.draw(y, states);
	target.draw(hertz, states);

	target.draw(reflections, states);
	target.draw(bestPos, states);
	target.draw(back, states);
}

void sideMenu::setRoomData(const int frequency, const double sizeX, const double sizeY)
{
	hertz.setText(to_string(frequency));
	x.setText(to_string(sizeX));
	y.setText(to_string(sizeY));
}




