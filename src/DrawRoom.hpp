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

enum Mode
{
	SHOW_REFLECTIONS,
	SHOW_DISTANCES,
	UNSELECTED
};


class DrawRoom : public sf::Drawable, public sf::Transformable
{
public:
	DrawRoom(Room& room);

	void setSize(int x);
	sf::Vector2u getRoomSize();
	sf::Vector2u getVisualizationSize();

	void setMode(Mode mode);
	void resetMode(Mode mode);

	void createPoints();

	int getExtension();

	sf::FloatRect getSourceBounds();
	sf::FloatRect getTargetBounds();

	sf::Vector2f getSourcePos();

private:
	Room& room;

	Mode mode;

	int extension;
	double ratio;			// from millis to pixels

	sf::RectangleShape bounds;

	sf::CircleShape source;
	Target target;

//	Mode: VISUALISING_REFLECTIONS
	std::vector<sf::VertexArray> reflectionPoints;
	std::vector<Arrow> waveDirections;

//	Mode: SETTING_DISTANCES
	DoubleHeadedArrow distX;
	DoubleHeadedArrow distY;

	void createReflectionPoints();
	void createWaveDir();
	void calcTransformRatio();

	void eraseReflectionPoints();
	void eraseWaveDir();

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	double millisToPixels(int millis);
	int startAngle(Wall wall);

};



#endif /* DRAWROOM_HPP_ */
