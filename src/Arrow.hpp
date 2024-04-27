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
	Arrow(const Point& point1,const Point& point2, double ratio);

private:
	sf::RectangleShape line;
	sf::CircleShape head;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};



#endif /* ARROW_HPP_ */
