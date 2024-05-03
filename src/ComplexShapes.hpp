/*
 *  Project: SzalontaGrafika2024
 *   Author: Endre
 */

#ifndef COMPLEXSHAPES_HPP_
#define COMPLEXSHAPES_HPP_

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


class Target : public sf::Drawable, public sf::Transformable
{
public:
	Target();
	Target(const sf::Vector2f& position, const sf::CircleShape& source);

	void setTarget(const sf::Vector2f& position, const sf::CircleShape& source);

	sf::Vector2f getPosition();

private:
	sf::CircleShape inner, outer;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};



#endif /* COMPLEXSHAPES_HPP_ */
