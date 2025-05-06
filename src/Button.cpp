/*
 *  Project: SzalontaGrafika2024
 *   Author: Endre
 */

#include "Header_files/Button.hpp"
#include "Header_files/utils.hpp"

using namespace std;
using namespace sf;

Button::Button()
{
	body.setFillColor(Colors::LIGHTGREY);
	body.setOutlineColor(Colors::BLACK);
	body.setOutlineThickness(1.5);

	font.loadFromFile("Media/noto_sans.ttf");
	text.setFont(font);

	text.setFillColor(Colors::BLACK);
}

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
	Vector2f pos = body.getPosition();


	this->text.setString(text);

	this->text.setOrigin(this->text.getGlobalBounds().width / 2, this->text.getGlobalBounds().height / 2);
	this->text.setPosition(pos);
}

string Button::getText() const
{
	return text.getString();
}

void Button::setPos(const Vector2f& position)
{
	body.setPosition(position);
	text.setPosition(position);
}

void Button::setSize(const Vector2f& size)
{
	body.setSize(size);
	text.setCharacterSize(size.y / 2);

	body.setOrigin(body.getGlobalBounds().width / 2, body.getGlobalBounds().height / 2);
	text.setOrigin(text.getGlobalBounds().width / 2, text.getGlobalBounds().height / 2);
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

void TextField::select()
{
	selected = true;

	body.setOutlineColor(Colors::RED);
	body.setOutlineThickness(6.0);
}

void TextField::deselect()
{
	selected = false;

	body.setOutlineColor(Colors::BLACK);
	body.setOutlineThickness(1.0);
}

void TextField::highlight(bool state)
{
	if (selected)
	{
		body.setOutlineThickness(6.0);
	}
	else if (state)
	{
		body.setOutlineThickness(6.0);
	}
	else
	{
		body.setOutlineThickness(1.0);
	}
}

bool TextField::getState() const
{
	return selected;
}









