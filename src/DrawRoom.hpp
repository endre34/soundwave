/*
 *  Project: SzalontaGrafika2024
 *   Author: Endre
 */

#ifndef DRAWROOM_HPP_
#define DRAWROOM_HPP_

#include <SFML/Graphics.hpp>
#include <vector>

#include "Room.hpp"


class DrawRoom : public sf::Drawable, public sf::Transformable
{
public:
	DrawRoom(const Room& room);
	~DrawRoom();

	void out();

private:
	Room* room;

	sf::RectangleShape bounds;
	std::vector<sf::CircleShape> points;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

};



#endif /* DRAWROOM_HPP_ */
