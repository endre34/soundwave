/*
 * Menus.cpp
 *
 *  Created on: Apr 28, 2025
 *      Author: kali
 */

#include "Header_files/Menus.hpp"
#include "Header_files/utils.hpp"

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

	menu_title.setStyle(Text::Bold);
	roomSize_title.setStyle(Text::Bold);
	roomSize_x.setStyle(Text::Regular);
	roomSize_y.setStyle(Text::Regular);
	reflections_title.setStyle(Text::Bold);
	positions_title.setStyle(Text::Bold);

	menu_title.setFillColor(Colors::BLACK);
	roomSize_title.setFillColor(Colors::BLACK);
	roomSize_x.setFillColor(Colors::BLACK);
	roomSize_y.setFillColor(Colors::BLACK);
	reflections_title.setFillColor(Colors::BLACK);
	positions_title.setFillColor(Colors::BLACK);

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

	//#########################################	buttons	#################################

	reflections.setSize(Vector2f(50, 50));
	reflections.setPos(Vector2f(fromWidth + 50, 150));
	bestPos.setSize(Vector2f(50, 50));
	bestPos.setPos(Vector2f(fromWidth + 50, 225));
	back.setSize(Vector2f(50, 50));
	back.setPos(Vector2f(fromWidth + 50, 300));

	//#########################################	textbox	#################################

	x.setSize(Vector2f(70, 30));
	x.setPos(Vector2f(fromWidth + mainBody.getSize().x / 2, 110));
	y.setSize(Vector2f(70, 30));
	y.setPos(Vector2f(fromWidth + mainBody.getSize().x / 2, 150));

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
	roomSize_x.setPosition(fromWidth + mainBody.getSize().x / 2 - 50, 110);
	roomSize_y.setPosition(fromWidth + mainBody.getSize().x / 2 - 50, 150);

	//#########################################	buttons	#################################

	reflections.setPos(Vector2f(fromWidth + 50, 2000));
	bestPos.setPos(Vector2f(fromWidth + 50, 123132));
	back.setPos(Vector2f(fromWidth + 50, 300));

	//#########################################	textbox	#################################

	x.setPos(Vector2f(fromWidth + mainBody.getSize().x / 2, 110));
	y.setPos(Vector2f(fromWidth + mainBody.getSize().x / 2, 150));
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
	target.draw(roomSize_x, states);
	target.draw(roomSize_y, states);
	target.draw(x, states);
	target.draw(y, states);
	target.draw(reflections_title, states);
	target.draw(reflections, states);
	target.draw(positions_title, states);
	target.draw(bestPos, states);
	target.draw(back, states);
}




