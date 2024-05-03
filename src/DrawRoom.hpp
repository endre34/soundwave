/*
 *  Project: SzalontaGrafika2024
 *   Author: Endre
 */

#ifndef DRAWROOM_HPP_
#define DRAWROOM_HPP_

#include <SFML/Graphics.hpp>
#include <vector>

#include "ComplexShapes.hpp"
#include "Room.hpp"


class DrawRoom : public sf::Drawable, public sf::Transformable
{
public:
	DrawRoom(Room& room);

	void setSize(int x);
	sf::Vector2u getRoomSize();
	sf::Vector2u getVisualizationSize();

	void calcTransformRatio();

	void createPoints();
	void createWaveDir();

	int getExtension();

private:
	Room& room;

	int extension;
	double ratio;			// from millis to pixels

	sf::RectangleShape bounds;
	sf::CircleShape source;
	Target target;
	std::vector<sf::VertexArray> reflectionPoints;
	std::vector<Arrow> waveDirections;


	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	double millisToPixels(int millis);
	int startAngle(Wall wall);

};



#endif /* DRAWROOM_HPP_ */
