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

enum Object
{
	SOURCE,
	TARGET,
	NOTHING
};


class DrawRoom : public sf::Drawable, public sf::Transformable
{
public:
	DrawRoom(Room& room);

	void setSize(int x);
	sf::Vector2u getRoomSize();
	sf::Vector2u getVisualizationSize();

	void setMode(Mode mode);
	void resetMode();

	void createPoints();

	void setMoveBegin(const sf::Vector2f& pos);
	void setMoveEnd(const sf::Vector2f& pos);
	void setMovedPoint(Object object);
	Object getMovedPoint();

	void movePoint();


	int getExtension();

	sf::FloatRect getSourceBounds();
	sf::FloatRect getTargetBounds();

	sf::Vector2f getSourcePos();

	void createDistances();

private:
	Room& room;

	Mode mode;

	int extension;
	double ratio;			// from millis to pixels

	sf::RectangleShape bounds;

	sf::CircleShape source;
	Target target;
	sf::CircleShape optimalPosition;

//	Mode: SHOW_REFLECTIONS
	std::vector<sf::VertexArray> reflectionPoints;
	std::vector<Arrow> waveDirections;

//	Mode: SHOW_DISTANCES
	DoubleHeadedArrow distX, distY;

	sf::Font font;
	sf::Text textX, textY;

	Object movedObject;
	sf::Vector2f begin, end;

	void createReflectionPoints();
	void createWaveDir();
	void createBestPos();
	void calcTransformRatio();

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	double millisToPixels(int millis);
	int pixelsToMillis(double pixels);
	int startAngle(Wall wall);

};



#endif /* DRAWROOM_HPP_ */
