/*
 * Menus.hpp
 *
 *  Created on: Apr 28, 2025
 *      Author: kali
 */

#ifndef SRC_HEADER_FILES_MENUS_HPP_
#define SRC_HEADER_FILES_MENUS_HPP_

#include <SFML/Graphics.hpp>
#include "Button.hpp"


class sideMenu : public sf::Drawable, public sf::Transformable
{
public:
	sideMenu(sf::Vector2f size, float fromWidth);

	void setSize(sf::Vector2f size);
	void setBegin(float fromWidth);

	sf::Vector2f getSize();
	float getBegin();

	std::string checkAction(sf::Event& event, sf::Vector2f& mousePos);
private:
	sf::Font font;

	sf::RectangleShape mainBody;
	sf::Text menu_title;

	sf::Text roomSize_title;
	TextField x;
	TextField y;

	sf::Text reflections_title;
	Button reflections;

	sf::Text positions_title;
	Button bestPos;

	Button back;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states)const override;
};


#endif /* SRC_HEADER_FILES_MENUS_HPP_ */
