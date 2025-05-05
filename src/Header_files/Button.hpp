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
	Button() {};
	Button(const sf::Vector2f& size, const sf::Vector2f& position);

	virtual void highlight(bool state);
	void setText(std::string text);
	std::string getText() const;
	void setPos(const sf::Vector2f& position);
	void setSize(const sf::Vector2f& size);

	bool isInside(const sf::Vector2f& mousePos);

protected:
	sf::RectangleShape body;

private:
	sf::Font font;
	sf::Text text;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

// #########################################################################

class TextField : public Button
{
public:
	TextField()
		: selected { false }
		{};
	TextField(const sf::Vector2f& size, const sf::Vector2f& position)
		: Button { size, position },
		  selected { false }
		{};

	virtual void highlight(bool state) override;

	void select();
	void deselect();
private:

	bool selected;
};



#endif /* BUTTON_HPP_ */
