/*
 *  Project: SzalontaGrafika2024
 *   Author: Endre
 */

#include "Header_files/Button.hpp"
#include "Header_files/utils.hpp"

using namespace std;
using namespace sf;


Button::Button(const Vector2f& size, const Vector2f& position)
{
	body.setSize(size);
	body.setOrigin(body.getGlobalBounds().width / 2, body.getGlobalBounds().height / 2);
	body.setPosition(position);

	body.setFillColor(Colors::LIGHTGREY);
	body.setOutlineColor(Colors::BLACK);
	body.setOutlineThickness(3);


	font.loadFromFile("Media/noto_sans.ttf");
	text.setFont(font);

	text.setCharacterSize(size.y / 2);
	text.setFillColor(Colors::BLACK);

	text.setOrigin(text.getGlobalBounds().width / 2, text.getGlobalBounds().height / 2);
	text.setPosition(position);
}

void Button::highlight(bool state)
{
	if (state)
	{
		body.setOutlineThickness(6);
	}
	else
	{
		body.setOutlineThickness(3);
	}
}

void Button::setText(string text)
{
	Vector2f pos = this->text.getPosition();


	this->text.setString(text);

	this->text.setOrigin(this->text.getGlobalBounds().width / 2, this->text.getGlobalBounds().height / 2);
	this->text.setPosition(pos);
}

bool Button::isInside(const Vector2f& mousePos)
{
	FloatRect bounds = body.getGlobalBounds();

	if (bounds.contains(mousePos))
	{
		return true;
	}
	else
	{
		return false;
	}
}


void Button::draw(RenderTarget& target, RenderStates states) const
{
	states.transform *= getTransform();

	states.texture = nullptr;

	target.draw(body, states);

	target.draw(text, states);
}

