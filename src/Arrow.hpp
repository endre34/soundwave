/*
 *  Project: SzalontaGrafika2024
 *   Author: Endre
 */

#ifndef ARROW_HPP_
#define ARROW_HPP_

#include <SFML/Graphics.hpp>
#include "Point.hpp"


class Arrow : public sf::Drawable, public sf::Transformable
{
public:
	Arrow(const sf::Vector2f& point1,const sf::Vector2f& point2);

private:
	sf::RectangleShape line;
	sf::CircleShape head;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	double get_angle(const sf::Vector2f& point1,const sf::Vector2f& point2);
};



#endif /* ARROW_HPP_ */
