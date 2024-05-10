/*
 *  Project: SzalontaGrafika2024
 *   Author: Endre
 */

#include <cmath>

#include "utils.hpp"


const sf::Color Colors::BLUE(0, 0, 255);
const sf::Color Colors::WHITE(255, 255, 255);
const sf::Color Colors::CYAN(50, 250, 250);
const sf::Color Colors::BLACK(0, 0, 0);
const sf::Color Colors::RED(240, 75, 75);
const sf::Color Colors::DARKGREY(75, 75, 75);
const sf::Color Colors::LIGHTGREY(245, 245, 245);
const sf::Color Colors::LIGHTGREEN(150, 200, 140);
const sf::Color Colors::TRANSPARENTGREEN(150, 200, 140, 150);


double round_to_precision(double value, int decimal_places)
{
    double multiplier = std::pow(10.0, decimal_places);
    return std::round(value * multiplier) / multiplier;
}

int to_millis(double meters)
{
	return meters * 1000.0;
}

double to_meters(int millis)
{
	return millis / 1000.0;
}
