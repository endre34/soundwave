/*
 *  Project: SzalontaGrafika2024
 *   Author: Endre
 */

#ifndef BUTTON_HPP_
#define BUTTON_HPP_

#include <SFML/Graphics.hpp>

class Button : public sf::Drawable, public sf::Transformable
{
public:
	Button(const sf::Vector2f& size, const sf::Vector2f& position);

	void highlight(bool state);
	void setText(std::string text);

	bool isInside(const sf::Vector2f& mousePos);

private:
	sf::RectangleShape body;

	sf::Font font;
	sf::Text text;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};



#endif /* BUTTON_HPP_ */
