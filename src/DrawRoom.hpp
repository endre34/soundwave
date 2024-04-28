/*
 *  Project: SzalontaGrafika2024
 *   Author: Endre
 */

#ifndef DRAWROOM_HPP_
#define DRAWROOM_HPP_

#include <SFML/Graphics.hpp>
#include <vector>

#include "Room.hpp"
#include "Arrow.hpp"


class DrawRoom : public sf::Drawable, public sf::Transformable
{
public:
	DrawRoom(Room& room);

	void setSize(int x);
	sf::Vector2u getSize();
	sf::Vector2u getWindowSize();

	void calcTransformRatio();

	void createPoints();
	void createWaveDir();

	void out();

private:
	Room& room;

	int sizeX, sizeY;
	double ratio;			// from millis to pixels

	sf::RectangleShape bounds;
	std::vector<sf::VertexArray> points;
	std::vector<Arrow> waveDirections;

	double millisToPixels(int millis);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	int startAngle(Wall wall);

};



#endif /* DRAWROOM_HPP_ */
