/*
 *  Project: SzalontaGrafika2024
 *   Author: Endre
 */

#ifndef UTILS_HPP_
#define UTILS_HPP_

#include <SFML/Graphics.hpp>


struct Colors
{
	const static sf::Color BLUE;
	const static sf::Color WHITE;
	const static sf::Color CYAN;
	const static sf::Color BLACK;
	const static sf::Color RED;
	const static sf::Color DARKGREY;
	const static sf::Color LIGHTGREY;
	const static sf::Color LIGHTGREEN;
};

double round_to_precision(double value, int decimal_places);

int to_millis(double meters);
double to_meters(int milis);




#endif /* UTILS_HPP_ */
