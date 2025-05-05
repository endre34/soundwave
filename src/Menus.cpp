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
	reflections_title.setFont(font);
	positions_title.setFont(font);

	menu_title.setStyle(Text::Bold);
	roomSize_title.setStyle(Text::Bold);
	reflections_title.setStyle(Text::Bold);
	positions_title.setStyle(Text::Bold);

	menu_title.setFillColor(Colors::BLACK);
	roomSize_title.setFillColor(Colors::BLACK);
	reflections_title.setFillColor(Colors::BLACK);
	positions_title.setFillColor(Colors::BLACK);

	menu_title.setCharacterSize(24);
	menu_title.setOrigin(menu_title.getGlobalBounds().width / 2, menu_title.getGlobalBounds().height / 2);
	menu_title.setPosition(fromWidth + 50, 50);
	menu_title.setString("MENU");

	//#########################################	buttons	#################################

	reflections.setSize(Vector2f(50, 50));
	reflections.setPos(Vector2f(fromWidth + 50, 150));
	bestPos.setSize(Vector2f(50, 50));
	bestPos.setPos(Vector2f(fromWidth + 50, 225));
	back.setSize(Vector2f(50, 50));
	back.setPos(Vector2f(fromWidth + 50, 300));

	//#########################################	textbox	#################################

	x.setSize(Vector2f(50, 50));
	x.setPos(Vector2f(fromWidth + 50, 375));
	y.setSize(Vector2f(50, 50));
	y.setPos(Vector2f(fromWidth + 50, 450));

}

void sideMenu::setSize(Vector2f size)
{
	mainBody.setSize(size);
}

void sideMenu::setBegin(float fromWidth)
{
	mainBody.setPosition(fromWidth, 0);

	//#########################################	text	#################################

	menu_title.setPosition(fromWidth + 50, 50);

	//#########################################	buttons	#################################

	reflections.setPos(Vector2f(fromWidth + 50, 150));
	bestPos.setPos(Vector2f(fromWidth + 50, 225));
	back.setPos(Vector2f(fromWidth + 50, 300));

	//#########################################	textbox	#################################

	x.setPos(Vector2f(fromWidth + 50, 375));
	y.setPos(Vector2f(fromWidth + 50, 450));
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
	target.draw(x, states);
	target.draw(y, states);
	target.draw(reflections_title, states);
	target.draw(reflections, states);
	target.draw(positions_title, states);
	target.draw(bestPos, states);
	target.draw(back, states);
}




